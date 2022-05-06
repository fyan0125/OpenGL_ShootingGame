#include "CPlayer.h"
#include "CBullet.h"

CBullet::CBullet() //Player  Bullet
{
	_isShoot = false;
	_fBulletSpeed = 30.f;

	_pBullet = new CCQuad(1);
	_pBullet->setColor(vec4(0.9019f, 0.9764f, 0.6862f, 1));
	_pBullet->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_pBullet->setShader(g_mxModelView, g_mxProjection);

	_fBT[1] = PLAYER_Y_AXIS;
	_mxBT = Translate(-20, _fBT[1], _fBT[2]);
	_fscale = 0.03f;
	_mxBS = Scale(_fscale, _fscale, _fscale);
	_pBullet->setTRSMatrix(_mxBT*_mxBS);
}

CBullet::CBullet(float y) //Enemy  Bullet
{
	_isShoot = false;
	_fBulletSpeed = -30.f;

	_pBullet = new CCQuad();

	_fBT[1] = y;
	_mxBT = Translate(_fBT[0], _fBT[1], _fBT[2]);
	_fscale = 0.3f;
	_mxBS = Scale(_fscale, _fscale, _fscale);
	_pBullet->setTRSMatrix(_mxBT*_mxBS);
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
	_fBT[0] = mat._m[0][3];
	_fBT[1] = mat._m[1][3];
	_mxBT = Translate(_fBT[0], _fBT[1], _fBT[2]);
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
	_pBullet->setTRSMatrix(_mxBT*_mxBS);
}

void CBullet::ShootBulletDown(float delta, float passive_x, float passive_y, mat4 &mxS) //向下發射子彈
{
	if (!_isShoot) {		//固定發射時的x座標
		_fBT[0] = passive_x;
		_fBT[1] = passive_y;
		_isShoot = true;
	}
	_fBT[1] -= delta * _fBulletSpeed;
	_mxBT = Translate(_fBT[0], _fBT[1], _fBT[2]);
	_pBullet->setTRSMatrix(_mxBT * mxS*_mxBS);
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

float CBullet::GetBulletPosition()
{
	float y;
	y = _mxBT._m[1][3];
	return y;
}