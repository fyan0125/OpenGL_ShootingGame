#include "CHealth.h"

CHealth::CHealth(float y_axis, float x_scale)
{
	//產生Obj檔實體物件
	//HP BAR
	_pHP = new CCQuad;
	_pHP->setColor(vec4(1.0f, 0.0f, 0.0f, 1));		//RED
	_pHP->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_pHP->setShader(g_mxModelView, g_mxProjection);
	_fHPT[1] = y_axis; //y座標
	_mxHPT = Translate(_fHPT[0], _fHPT[1], _fHPT[2]);
	_fHPS[0] = x_scale;		//X
	_fHPS[1] = HP_Y_SCALE;	//Y
	_fHPS[2] = 1.0f;		//Z
	_mxHPS = Scale(_fHPS[0], _fHPS[1], _fHPS[2]);	//縮放
	_pHP->setTRSMatrix(_mxHPT * _mxHPS);

	_mxHPT_adjust = Translate(vec4(0.0f, 0.0f, 0.0f, 0.0f));	//初始化調整矩陣
}

CHealth::~CHealth()
{
	if (_pHP != NULL) delete _pHP;
}

//----------------------------------------------------
void CHealth::GL_SetTranslatMatrix(mat4 &mat)
{
	_mxHPT = mat;
	_fHPT[0] = _mxHPT._m[0][3];
	_fHPT[1] = _mxHPT._m[1][3];
}

void CHealth::GL_SetAdjustTranslatMatrix(mat4 &mat)
{
	_mxHPT_adjust = mat;
}

void CHealth::GL_SetTRSMatrix(mat4 &mat)
{
	_pHP->setTRSMatrix(mat);
}

//----------------------------------------------------------

void CHealth::UpdateMatrix(float delta)
{
	_pHP->setTRSMatrix(_mxHPT * _mxHPT_adjust * _mxHPS);
}

void CHealth::GL_Draw()
{
	_pHP->draw();
}

void CHealth::SetViewMatrix(mat4 &mvx)
{
	_pHP->setViewMatrix(mvx);
}

void CHealth::SetProjectionMatrix(mat4 &mpx)
{
	_pHP->setProjectionMatrix(mpx);
}

//----------------------------------------------------
mat4 CHealth::GetTRSMatrix()
{
	return(_pHP->GetTRSMatrix());
}

void CHealth::SetColor(vec4 vColor)
{
	_pHP->setColor(vColor);
}

void CHealth::SetScaleMatrix(mat4 &scale)
{
	_fHPS[0] = scale._m[0][0];		//X
									//_fHPS[1] = HP_Y_SCALE;	//Y
									//_fHPS[2] = 1.0f;		//Z
	_mxHPS = scale;	//縮放
}