#include "CEnemy.h"

CEnemy::CEnemy()
{
	_pEnemy = NULL;
	_mxET = Translate(_fET[0], _fET[1], _fET[2]); // 0
}

CEnemy::~CEnemy()
{
	if (_pEnemy != NULL) delete _pEnemy;
}

mat4 CEnemy::GetTranslateMatrix()
{
	return _mxET;
}

mat4 CEnemy::GetBulletTranslateMatrix()
{
	return _mxBT;
}