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

	float _fMT[3] = { 0 };
	mat4 _mxMT;
	GLfloat _fMAngle_Track = 0;

	bool first = true;

public:

	float _fMSpeed = 1.0f;					//���|�t��

	CBoss();
	~CBoss();

	void UpdateMatrix(float delta, int BossStatus);			//��s�B��
	void GL_Draw();
	void GL_SetTRSMatrix(mat4 &mat);
	void SetColor(int RandomColor);				//�]�w�p���C��

	void CreateBulletList();
	void ShootBullet(float delta);
	void DeleteBullet();
};