#include "../Header/Angel.h"
#include "CCQuad.h"
#include "CEnemy.h"
#include "CBullet.h"

#define X 5
#define Y 7

class CMob : public CEnemy
{
protected:
	mat4 g_mxModelView = 1.0f;
	mat4 g_mxProjection = Ortho(-5.0f, 5.0f, -7.0f, 7.0f, -12.0f, 12.0f);

	float _fMT[3] = { 0 };
	float _fscale = 1;
	mat4 _mxMS, _mxMR;

public:

	float _fMSpeed = 1.0f;					//路徑速度

	CMob();
	~CMob();

	void UpdateMatrix(float, int);			//更新運動
	void GL_Draw();
	void GL_SetTRSMatrix(mat4 &mat);

	void CreateBulletList();
	void ShootBullet(float delta);
	void DeleteBullet();
};