#ifndef CPLAYER_H
#define CPLAYER_H
#include <vector>
#include "../Header/Angel.h"
#include "CCQuad.h"
#include "CBullet.h"
#include <vector>
using namespace std;

#define PLAYER_Y_AXIS -5.0f			//���aY�b��m
#define BULLET_NUM 10				//�l�u�ƶq
#define MASK_NUM 3				//���@�n�ƶq
#define MASK_RADIUS 1.5f				//���@�n  �Z���b�|

class CPlayer
{
protected:
	mat4 g_mxModelView = 1.0f;
	mat4 g_mxProjection = Ortho(-5.0f, 5.0f, -7.0f, 7.0f, -12.0f, 12.0f);

	CCQuad *_pPlayer;
	CCQuad *_pMask[MASK_NUM];
											
	float _fPT[3] = { 0 };				//TRS matrix	
	float _fscale = 1;
	mat4 _mxPT, _mxPS;

	GLfloat _AngleSpeed;						
	mat4 _mxMask[MASK_NUM];				

	// Bullet List
	mat4 _mxBT;
	CBullet *_pBHead, *_pBGet, *_pBTail;
	CBullet *_pBHead_shoot, *_pBGet_shoot;

public:
	CPlayer();
	~CPlayer();

	void GL_Draw();			
	void GL_DrawMask();

	void GL_SetTRSMatrix(mat4 &mat);
	void GL_SetTranslatMatrix(mat4 &mat);
	void UpdateMatrix(float delta);
	float GetPlayerScale();

	int _BulletNum;
	void CreateBulletList();
	void ShootBullet(float delta, float passive_x);
	void NextBullet(float g_fPTx);
};
#endif