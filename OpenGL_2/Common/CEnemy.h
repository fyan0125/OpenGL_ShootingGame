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
	mat4 _mxBR;								//�l�u��V

	vector<CBullet *> *ballsAry;

public:

	CEnemy();
	virtual ~CEnemy();

	virtual void UpdateMatrix(float delta, int Status) = 0;			//��s�B��
	virtual void GL_Draw() = 0;
	mat4 GetTranslateMatrix();						//���oBOSS��m
	mat4 GetBulletTranslateMatrix();				//���o�l�u��m

	virtual void CreateBulletList() = 0;							//�إߤl�u��C
	virtual void ShootBullet(float delta) = 0;						//�o�g�l�u
	virtual void DeleteBullet() = 0;
};
#endif