#include <time.h>
#include "CMob.h"

CMob::CMob()
{
	int RandomColor = rand() % 2;
	_pEnemy = new CCQuad(3);
	_pEnemy->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_pEnemy->setShader(g_mxModelView, g_mxProjection);
	if (RandomColor == 0) _pEnemy->setColor(vec4(0.0f, 0.6235f, 0.7176f, 1), vec4(0.9529f, 0.9529f, 0.9529f, 1.0f));		//�H���C��
	else if (RandomColor == 1) _pEnemy->setColor(vec4(0.9960f, 0.8431f, 0.4f, 1), vec4(0.9529f, 0.9529f, 0.9529f, 1.0f));
	_fMT[0] = -X + (rand() % (X * 2) + (rand() % 10) * 0.1);	//x�y��
	_fMT[1] = -Y + (rand() % 25 + (rand() % 10) * 10);			//y�y��
	_mxET = Translate(_fMT[0], _fMT[1], 0);
	_mxMR = RotateZ(180.0f);
	_fscale = 0.15f;
	_mxMS = Scale(_fscale, _fscale, _fscale);
	_pEnemy->setTRSMatrix(_mxET * _mxMS * _mxMR);
	CreateBulletList();
}

CMob::~CMob()
{
	
}

//----------------------------------------------
void CMob::UpdateMatrix(float delta, int status)
{
	_fMT[1] -= delta * _fMSpeed;	//y�y��
	_mxET = Translate(_fMT[0], _fMT[1], _fMT[2]);
	_pEnemy->setTRSMatrix(_mxET * _mxMS * _mxMR);
}
void CMob::GL_Draw()
{
	_pEnemy->draw();

	for (vector<CBullet *>::iterator spriteIterator = ballsAry->begin();
		spriteIterator != ballsAry->end(); spriteIterator++)
	{
		(*spriteIterator)->GL_Draw();
	}
}

void CMob::GL_SetTRSMatrix(mat4 &mat)
{
	_mxET = mat;
	_fET[0] = _mxET._m[0][3];
	_fET[1] = _mxET._m[1][3];
	_pEnemy->setTRSMatrix(mat);
}

//----------------------------------------------

void CMob::SetColor(int RandomColor)
{
	//LE
	if (RandomColor == 0) _pEnemy->setColor(vec4(-1.0f, 0.0f, 0.0f, 1));		//�H���C��
	else if (RandomColor == 1) _pEnemy->setColor(vec4(0.0f, -1.0f, 0.0f, 1));
	else _pEnemy->setColor(vec4(0.0f, 0.0f, -1.0f, 1));
}

void CMob::CreateBulletList()
{
	ballsAry = new vector<CBullet *>;
}

void CMob::ShootBullet(float delta)
{
	static int updates = 0;
	if (_fMT[1] <= 7.0f && _fMT[1] >= -7.0f)
	{
		if (updates >= 5000) {
			CBullet *ball = new CBullet;
			ballsAry->push_back(ball);
			updates = 0;
		}
	}
	
	updates++;

	for (vector<CBullet *>::iterator spriteIterator = ballsAry->begin();
		spriteIterator != ballsAry->end(); spriteIterator++)
	{
		(*spriteIterator)->ShootBulletDown(delta, _fMT[0], _fMT[1], _mxBS);
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

void CMob::DeleteBullet()
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