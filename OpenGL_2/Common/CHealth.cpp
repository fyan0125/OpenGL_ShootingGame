#include "CHealth.h"

CHealth::CHealth()
{
	_pHP = new CCQuad;
	_pHP->setColor(vec4(1.0f, 0.0f, 0.0f, 1));
	_pHP->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_pHP->setShader(g_mxModelView, g_mxProjection);
	_fHPT[1] = 6.95; //y®y¼Ð
	_mxHPT = Translate(_fHPT[0], _fHPT[1], _fHPT[2]);
	_fHPS[0] = 10.0f;		//X
	_fHPS[1] = 0.25;	//Y
	_fHPS[2] = 1.0f;		//Z
	_mxHPS = Scale(_fHPS[0], _fHPS[1], _fHPS[2]);
	_pHP->setTRSMatrix(_mxHPT * _mxHPS);
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

void CHealth::GL_SetTRSMatrix(mat4 &mat)
{
	_pHP->setTRSMatrix(mat);
}

//----------------------------------------------------------

void CHealth::UpdateMatrix(float delta)
{
	_pHP->setTRSMatrix(_mxHPT * _mxHPS);
}

void CHealth::GL_Draw()
{
	_pHP->draw();
}

//----------------------------------------------------
mat4 CHealth::GetTRSMatrix()
{
	return(_pHP->GetTRSMatrix());
}