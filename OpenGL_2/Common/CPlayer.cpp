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

	CreateBulletList();	//¤l¼u
}

CPlayer::~CPlayer()
{
	delete _pPlayer;
}

//-------------------------------------------
void CPlayer::GL_Draw()
{
	_pPlayer->draw();

	for (vector<CBullet *>::iterator spriteIterator = ballsAry->begin();
		spriteIterator != ballsAry->end(); spriteIterator++)
	{
		(*spriteIterator)->GL_Draw();
	}
}

void CPlayer::UpdateMatrix(float delta)
{
	mat4 mxMa[MASK_NUM];

	_AngleSpeed += 150.f * delta;
	if (_AngleSpeed > 360) _AngleSpeed -= 360;
	for (int i = 0; i < _MaskNum; i++) {
		mxMa[i] = RotateZ(_AngleSpeed);
		_pMask[i]->setTRSMatrix(_mxPT * mxMa[i] * _mxMask[i] * _mxPS);
	}
}

mat4 CPlayer::GetTranslateMatrix()
{
	return _mxPT;
}

mat4 CPlayer::GetBulletTranslateMatrix()
{
	return _mxBT;
}

float CPlayer::GetPlayerScale()
{
	return _fscale;
}

void CPlayer::AttackedByEnemies(float delta)
{
	static int updates = 0;
	if (updates >= 300) {
		_MaskNum -= 1;
		updates = 0;
		cout << "hit" << endl;
	}
	updates++;
}

void CPlayer::GL_DrawMask()
{
	for (int i = 0; i < _MaskNum; i++) _pMask[i]->draw();
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

void CPlayer::CreateBulletList()
{
	ballsAry = new vector<CBullet *>;
}

void CPlayer::ShootBullet(float delta, float passive_x)
{
	static int updates = 0;
	if (updates >= 500) {
		CBullet *ball = new CBullet;
		ballsAry->push_back(ball);
		updates = 0;
	}
	updates++;

	for (vector<CBullet *>::iterator spriteIterator = ballsAry->begin();
		spriteIterator != ballsAry->end(); spriteIterator++)
	{
		(*spriteIterator)->PlayerShoot(delta, passive_x);
		_mxBT = (*spriteIterator)->GetTranslateMatrix();
	}

	vector<vector<CBullet *>::iterator> deleteArray;
	for (vector<CBullet *>::iterator spriteIterator = ballsAry->begin();
		spriteIterator != ballsAry->end(); spriteIterator++)
	{
		if ((*spriteIterator)->GetBulletPosition() > 7)
		{
			deleteArray.push_back(spriteIterator);
		}
	}

	for (vector<vector<CBullet *>::iterator>::iterator deleteIterator = deleteArray.begin();
		deleteIterator != deleteArray.end(); deleteIterator++)
	{
		ballsAry->erase(*deleteIterator);
	}
}

void CPlayer::DeleteBullet()
{
	vector<vector<CBullet *>::iterator> deleteArray;
	for (vector<CBullet *>::iterator spriteIterator = ballsAry->begin();
		spriteIterator != ballsAry->end(); spriteIterator++)
	{
		deleteArray.push_back(spriteIterator);
	}

	for (vector<vector<CBullet *>::iterator>::iterator deleteIterator = deleteArray.begin();
		deleteIterator != deleteArray.end(); deleteIterator++)
	{
		ballsAry->erase(*deleteIterator);
	}
}