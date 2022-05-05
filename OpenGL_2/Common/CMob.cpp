#include <time.h>
#include "CMob.h"

CMob::CMob()
{
	_pEnemy = new CCQuad();
	_pEnemy->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	_pEnemy->setShader(g_mxModelView, g_mxProjection);
	_pEnemy->setColor(vec4(1.0f, 0.0f, 0.0f, 1));
	_fMT[0] = -X + (rand() % (X * 2) + (rand() % 10) * 0.1);	//x�y��
	_fMT[1] = Y;			//y�y��
	_mxET = Translate(0, _fMT[1], 0);
	_pEnemy->setTRSMatrix(_mxET);
	_iBulletNum = 0;
	CreateBulletList();
}

CMob::~CMob()
{
	DeleteBulletList();		//�l�u
}

//----------------------------------------------
void CMob::UpdateMatrix(float delta)
{
	_fMT[1] -= delta * _fMSpeed;	//y�y��
	_mxMT = Translate(_fMT[0], _fMT[1], _fMT[2]);
	_pEnemy->setTRSMatrix(_mxMT);
}
void CMob::GL_Draw()
{
	_pEnemy->draw();

	//�l�u���
	_pBGet = _pBHead;
	while (_pBGet != nullptr) {
		if (_pBGet->_isShoot) _pBGet->GL_Draw();		//�u��ܮg�X���l�u
		_pBGet = _pBGet->link;
	}
}

void CMob::GL_SetTRSMatrix(mat4 &mat)
{
	_mxET = mat;
	_fET[0] = _mxET._m[0][3];
	_fET[1] = _mxET._m[1][3];
	_pEnemy->setTRSMatrix(mat);
}

//----------------------------------------------

void CMob::SetColor(int RandomColor)
{
	//LE
	if (RandomColor == 0) _pEnemy->setColor(vec4(-1.0f, 0.0f, 0.0f, 1));		//�H���C��
	else if (RandomColor == 1) _pEnemy->setColor(vec4(0.0f, -1.0f, 0.0f, 1));
	else _pEnemy->setColor(vec4(0.0f, 0.0f, -1.0f, 1));
}

void CMob::CreateBulletList()
{
	//first node
	_pBHead = new CBullet(_fMT[1]);
	_pBHead->link = nullptr;
	_pBTail = _pBHead;
	_pBHead_shoot = _pBHead;	//�l�u�o�g��
	_pBHead->GL_SetTRSMatrix(_mxMT * _mxBR); //�]�w�l�u��BOSS��m

	float fspeed = rand() % 20 + 10.f;
	_pBHead->_fBulletSpeed = fspeed;

	_iBulletNum++;	//�l�u�ƶq����

					//the rest of nodes
	for (int i = 0; i < BULLET_NUM - 1; i++) {
		if ((_pBGet = new CBullet(_fMT[1])) == NULL) {
			printf("�O���餣��\n"); exit(0);
		}
		_pBGet->link = nullptr;
		_pBTail->link = _pBGet;
		_pBTail = _pBGet;
		_pBGet->GL_SetTRSMatrix(_mxMT * _mxBR); //�]�w�l�u��BOSS��m
		_pBGet->_fBulletSpeed = fspeed;
		_iBulletNum++;	//�l�u�ƶq����
	}
}
void CMob::DeleteBulletList()
{
	_pBGet = _pBHead;
	while (_pBHead != nullptr) {
		_pBHead = _pBHead->link;
		delete _pBGet;
		_pBGet = _pBHead;
	}
	_iBulletNum = 0;	//�l�u�ƶq�k�s
}
void CMob::ShootBullet(float delta)
{
	_pBGet_shoot = _pBHead_shoot;
	_pBGet_shoot->ShootBulletDown(delta, _fMT[0], _fMT[1], _mxBS);
	_mxBT = _pBGet_shoot->GetTranslateMatrix();	//��s�l�u��m
	_pBGet_shoot->_isShoot = true;		//�l�u�g�X
}
void CMob::NextBullet()
{
	_iBulletNum--;				//�l�u�ƶq����
	_pBHead_shoot = _pBHead_shoot->link;
	_pBGet_shoot->_isShoot = false;

	if (_iBulletNum == 0) {	//�S���l�u
		_pBHead_shoot = _pBHead;
		_pBGet_shoot = _pBHead_shoot;
		while (_pBGet_shoot != nullptr) {
			_pBGet_shoot->ResetBullet(_mxBR, _fMT[0], _fMT[1]); //�l�u�k��
			_pBGet_shoot = _pBGet_shoot->link;
			_iBulletNum++; //�l�u�ƶq����
		}
	}
}
void CMob::SetBulletPassiveMove()
{
	_pBGet = _pBHead;	//�l�u��C
	while (_pBGet != nullptr) {
		if (_pBGet->_isShoot == false) { //�l�u�|���g�X
			_pBGet->GL_SetTRSMatrix(_mxMT * _mxBR);
		}
		_pBGet = _pBGet->link;
	}
}