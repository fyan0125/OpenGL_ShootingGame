#include "CPlayer.h"
#include "CBullet.h"

CBullet::CBullet() //Player  Bullet
{
	_isShoot = false;
	_fBulletSpeed = 30.f;

	_pBullet = new CCQuad();
	_pBullet->setColor(vec4(1.0f, 1.0f, 1.0f, 1));
	_pBullet->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_pBullet->setShader(g_mxModelView, g_mxProjection);

	_fBT[1] = PLAYER_Y_AXIS;
	_mxBT = Translate(-20, _fBT[1], _fBT[2]);
	_pBullet->setTRSMatrix(_mxBT);
}

CBullet::~CBullet()
{
	delete _pBullet;
}

//----------------------------------------------------
void CBullet::GL_Draw()
{
	_pBullet->draw();
}

void CBullet::GL_SetTRSMatrix(mat4 &mat)
{
	_pBullet->setTRSMatrix(mat);
}

//---------------------------------------
void CBullet::PlayerShoot(float delta, float passive_x)
{
	if (!_isShoot) {
		_fBT[0] = passive_x;
		_isShoot = true;
	}
	_fBT[1] += delta * _fBulletSpeed;
	_mxBT = Translate(_fBT[0], _fBT[1], _fBT[2]);
	_pBullet->setTRSMatrix(_mxBT);
}

void CBullet::ResetBullet(float fPTx)
{
	_fBT[0] = -20;
	_fBT[1] = PLAYER_Y_AXIS;
	_mxBT = Translate(_fBT[0], _fBT[1], _fBT[2]);
	_pBullet->setTRSMatrix(_mxBT);
}

//------------------------------------------------
mat4 CBullet::GetTranslateMatrix()
{
	return _mxBT;
}

mat4 CBullet::GetTRSMatrix()
{
	return(_pBullet->GetTRSMatrix());
}