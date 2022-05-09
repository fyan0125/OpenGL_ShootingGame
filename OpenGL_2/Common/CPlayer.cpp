#include "../header/Angel.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
	_pPlayer = new CCQuad(3);
	//_pPlayer->setColor(vec4(1.0f, 0.0f, 1.0f, 1.0f));
	_pPlayer->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_pPlayer->setShader(g_mxModelView, g_mxProjection);
	_mxPT = Translate(0, PLAYER_Y_AXIS, 0);
	_fscale = 0.1f;
	_mxPS = Scale(_fscale, _fscale, _fscale);
	_pPlayer->setTRSMatrix(_mxPT*_mxPS);

	//Mask
	_AngleSpeed = 0;
	float fDEscale = 0.3f;
	for (int i = 0; i < MASK_NUM; i++) {
		_pMask[i] = new CCQuad(1);
		_pMask[i]->setColor(vec4(0.8901f, 0.6570f, 0.5294f, 1.0f));
		_pMask[i]->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
		_pMask[i]->setShader(g_mxModelView, g_mxProjection);
		_mxMask[i] = Translate(MASK_RADIUS * cosf(M_PI*2.0f*i / MASK_NUM), MASK_RADIUS * sinf(M_PI*2.0f*i / MASK_NUM), 0.0f);
		_fMscale = 0.05f;
		_mxMS = Scale(_fMscale, _fMscale, _fMscale);
		_pMask[i]->setTRSMatrix(_mxPT * _mxMask[i] * _mxMS);
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
	for (vector<CBullet *>::iterator spriteIterator = ballsAry2->begin();
		spriteIterator != ballsAry2->end(); spriteIterator++)
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
		_pMask[i]->setTRSMatrix(_mxPT * mxMa[i] * _mxMask[i] * _mxMS);
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

void CPlayer::UpdateScale(float playerScale)
{
	_fscale = playerScale;
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
	}
	updates++;
}

int CPlayer::GetMaskNum()
{
	return _MaskNum;
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
	ballsAry2 = new vector<CBullet *>;
}

void CPlayer::ShootBullet(float delta, float passive_x, int bullet_time)
{
	static int updates = 0;
	if (updates >= bullet_time) {
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

void CPlayer::ShootBullet2(float delta, float passive_x, int bullet_time)
{
	static int updates = 0;
	if (updates >= bullet_time) {
		CBullet *ball = new CBullet;
		ballsAry2->push_back(ball);
		updates = 0;
	}
	updates++;

	for (vector<CBullet *>::iterator spriteIterator = ballsAry2->begin();
		spriteIterator != ballsAry2->end(); spriteIterator++)
	{
		(*spriteIterator)->PlayerShoot(delta, passive_x);
		_mxBT = (*spriteIterator)->GetTranslateMatrix();
	}

	vector<vector<CBullet *>::iterator> deleteArray;
	for (vector<CBullet *>::iterator spriteIterator = ballsAry2->begin();
		spriteIterator != ballsAry2->end(); spriteIterator++)
	{
		if ((*spriteIterator)->GetBulletPosition() > 7)
		{
			deleteArray.push_back(spriteIterator);
		}
	}

	for (vector<vector<CBullet *>::iterator>::iterator deleteIterator = deleteArray.begin();
		deleteIterator != deleteArray.end(); deleteIterator++)
	{
		ballsAry2->erase(*deleteIterator);
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
	vector<vector<CBullet *>::iterator> deleteArray2;
	for (vector<CBullet *>::iterator spriteIterator = ballsAry2->begin();
		spriteIterator != ballsAry2->end(); spriteIterator++)
	{
		deleteArray2.push_back(spriteIterator);
	}

	for (vector<vector<CBullet *>::iterator>::iterator deleteIterator = deleteArray2.begin();
		deleteIterator != deleteArray2.end(); deleteIterator++)
	{
		ballsAry2->erase(*deleteIterator);
	}
}