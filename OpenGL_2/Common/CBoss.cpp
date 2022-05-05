#include <time.h>
#include "CBoss.h"

CBoss::CBoss()
{
	int RandomColor = rand() % 2;
	_pEnemy = new CCQuad();
	_pEnemy->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_pEnemy->setShader(g_mxModelView, g_mxProjection);
	if (RandomColor == 0) _pEnemy->setColor(vec4(1.0f, 0.0f, 0.0f, 1));		//隨機顏色
	else if (RandomColor == 1) _pEnemy->setColor(vec4(0.0f, 1.0f, 0.0f, 1));
	_fMT[1] = 14;		//y座標
	_mxET = Translate(0, _fMT[1], 0);
	_pEnemy->setTRSMatrix(_mxET);
	CreateBulletList();
}

CBoss::~CBoss()
{

}

//----------------------------------------------
void CBoss::UpdateMatrix(float delta)
{
	if (first)
	{
		_fMT[1] -= delta * _fMSpeed;	//y座標
		_mxET = Translate(_fMT[0], _fMT[1], _fMT[2]);
		if (_fMT[1] < 6)first = false;
	}
	else
	{
		float speed = 3.5f;
		_fMAngle_Track += speed * delta;
		if (_fMAngle_Track > 360) _fMAngle_Track -= 360;

		float sint = sinf(_fMAngle_Track);
		float cost2 = cosf(_fMAngle_Track / 2.f);
		_fMT[0] = (cost2 * sint) * 4;
		_fMT[1] = (cost2)+5.0f;
		_mxET = Translate(_fMT[0], _fMT[1], _fMT[2]);
	}
	
	_pEnemy->setTRSMatrix(_mxET);
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

//----------------------------------------------

void CBoss::SetColor(int RandomColor)
{
	//LE
	if (RandomColor == 0) _pEnemy->setColor(vec4(-1.0f, 0.0f, 0.0f, 1));		//隨機顏色
	else if (RandomColor == 1) _pEnemy->setColor(vec4(0.0f, -1.0f, 0.0f, 1));
	else _pEnemy->setColor(vec4(0.0f, 0.0f, -1.0f, 1));
}

void CBoss::CreateBulletList()
{
	ballsAry = new vector<CBullet *>;
}

void CBoss::ShootBullet(float delta)
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
		if ((*spriteIterator)->getPosition() < -7)
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