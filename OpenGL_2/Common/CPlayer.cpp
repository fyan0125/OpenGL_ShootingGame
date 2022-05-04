#include "../header/Angel.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
	_pPlayer = new CCQuad();
	_pPlayer->setColor(vec4(1.0f, 0.0f, 1.0f, 1.0f));
	_pPlayer->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_pPlayer->setShader(g_mxModelView, g_mxProjection);
	_mxPT = Translate(0, PLAYER_Y_AXIS, 0);
	_fscale = 0.5f;
	_mxPS = Scale(_fscale, _fscale, _fscale);
	_pPlayer->setTRSMatrix(_mxPT*_mxPS);

	//Mask
	_AngleSpeed = 0;
	float fDEscale = 0.3f;
	for (int i = 0; i < MASK_NUM; i++) {
		_pMask[i] = new CCQuad();
		_pMask[i]->setColor(vec4(1.0f, 1.0f, 0.0f, 1.0f));
		_pMask[i]->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
		_pMask[i]->setShader(g_mxModelView, g_mxProjection);
		_mxMask[i] = Translate(MASK_RADIUS * cosf(M_PI*2.0f*i / MASK_NUM), MASK_RADIUS * sinf(M_PI*2.0f*i / MASK_NUM), 0.0f);
		_pMask[i]->setTRSMatrix(_mxPT * _mxMask[i] * _mxPS);
	}

	_BulletNum = 0;
	CreateBulletList();	//子彈
}

CPlayer::~CPlayer()
{
	delete _pPlayer;
}

//-------------------------------------------
void CPlayer::GL_Draw()
{
	_pPlayer->draw();

	_pBGet = _pBHead;
	while (_pBGet != nullptr) {
		_pBGet->GL_Draw();
		_pBGet = _pBGet->link;
	}
}

void CPlayer::UpdateMatrix(float delta)
{
	mat4 mxMa[MASK_NUM];

	_AngleSpeed += 150.f * delta;
	if (_AngleSpeed > 360) _AngleSpeed -= 360;
	for (int i = 0; i < MASK_NUM; i++) {
		mxMa[i] = RotateZ(_AngleSpeed);
		_pMask[i]->setTRSMatrix(_mxPT * mxMa[i] * _mxMask[i] * _mxPS);
	}
}

float CPlayer::GetPlayerScale()
{
	return _fscale;
}

void CPlayer::GL_DrawMask()
{
	for (int i = 0; i < MASK_NUM; i++) _pMask[i]->draw();
}

void CPlayer::GL_SetTRSMatrix(mat4 &mat)
{
	_pPlayer->setTRSMatrix(mat);
}

void CPlayer::GL_SetTranslatMatrix(mat4 &mat)
{
	_mxPT = mat;
	_fPT[0] = _mxPT._m[0][3];
	_fPT[1] = _mxPT._m[1][3];
}

void CPlayer::ShootBullet(float delta, float passive_x)
{
	_pBGet_shoot = _pBHead_shoot;
	_pBGet_shoot->PlayerShoot(delta, passive_x);
	_mxBT = _pBGet_shoot->GetTranslateMatrix();	//更新子彈位置
	_pBGet_shoot->_isShoot = true;		//子彈射出
}

void CPlayer::NextBullet(float g_fPTx)
{
	_BulletNum--; //子彈數量紀錄
	_pBHead_shoot = _pBHead_shoot->link;
	_pBGet_shoot->_isShoot = false;

	if (_BulletNum == 0) {	//沒有子彈
		_pBHead_shoot = _pBHead;
		_pBGet_shoot = _pBHead_shoot;
		while (_pBGet_shoot != nullptr) {
			_pBGet_shoot->ResetBullet(g_fPTx); //子彈歸位
			_pBGet_shoot = _pBGet_shoot->link;
			_BulletNum++; //子彈數量紀錄
		}
	}
}

void CPlayer::CreateBulletList()
{
	//first node
	_pBHead = new CBullet;
	_pBHead->link = nullptr;
	_pBTail = _pBHead;
	_pBHead_shoot = _pBHead;	
	_BulletNum++;				

	for (int i = 0; i < BULLET_NUM - 1; i++) {
		if ((_pBGet = new CBullet) == NULL) {
			exit(0);
		}
		_pBGet->link = nullptr;
		_pBTail->link = _pBGet;
		_pBTail = _pBGet;
		_BulletNum++;
	}
}