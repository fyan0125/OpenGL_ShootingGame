#include "../Header/Angel.h"
#include "CCQuad.h"
#include "CEnemy.h"
#include "CBullet.h"

#define X 5
#define Y 7

class CBoss : public CEnemy
{
protected:
	mat4 g_mxModelView = 1.0f;
	mat4 g_mxProjection = Ortho(-5.0f, 5.0f, -7.0f, 7.0f, -12.0f, 12.0f);

	float _fBossT[3] = { 0 };
	float _fscale = 1;
	mat4 _mxBossS;
	GLfloat _fMAngle_Track = 0;

	bool first = true;

public:

	float _fMSpeed = 1.0f;

	CBoss();
	~CBoss();

	void UpdateMatrix(float delta, int BossStatus);			//更新運動
	void GL_Draw();
	void GL_SetTRSMatrix(mat4 &mat);

	void CreateBulletList();
	void ShootBullet(float delta);
	void DeleteBullet();
};