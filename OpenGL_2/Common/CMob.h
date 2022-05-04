#include "../Header/Angel.h"
#include "CCQuad.h"
#include "CEnemy.h"
#include "CBullet.h"

#define BOSS_Y 3

class CMob : public CEnemy
{
protected:
	mat4 g_mxModelView = 1.0f;
	mat4 g_mxProjection = Ortho(-12.0f, 12.0f, -12.0f, 12.0f, -12.0f, 12.0f);

	float _fTrack[3] = { 0 };
	mat4 _mxTrack;
	GLfloat _fMAngle_Track = 0;			//路徑移動角度

public:

	float _fTrackSpeed;					//路徑速度
	mat4 _mxHPT_adjust;
	float _fHPMoveT_x;					//小怪減血
	float _fHPMoveS_x;					//小怪減血

	CMob(int RandomColor);
	~CMob();

	void UpdateMatrix(float);			//更新運動
	void GL_Draw();
	void GL_SetTRSMatrix(mat4 &mat);
	void SetColor(int RandomColor);				//設定小怪顏色

	void CreateBulletList();
	void DeleteBulletList();
	void ShootBullet(float delta);
	void NextBullet();
	void SetBulletPassiveMove();
};