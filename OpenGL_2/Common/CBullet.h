#ifndef CBULLET_H
#define CBULLET_H
#include "CCQuad.h"
#include "../Header/Angel.h"

class CBullet
{
protected:
	mat4 g_mxModelView = 1.0f;
	mat4 g_mxProjection = Ortho(-12.0f, 12.0f, -12.0f, 12.0f, -12.0f, 12.0f);
	
	CCQuad *_pBullet;

	float _fBT[3] = { 0 };				//TRS matrix
	float _fscale = 1;
	mat4 _mxBT;							//for bullet translation
	mat4 _mxBR;							//for bullet rotation
	mat4 _mxBS;							//for bullet scale

public:
	CBullet();							//�ǤJ���o�g�l�u�����a����
	CBullet(float y);
	~CBullet();
	CBullet *link;						//for link list

	bool _isShoot;						
	float _fBulletSpeed;				//�l�u�t��

	void GL_Draw();
	void GL_SetTRSMatrix(mat4 &mat);

	void ShootBulletUp(float delta, float passive_x);				//�V�W�o�g�l�u
	void ResetBullet(float x);									//�]�w�l�u�C��

	mat4 GetTranslateMatrix();
	mat4 GetTRSMatrix();
};
#endif