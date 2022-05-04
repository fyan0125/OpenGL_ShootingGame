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
	mat4 _mxMT;

public:

	float _fMSpeed = 2.0f;					//���|�t��

	CMob();
	~CMob();

	void UpdateMatrix(float);			//��s�B��
	void GL_Draw();
	void GL_SetTRSMatrix(mat4 &mat);
	void SetColor(int RandomColor);				//�]�w�p���C��

	void CreateBulletList();
	void DeleteBulletList();
	void ShootBullet(float delta);
	void NextBullet();
	void SetBulletPassiveMove();
};