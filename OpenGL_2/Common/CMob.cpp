#include <time.h>
#include "CMob.h"

CMob::CMob()
{
	_pEnemy = new CCQuad();
	_pEnemy->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_pEnemy->setShader(g_mxModelView, g_mxProjection);
	_pEnemy->setColor(vec4(1.0f, 0.0f, 0.0f, 1));
	_fMT[0] = -X + (rand() % (X * 2) + (rand() % 10) * 0.1);	//x座標
	_fMT[1] = rand() % (Y * 2) + (rand() % 10) * 5;			//y座標
	_mxET = Translate(0, _fMT[1], 0);
	_pEnemy->setTRSMatrix(_mxET);
}

CMob::~CMob()
{
	DeleteBulletList();		//子彈
}

//----------------------------------------------
void CMob::UpdateMatrix(float delta)
{
	_fMT[1] -= delta * _fMSpeed;	//y座標
	_mxMT = Translate(_fMT[0], _fMT[1], _fMT[2]);
	_pEnemy->setTRSMatrix(_mxMT);
}
void CMob::GL_Draw()
{
	_pEnemy->draw();
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
	if (RandomColor == 0) _pEnemy->setColor(vec4(-1.0f, 0.0f, 0.0f, 1));		//隨機顏色
	else if (RandomColor == 1) _pEnemy->setColor(vec4(0.0f, -1.0f, 0.0f, 1));
	else _pEnemy->setColor(vec4(0.0f, 0.0f, -1.0f, 1));
}

void CMob::CreateBulletList()
{

}
void CMob::DeleteBulletList()
{

}
void CMob::ShootBullet(float delta)
{

}
void CMob::NextBullet()
{

}
void CMob::SetBulletPassiveMove()
{

}