#include "../Header/Angel.h"
#include "CCQuad.h"

class CHealth
{
protected:
	// For Objects
	CCQuad *_pHP;					//血條 物件
	mat4 g_mxModelView = 1.0f;
	mat4 g_mxProjection = Ortho(-5.0f, 5.0f, -7.0f, 7.0f, -12.0f, 12.0f);

										//TRS matrix
	float _fHPT[3] = { 0 };				//for player translation / scale
	float _fHPS[3];
	mat4 _mxHPT, _mxHPS;

public:

	CHealth();
	~CHealth();

	void GL_SetTranslatMatrix(mat4 &mat);			//更新位置
	void GL_SetTRSMatrix(mat4 &mat);
	void UpdateMatrix(float);						//更新運動
	void GL_Draw();

	mat4 GetTRSMatrix();							//取得血條位置
	
};