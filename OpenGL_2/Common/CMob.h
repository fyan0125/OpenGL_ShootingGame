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
	GLfloat _fMAngle_Track = 0;			//���|���ʨ���

public:

	float _fTrackSpeed;					//���|�t��
	mat4 _mxHPT_adjust;
	float _fHPMoveT_x;					//�p�Ǵ��
	float _fHPMoveS_x;					//�p�Ǵ��

	CMob(int RandomColor);
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