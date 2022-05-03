#ifndef CPLAYER_H
#define CPLAYER_H
#include "../Header/Angel.h"
#include "CCQuad.h"
#include "CBullet.h"

#define PLAYER_Y_AXIS -8.f			//玩家Y軸位置
#define BULLET_NUM 10				//子彈數量
#define MASK_NUM 3				//防護罩數量
#define DE_RADIUS 3.0f				//防護罩  距離半徑

class CPlayer
{
protected:
	mat4 g_mxModelView = 1.0f;
	mat4 g_mxProjection = Ortho(-12.0f, 12.0f, -12.0f, 12.0f, -12.0f, 12.0f);

	CCQuad *_pPlayer;
	CCQuad *_pMask[MASK_NUM];
											
	float _fPT[3] = { 0 };				//TRS matrix	
	mat4 _mxPT;

	//防護罩旋轉速度
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
	void GL_DrawDefense();

	void GL_SetTRSMatrix(mat4 &mat);
	void GL_SetTranslatMatrix(mat4 &mat);
	void UpdateMatrix(float delta);

	int _BulletNum;
	void CreateBulletList();
	void ShootBullet(float delta, float passive_x);
	void NextBullet(float g_fPTx);
};
#endif