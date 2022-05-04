#ifndef CBULLET_H
#define CBULLET_H
#include "CCQuad.h"
#include "../Header/Angel.h"

class CBullet
{
protected:
	mat4 g_mxModelView = 1.0f;
	mat4 g_mxProjection = Ortho(-5.0f, 5.0f, -7.0f, 7.0f, -12.0f, 12.0f);
	
	CCQuad *_pBullet;

	float _fBT[3] = { 0 };				
	float _fscale = 1;
	mat4 _mxBT, _mxBS;

public:
	CBullet();
	~CBullet();
	CBullet *link;						

	bool _isShoot;						
	float _fBulletSpeed;				

	void GL_Draw();
	void GL_SetTRSMatrix(mat4 &mat);

	void PlayerShoot(float delta, float passive_x);
	void ResetBullet(float x);						

	mat4 GetTranslateMatrix();
	mat4 GetTRSMatrix();
};
#endif