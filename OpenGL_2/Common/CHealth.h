#include "../Header/Angel.h"
#include "CCQuad.h"

#define HP_Y_SCALE 0.25f	//Y軸縮放

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
	mat4 _mxHPT_adjust;					//血條位置，調整用

public:

	CHealth(float y_axis, float x_scale);		//給血條Y座標, X Scale
	~CHealth();

	void GL_SetTranslatMatrix(mat4 &mat);			//更新位置
	void GL_SetAdjustTranslatMatrix(mat4 &mat);		//更新調整矩陣
	void GL_SetTRSMatrix(mat4 &mat);
	void UpdateMatrix(float);						//更新運動
	void GL_Draw();
	void SetViewMatrix(mat4 &);
	void SetProjectionMatrix(mat4 &);

	mat4 GetTRSMatrix();							//取得血條位置
	void SetColor(vec4 vColor);						//設定血條顏色
	void SetScaleMatrix(mat4 &scale);				//設定縮放矩陣

};