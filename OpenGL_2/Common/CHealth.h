#include "../Header/Angel.h"
#include "CCQuad.h"

#define HP_Y_SCALE 0.25f	//Y�b�Y��

class CHealth
{
protected:
	// For Objects
	CCQuad *_pHP;					//��� ����
	mat4 g_mxModelView = 1.0f;
	mat4 g_mxProjection = Ortho(-5.0f, 5.0f, -7.0f, 7.0f, -12.0f, 12.0f);

										//TRS matrix
	float _fHPT[3] = { 0 };				//for player translation / scale
	float _fHPS[3];
	mat4 _mxHPT, _mxHPS;
	mat4 _mxHPT_adjust;					//�����m�A�վ��

public:

	CHealth(float y_axis, float x_scale);		//�����Y�y��, X Scale
	~CHealth();

	void GL_SetTranslatMatrix(mat4 &mat);			//��s��m
	void GL_SetAdjustTranslatMatrix(mat4 &mat);		//��s�վ�x�}
	void GL_SetTRSMatrix(mat4 &mat);
	void UpdateMatrix(float);						//��s�B��
	void GL_Draw();
	void SetViewMatrix(mat4 &);
	void SetProjectionMatrix(mat4 &);

	mat4 GetTRSMatrix();							//���o�����m
	void SetColor(vec4 vColor);						//�]�w����C��
	void SetScaleMatrix(mat4 &scale);				//�]�w�Y��x�}

};