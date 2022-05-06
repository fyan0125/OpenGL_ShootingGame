#pragma once
#ifndef CENEMY_H
#define CENEMY_H
#include <vector>
#include "../Header/Angel.h"
#include "CCamera.h"
#include "CCQuad.h"
#include "CBullet.h"
using namespace std;

class CEnemy
{
protected:
	CCQuad *_pEnemy;
					
	float _fET[3] = { 0 };		// For TRS
	mat4 _mxET;					//for main object translation

								// Bullet List
	mat4 _mxBT;								// for bullet translate
	mat4 _mxBS;								// for big shoot scale
	mat4 _mxBR;								//子彈轉向

	vector<CBullet *> *ballsAry;

public:

	CEnemy();
	virtual ~CEnemy();

	virtual void UpdateMatrix(float delta, int Status) = 0;			//更新運動
	virtual void GL_Draw() = 0;
	mat4 GetTranslateMatrix();						//取得BOSS位置
	mat4 GetBulletTranslateMatrix();				//取得子彈位置

	virtual void CreateBulletList() = 0;							//建立子彈串列
	virtual void ShootBullet(float delta) = 0;						//發射子彈
	virtual void DeleteBullet() = 0;
};
#endif