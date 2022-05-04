#include <time.h>
#include "CMob.h"

CMob::CMob(int RandomColor)
{
	_pMainBody = new CCQuad();
	//if (RandomColor == 0) _pMainBody->setColor(vec4(-1.0f, 0.0f, 0.0f, 1));		//隨機顏色
	//else if (RandomColor == 1) _pMainBody->setColor(vec4(0.0f, -1.0f, 0.0f, 1));
	//else _pMainBody->setColor(vec4(0.0f, 0.0f, -1.0f, 1));
	_pMainBody->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_pMainBody->setShader(g_mxModelView, g_mxProjection);
	_pMainBody->setColor(vec4(-1.0f, 0.0f, 0.0f, 1));
	_fMT[1] = BOSS_Y;				//y座標
	_mxMT = Translate(0, 0, 0);
	_pMainBody->setTRSMatrix(_mxMT);
}

CMob::~CMob()
{
	DeleteBulletList();		//子彈
}

//----------------------------------------------
void CMob::UpdateMatrix(float delta)
{
	//float speed = 1.5f;	//路徑速度
	_fMAngle_Track += _fTrackSpeed * delta;
	if (_fMAngle_Track > 360) _fMAngle_Track -= 360; //歸零

	float sint, cost, sin2t, cos2t, sin3t, cos3t, cos4t, sin12t, cost2, sin5t2; //---------定義----------
	sint = sinf(_fMAngle_Track);			sin2t = sinf(2 * _fMAngle_Track);
	cost = cosf(_fMAngle_Track);			cos2t = cosf(2 * _fMAngle_Track);
	cos3t = cosf(3 * _fMAngle_Track);		cos4t = cosf(4 * _fMAngle_Track);
	cost2 = cosf(_fMAngle_Track / 2.f);		sin5t2 = sinf(5 * _fMAngle_Track / 2.f);
	sin3t = sinf(3 * _fMAngle_Track);
	float fsize = 1.0f;
	_fTrack[0] = (cost * sin3t)*fsize;				//x
	_fTrack[1] = (sint * sin3t)*fsize;				//y
	_mxTrack = Translate(_fTrack[0], _fTrack[1], _fTrack[2]);	//路徑移動

																//物件
	_pMainBody->setTRSMatrix(_mxMT * _mxTrack);
}
void CMob::GL_Draw()
{
	_pMainBody->draw();

	//子彈顯示
	//_pBGet = _pBHead;
	//while (_pBGet != nullptr) {
	//	if (_pBGet->_isShoot) _pBGet->GL_Draw();		//只顯示射出的子彈
	//	_pBGet = _pBGet->link;
	//}
}

void CMob::GL_SetTRSMatrix(mat4 &mat)
{
	_mxMT = mat;
	_fMT[0] = _mxMT._m[0][3];
	_fMT[1] = _mxMT._m[1][3];
	_pMainBody->setTRSMatrix(mat);
}

//----------------------------------------------

void CMob::SetColor(int RandomColor)
{
	//LE
	if (RandomColor == 0) _pMainBody->setColor(vec4(-1.0f, 0.0f, 0.0f, 1));		//隨機顏色
	else if (RandomColor == 1) _pMainBody->setColor(vec4(0.0f, -1.0f, 0.0f, 1));
	else _pMainBody->setColor(vec4(0.0f, 0.0f, -1.0f, 1));
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