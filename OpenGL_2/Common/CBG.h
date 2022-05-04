#ifndef CBG_H
#define CBG_H
#include "CCQuad.h"
#include "../Header/Angel.h"

#define BG_NUM 5
#define X 5
#define Y 7

class CBG
{
protected:
	mat4 g_mxModelView = 1.0f;
	mat4 g_mxProjection = Ortho(-5.0f, 5.0f, -7.0f, 7.0f, -12.0f, 12.0f);

	CCQuad *_pBG[BG_NUM];

	float _fSpeed;						//TRS matrix
	float _fBGT[BG_NUM][3] = { 0 };
	float _fBGScale;
	mat4 _mxBGT, _mxBGS;

public:
	CBG();
	~CBG();

	void GL_Draw();
	void UpdateMatrix(float);
};
#endif