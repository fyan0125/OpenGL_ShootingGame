#include "CBG.h"

CBG::CBG()
{
	_fSpeed = 10.f;

	for (int i = 0; i < BG_NUM; i++) {
		_pBG[i] = new CCQuad(0);
		_pBG[i]->setColor(vec4(0.7f, 0.7f, 0.7f, 1));
		_pBG[i]->setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
		_pBG[i]->setShader(g_mxModelView, g_mxProjection);

		_fBGT[i][0] = -X + (rand() % (X * 2) + (rand() % 10)*0.1);	//x座標
		_fBGT[i][1] = -Y + (rand() % (Y * 2) + (rand() % 10)*0.1);	//y座標
		_fBGT[i][2] = -5;				
		_mxBGT = Translate(_fBGT[i][0], _fBGT[i][1], _fBGT[i][2]);
		_fBGScale = 0.1f;
		_mxBGS = Scale(_fBGScale, _fBGScale, _fBGScale);
		_pBG[i]->setTRSMatrix(_mxBGT*_mxBGS);
	}
}

void CBG::GL_Draw()
{
	for (int i = 0; i < BG_NUM; i++) _pBG[i]->draw();
}

void CBG::UpdateMatrix(float delta)
{
	for (int i = 0; i < BG_NUM; i++) {
		_fBGT[i][1] -= delta * _fSpeed;	//y座標
		_mxBGT = Translate(_fBGT[i][0], _fBGT[i][1], _fBGT[i][2]);
		_pBG[i]->setTRSMatrix(_mxBGT*_mxBGS);

		if (_fBGT[i][1] < -7) {
			_fBGT[i][0] = -X + (rand() % (X * 2) + (rand() % 10)*0.1);	//x座標
			_fBGT[i][1] = Y + 1;	//上方開始
		}
	}
}

CBG::~CBG()
{
	for (int i = 0; i < BG_NUM; i++) delete _pBG[i];
}