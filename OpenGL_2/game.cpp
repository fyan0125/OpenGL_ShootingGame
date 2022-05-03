#include "header/Angel.h"
#include "Common/CPlayer.h"
#include <stdlib.h>
#include <vector>
using namespace std;

#define SPACE_KEY 32
#define SCREENX 500
#define SCREENY 700
#define HALFX (SCREENX/2) 
#define HALFY (SCREENY/2) 
#define Update_Per_Second 60
#define NEXT_BULLET_DELAY 0.45f

CPlayer *g_pPlayer;

float  g_fQuadT[3];
mat4  mxRT;

GLfloat g_fPTx = 0, g_fTy = 0;

bool shooting = false;

float _fcount = 0;

//----------------------------------------------------------------------------
// ㄧΑ
void IdleProcess();

void init(void)
{
	
	vec2 position = vec2(0, 0);

	g_pPlayer = new CPlayer;

	glClearColor(0.0, 0.0, 0.0, 1.0); // black background
}

//----------------------------------------------------------------------------
void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window

	g_pPlayer->GL_Draw();
	g_pPlayer->GL_DrawDefense();

	glutSwapBuffers();	// ユ传 Frame Buffer
}

void onFrameMove(float delta)
{
	//產紆
	_fcount += delta;
	if (_fcount < 0.8f) g_pPlayer->ShootBullet(delta, g_fPTx);	//祇甮紆
	else {
		if (!shooting) {
			g_pPlayer->NextBullet(g_fPTx);	//紆
			_fcount -= 0.8f;
		}
		else _fcount = 0;			//籛Ч穝璸计
	}

	g_pPlayer->UpdateMatrix(delta);

	GL_Display();
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // ヘ玡琌菲公オ龄
		if (state == GLUT_DOWN)
		{
		}
		break;
	case GLUT_MIDDLE_BUTTON:  // ヘ玡琌菲公い龄 
		if (state == GLUT_DOWN);
		break;
	case GLUT_RIGHT_BUTTON:   // ヘ玡琌菲公龄
		if (state == GLUT_DOWN);
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------
// The passive motion callback for a window is called when the mouse moves within the window while no mouse buttons are pressed.
void Win_PassiveMotion(int x, int y) {
	g_fPTx = 12.0f * (x - HALFX) / (HALFX);
	mxRT = Translate(g_fPTx, PLAYER_Y_AXIS, 0);
	g_pPlayer->GL_SetTRSMatrix(mxRT);
	g_pPlayer->GL_SetTranslatMatrix(mxRT);
	
}
// The motion callback for a window is called when the mouse moves within the window while one or more mouse buttons are pressed.
void Win_MouseMotion(int x, int y) {
	g_fPTx = 12.0f * (x - HALFX) / (HALFX);
	mxRT = Translate(g_fPTx, PLAYER_Y_AXIS, 0);
	g_pPlayer->GL_SetTRSMatrix(mxRT);
	g_pPlayer->GL_SetTranslatMatrix(mxRT);
}
//----------------------------------------------------------------------------
void Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case  SPACE_KEY:
		break;
	case 68: // D key
	case 100: // d key
		break;
	case 82: // R key
	case 114: // r key
		break;
	case 033:
		if (g_pPlayer != nullptr) delete g_pPlayer;
		exit(EXIT_SUCCESS);
		break;
	}
}
//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		break;
	}
}
//----------------------------------------------------------------------------
void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
}

//----------------------------------------------------------------------------

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(SCREENX, SCREENY);

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Game");


	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutMouseFunc(Win_Mouse);
	glutMotionFunc(Win_MouseMotion);
	glutPassiveMotionFunc(Win_PassiveMotion);
	glutKeyboardFunc(Win_Keyboard);	// 矪瞶 ASCII 龄 AaESC 龄...单单
	glutSpecialFunc(Win_SpecialKeyboard);	// 矪瞶 NON-ASCII 龄 F1Homeよ龄...单单
	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);

	glutMainLoop();
	return 0;
}
