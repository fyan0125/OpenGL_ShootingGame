#include <time.h>
#include "CBoss.h"

CBoss::CBoss()
{
	
	_pEnemy = new CCQuad(4);
	_pEnemy->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_pEnemy->setShader(g_mxModelView, g_mxProjection);
	
	_fBossT[1] = 14;		//y®y¼Ð
	_mxET = Translate(0, _fBossT[1], 0);
	_fscale = 0.15f;
	_mxBossS = Scale(_fscale, _fscale, _fscale);
	_pEnemy->setTRSMatrix(_mxET * _mxBossS);
	CreateBulletList();
}

CBoss::~CBoss()
{

}

//----------------------------------------------
void CBoss::UpdateMatrix(float delta, int BossStatus)
{
	if (first)
	{
		_fBossT[1] -= delta * _fMSpeed;	//y®y¼Ð
		_mxET = Translate(_fBossT[0], _fBossT[1], _fBossT[2]);
		if (_fBossT[1] < 6)first = false;
	}
	else
	{
		float speed = 3.5f;
		_fMAngle_Track += speed * delta;
		if (_fMAngle_Track > 360) _fMAngle_Track -= 360;

		float sint = sinf(_fMAngle_Track);
		float sin2t = sinf(_fMAngle_Track * 2.f);
		float cost2 = cosf(_fMAngle_Track / 2.f);
		if (BossStatus == 1)
		{
			_fBossT[0] = (cost2 * sint) * 4;
			_fBossT[1] = (cost2)+5.0f;
			_mxET = Translate(_fBossT[0], _fBossT[1], _fBossT[2]);
		}
		else if (BossStatus == 2)
		{
			_fBossT[0] = cost2 * 4;
			_fBossT[1] = sint + 5.0f;
			_mxET = Translate(_fBossT[0], _fBossT[1], _fBossT[2]);
		}
		else if (BossStatus == 3)
		{
			_fBossT[0] = cost2 * 4;
			_fBossT[1] = sin2t + 5.0f;
			_mxET = Translate(_fBossT[0], _fBossT[1], _fBossT[2]);
		}
	}
	
	_pEnemy->setTRSMatrix(_mxET * _mxBossS);
}

void CBoss::GL_Draw()
{
	_pEnemy->draw();

	for (vector<CBullet *>::iterator spriteIterator = ballsAry->begin();
		spriteIterator != ballsAry->end(); spriteIterator++)
	{
		(*spriteIterator)->GL_Draw();
	}
}

void CBoss::GL_SetTRSMatrix(mat4 &mat)
{
	_mxET = mat;
	_fET[0] = _mxET._m[0][3];
	_fET[1] = _mxET._m[1][3];
	_pEnemy->setTRSMatrix(mat);
}

void CBoss::CreateBulletList()
{
	ballsAry = new vector<CBullet *>;
}

void CBoss::ShootBullet(float delta)
{
	static int updates = 0;
	if (_fBossT[1] <= 7.0f && _fBossT[1] >= -7.0f)
	{
		if (updates >= 2000) {
			CBullet *ball = new CBullet;
			ballsAry->push_back(ball);
			updates = 0;
		}
	}

	updates++;

	for (vector<CBullet *>::iterator spriteIterator = ballsAry->begin();
		spriteIterator != ballsAry->end(); spriteIterator++)
	{
		(*spriteIterator)->EnemyShoot(delta, _fBossT[0], _fBossT[1], _mxBS);
		_mxBT = (*spriteIterator)->GetTranslateMatrix();
	}

	vector<vector<CBullet *>::iterator> deleteArray;
	for (vector<CBullet *>::iterator spriteIterator = ballsAry->begin();
		spriteIterator != ballsAry->end(); spriteIterator++)
	{
		if ((*spriteIterator)->GetBulletPosition() < -7)
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

void CBoss::DeleteBullet()
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