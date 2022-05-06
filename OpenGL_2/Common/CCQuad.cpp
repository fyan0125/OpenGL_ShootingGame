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
	case 4://boss
		_nVtx = 57;
		_Points = new vec4[_nVtx];

		_Points[0] = vec4(1.3847f, 1.8627f, 0.0f, 1.0f);//14
		_Points[1] = vec4(1.3847f, - 1.0603f, 0.0f, 1.0f);//15
		_Points[2] = vec4(3.8799f, 1.4451f, 0.0f, 1.0f);//16
		_Points[3] = vec4(3.8799f, 3.9505f, 0.0f, 1.0f);//17
		_Points[4] = vec4(1.3847f, 1.8627f, 0.0f, 1.0f);//14
		_Points[5] = vec4(3.8799f, 1.4451f, 0.0f, 1.0f);//16
		_Points[6] = vec4(4.5928f, 3.9505f, 0.0f, 1.0f);//18
		_Points[7] = vec4(3.8799f, 3.9505f, 0.0f, 1.0f);//17
		_Points[8] = vec4(3.8799f, 1.4451f, 0.0f, 1.0f);//16
		_Points[9] = vec4(4.5928f, - 2.3130f, 0.0f, 1.0f);//19
		_Points[10] = vec4(4.5928f, 3.9505f, 0.0f, 1.0f);//18
		_Points[11] = vec4(3.8799f, 1.4451f, 0.0f, 1.0f);//16
		_Points[12] = vec4(4.5928f, - 2.3130f, 0.0f, 1.0f);//19
		_Points[13] = vec4(3.8799f, 1.4451f, 0.0f, 1.0f);//16
		_Points[14] = vec4(3.8799f, - 2.3130f, 0.0f, 1.0f);//20

		_Points[15] = vec4(-3.8738f, 1.4451f, 0.0f, 1.0f);//21
		_Points[16] = vec4(-1.3786f, - 1.0603f, 0.0f, 1.0f);//22
		_Points[17] = vec4(-1.3786f, 1.8627f, 0.0f, 1.0f);//23
		_Points[18] = vec4(-3.8738f, 1.4451f, 0.0f, 1.0f);//21
		_Points[19] = vec4(-1.3786f, 1.8627f, 0.0f, 1.0f);//23
		_Points[20] = vec4(-3.8738f, 3.9505f, 0.0f, 1.0f);//24
		_Points[21] = vec4(-3.8738f, 1.4451f, 0.0f, 1.0f);//21
		_Points[22] = vec4(-3.8738f, 3.9505f, 0.0f, 1.0f);//24
		_Points[23] = vec4(-4.5867f, 3.9505f, 0.0f, 1.0f);//25
		_Points[24] = vec4(-3.8738f, 1.4451f, 0.0f, 1.0f);//21
		_Points[25] = vec4(-4.5867f, 3.9505f, 0.0f, 1.0f);//25
		_Points[26] = vec4(-4.5867f, - 2.3130f, 0.0f, 1.0f);//26
		_Points[27] = vec4(-3.8738f, - 2.3130f, 0.0f, 1.0f);//27
		_Points[28] = vec4(-3.8738f, 1.4451f, 0.0f, 1.0f);//21
		_Points[29] = vec4(-4.5867f, - 2.3130f, 0.0f, 1.0f);//26

		_Points[30] = vec4(1.3794f, - 1.8954f, 1.0f, 1.0f);//1
		_Points[31] = vec4(1.3794f, 2.6978f, 1.0f, 1.0f);//2
		_Points[32] = vec4(0.9209f, 2.6978f, 1.0f, 1.0f);//3
		_Points[33] = vec4(-1.3715f, - 1.8954f, 1.0f, 1.0f);//4
		_Points[34] = vec4(0.0040f, - 4.4008f, 1.0f, 1.0f);//5
		_Points[35] = vec4(1.3794f, - 1.8954f, 1.0f, 1.0f);//1
		_Points[36] = vec4(-1.3715f, -1.8954f, 1.0f, 1.0f);//4
		_Points[37] = vec4(1.3794f, -1.8954f, 1.0f, 1.0f);//1
		_Points[38] = vec4(0.9209f, 2.6978f, 1.0f, 1.0f);//3
		_Points[39] = vec4(-0.9130f, 2.6978f, 1.0f, 1.0f);//6
		_Points[40] = vec4(-1.3715f, 2.6978f, 1.0f, 1.0f);//7
		_Points[41] = vec4(-1.3715f, -1.8954f, 1.0f, 1.0f);//4
		_Points[42] = vec4(-0.9130f, 2.6978f, 1.0f, 1.0f);//6
		_Points[43] = vec4(-1.3715f, -1.8954f, 1.0f, 1.0f);//4
		_Points[44] = vec4(0.9209f, 2.6978f, 1.0f, 1.0f);//3
		_Points[45] = vec4(-0.4545f, 3.5329f, 1.0f, 1.0f);//8
		_Points[46] = vec4(-0.9130f, 2.6978f, 1.0f, 1.0f);//6
		_Points[47] = vec4(0.9209f, 2.6978f, 1.0f, 1.0f);//3
		_Points[48] = vec4(0.4625f, 3.5329f, 1.0f, 1.0f);//9
		_Points[49] = vec4(-0.4545f, 3.5329f, 1.0f, 1.0f);//8
		_Points[50] = vec4(0.9209f, 2.6978f, 1.0f, 1.0f);//3

		_Points[51] = vec4(0.9209f, -0.6427f, 2.0f, 1.0f);//10
		_Points[52] = vec4(-0.9130f, -0.6427f, 2.0f, 1.0f);//11
		_Points[53] = vec4(-0.6838f, -1.8954f, 2.0f, 1.0f);//12
		_Points[54] = vec4(0.9209f, -0.6427f, 2.0f, 1.0f);//10
		_Points[55] = vec4(-0.6838f, -1.8954f, 2.0f, 1.0f);//12
		_Points[56] = vec4(0.6917f, - 1.8954f, 2.0f, 1.0f);//13

		
		_Colors = new vec4[_nVtx];
		for (int i = 0; i < 30; i++) _Colors[i] = vec4(0.9529f, 0.9529f, 0.9529f, 1.0f);
		for (int i = 30; i < 51; i++) _Colors[i] = vec4(0.9803f, 0.9803f, 0.9803f, 1.0f);
		for (int i = 51; i < _nVtx; i++) _Colors[i] = vec4(0.2f, 0.6f, 0.5372f, 1.0f);
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
