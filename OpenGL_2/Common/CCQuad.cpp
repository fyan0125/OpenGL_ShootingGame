#include "CCQuad.h"

CCQuad::CCQuad()
{
	_nVtx = QUAD_NUM;
	_Points = new vec4[QUAD_NUM];

	_Points[0] = vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	_Points[1] = vec4(0.5f, 0.5f, 0.0f, 1.0f);
	_Points[2] = vec4(0.5f, -0.5f, 0.0f, 1.0f);
	_Points[3] = vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	_Points[4] = vec4(0.5f, -0.5f, 0.0f, 1.0f);
	_Points[5] = vec4(-0.5f, -0.5f, 0.0f, 1.0f);

	_Colors = new vec4[QUAD_NUM];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);  // (r, g, b, a)
	_Colors[1] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_Colors[2] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[3] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_Colors[4] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[5] = vec4(0.0f, 0.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;
}

CCQuad::CCQuad(int objectID)
{
	switch (objectID)
	{
	case 0://bg
		_nVtx = 30;
		_Points = new vec4[_nVtx];

		_Points[0] = vec4(-1.1357f, - 1.9671f, 0.0f, 1.0f);//1
		_Points[1] = vec4(0.0000f, - 4.7354f, 0.0f, 1.0f);//2
		_Points[2] = vec4(1.1357f, - 1.9671f, 0.0f, 1.0f);//3
		_Points[3] = vec4(1.1357f, - 1.9671f, 0.0f, 1.0f);
		_Points[4] = vec4(4.1010f, - 2.3677f, 0.0f, 1.0f);//4
		_Points[5] = vec4(2.2714f, 0.0000f, 0.0f, 1.0f);//5
		_Points[6] = vec4(-1.1357f, 1.9671f, 0.0f, 1.0f);//6
		_Points[7] = vec4(-4.1010f, 2.3677f, 0.0f, 1.0f);//7
		_Points[8] = vec4(-2.2714f, - 0.0000f, 0.0f, 1.0f);//8
		_Points[9] = vec4(1.1357f, 1.9671f, 0.0f, 1.0f);//9
		_Points[10] = vec4(-0.0000f, 4.7354f, 0.0f, 1.0f);//10
		_Points[11] = vec4(-1.1357f, 1.9671f, 0.0f, 1.0f);//6
		_Points[12] = vec4(2.2714f, 0.0000f, 0.0f, 1.0f);//5
		_Points[13] = vec4(4.1010f, 2.3677f, 0.0f, 1.0f);//11
		_Points[14] = vec4(1.1357f, 1.9671f, 0.0f, 1.0f);//9
		_Points[15] = vec4(-2.2714f, - 0.0000f, 0.0f, 1.0f);//8
		_Points[16] = vec4(-4.1010f, - 2.3677f, 0.0f, 1.0f);//12
		_Points[17] = vec4(-1.1357f, -1.9671f, 0.0f, 1.0f);//1
		_Points[18] = vec4(-1.1357f, 1.9671f, 0.0f, 1.0f);//6
		_Points[19] = vec4(-2.2714f, - 0.0000f, 0.0f, 1.0f);//8
		_Points[20] = vec4(-1.1357f, -1.9671f, 0.0f, 1.0f);//1
		_Points[21] = vec4(1.1357f, 1.9671f, 0.0f, 1.0f);//9
		_Points[22] = vec4(-1.1357f, 1.9671f, 0.0f, 1.0f);//6
		_Points[23] = vec4(-1.1357f, -1.9671f, 0.0f, 1.0f);//1
		_Points[24] = vec4(2.2714f, 0.0000f, 0.0f, 1.0f);//5
		_Points[25] = vec4(1.1357f, 1.9671f, 0.0f, 1.0f);//9
		_Points[26] = vec4(-1.1357f, -1.9671f, 0.0f, 1.0f);//1
		_Points[27] = vec4(1.1357f, -1.9671f, 0.0f, 1.0f);//3
		_Points[28] = vec4(2.2714f, 0.0000f, 0.0f, 1.0f);//5
		_Points[29] = vec4(-1.1357f, -1.9671f, 0.0f, 1.0f);//1
		_Colors = new vec4[_nVtx];
		for (int i = 0; i < _nVtx; i++) _Colors[i] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case 1://bullet
		_nVtx = 18;
		_Points = new vec4[_nVtx];

		_Points[0] = vec4(-3.1458f, - 3.1458f, 0.0f, 1.0f);//1
		_Points[1] = vec4(0.0000f, - 4.4500f, 0.0f, 1.0f);//2
		_Points[2] = vec4(3.1458f, - 3.1458f, 0.0f, 1.0f);//3
		_Points[3] = vec4(-4.4500f, - 0.0000f, 0.0f, 1.0f);//4
		_Points[4] = vec4(-3.1458f, - 3.1458f, 0.0f, 1.0f);//1
		_Points[5] = vec4(3.1458f, - 3.1458f, 0.0f, 1.0f);//3
		_Points[6] = vec4(-3.1458f, 3.1458f, 0.0f, 1.0f);//5
		_Points[7] = vec4(-4.4500f, - 0.0000f, 0.0f, 1.0f);//4
		_Points[8] = vec4(3.1458f, - 3.1458f, 0.0f, 1.0f);//3
		_Points[9] = vec4(-0.0000f, 4.4500f, 0.0f, 1.0f);//6
		_Points[10] = vec4(-3.1458f, 3.1458f, 0.0f, 1.0f);//5
		_Points[11] = vec4(3.1458f, - 3.1458f, 0.0f, 1.0f);//3
		_Points[12] = vec4(3.1458f, 3.1458f, 0.0f, 1.0f);//7
		_Points[13] = vec4(-0.0000f, 4.4500f, 0.0f, 1.0f);//6
		_Points[14] = vec4(3.1458f, - 3.1458f, 0.0f, 1.0f);//3
		_Points[15] = vec4(4.4500f, 0.0000f, 0.0f, 1.0f);//8
		_Points[16] = vec4(3.1458f, 3.1458f, 0.0f, 1.0f);//7
		_Points[17] = vec4(3.1458f, - 3.1458f, 0.0f, 1.0f);//3
		_Colors = new vec4[_nVtx];
		for (int i = 0; i < _nVtx; i++) _Colors[i] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case 3://player
		_nVtx = 9;
		_Points = new vec4[_nVtx];

		_Points[0] = vec4(3.0462f, -2.3839f, 0.0f, 1.0f);
		_Points[1] = vec4(-0.0000f, 4.7240f, 0.0f, 1.0f);
		_Points[2] = vec4(-3.0462f, -2.3839f, 0.0f, 1.0f);
		_Points[3] = vec4(1.0154f, - 2.3839f, 1.0f, 1.0f);
		_Points[4] = vec4(0.0000f, 4.7240f, 1.0f, 1.0f);
		_Points[5] = vec4(-1.0154f, - 2.3839f, 1.0f, 1.0f);
		_Points[6] = vec4(-1.0154f, - 2.3839f, 1.0f, 1.0f);
		_Points[7] = vec4(0.0000f, - 4.4147f, 1.0f, 1.0f);
		_Points[8] = vec4(1.0154f, - 2.3839f, 1.0f, 1.0f);
		_Colors = new vec4[_nVtx];
		for (int i = 0; i < 3; i++) _Colors[i] = vec4(0.9411f, 0.3294f, 0.309f, 1.0f);
		for (int i = 3; i < _nVtx; i++) _Colors[i] = vec4(0.9529f, 0.9529f, 0.9529f, 1.0f);
		break;
	}
	

	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;
}


void CCQuad::draw()
{
	glUseProgram(_uiProgram);
	glBindVertexArray(_uiVao);
	if (_bUpdateMV) {
		_mxMVFinal = _mxView * _mxTRS;
		_bUpdateMV = false;
	}
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);

	if (_bUpdateProj) {
		glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);
		_bUpdateProj = false;
	}
	glDrawArrays(GL_TRIANGLES, 0, _nVtx);
}

void CCQuad::drawW()
{
	glBindVertexArray(_uiVao);

	if (_bUpdateMV) {
		_mxMVFinal = _mxView * _mxTRS;
		_bUpdateMV = false;
	}

	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);
	if (_bUpdateProj) {
		glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);
		_bUpdateProj = false;
	}
	glDrawArrays(GL_TRIANGLES, 0, _nVtx);
}
