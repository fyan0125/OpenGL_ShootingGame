#ifndef CPLAYER_H
#define CPLAYER_H
#include <vector>
#include "../Header/Angel.h"
#include "CCQuad.h"
#include "CBullet.h"
using namespace std;

#define PLAYER_Y_AXIS -5.0f			//???aY?b???m
#define MASK_NUM 5				//???@?n?ƶq
#define MASK_RADIUS 1.5f				//???@?n  ?Z???b?|

class CPlayer
{
protected:
	mat4 g_mxModelView = 1.0f;
	mat4 g_mxProjection = Ortho(-5.0f, 5.0f, -7.0f, 7.0f, -12.0f, 12.0f);

	int _MaskNum = 5;

	CCQuad *_pPlayer;
	CCQuad *_pMask[MASK_NUM];
											
	float _fPT[3] = { 0 };				//TRS matrix	
	float _fscale = 1;
	mat4 _mxPT, _mxPS;

	GLfloat _AngleSpeed;		
	float _fMscale = 1;
	mat4 _mxMask[MASK_NUM], _mxMS;

	// Bullet List
	mat4 _mxBT;

	vector<CBullet *> *ballsAry;
	vector<CBullet *> *ballsAry2;

public:
	CPlayer();
	~CPlayer();

	void GL_Draw();			
	void GL_DrawMask();

	void GL_SetTRSMatrix(mat4 &mat);
	void GL_SetTranslatMatrix(mat4 &mat);
	void UpdateMatrix(float delta);
	mat4 GetTranslateMatrix();
	mat4 GetBulletTranslateMatrix();
	void UpdateScale(float playerScale);
	float GetPlayerScale();
	void AttackedByEnemies(float delta);
	int GetMaskNum();

	void CreateBulletList();
	void ShootBullet(float delta, float passive_x, int bullet_time);
	void ShootBullet2(float delta, float passive_x, int bullet_time);
	void DeleteBullet();
};
#endif