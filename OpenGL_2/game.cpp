#include "header/Angel.h"
#include "Common/CPlayer.h"
#include "Common/CBG.h"
#include "Common/CMob.h"
#include <stdlib.h>
#include <vector>
using namespace std;

#define SPACE_KEY 32
#define SCREENX 500
#define SCREENY 800
#define HALFX (SCREENX/2) 
#define HALFY (SCREENY/2) 
#define NEXT_BULLET_DELAY 0.45f
#define MOB_NUM 10

CPlayer *g_pPlayer;
CBG *g_pBG;
CMob *g_pMob[MOB_NUM];

GLfloat g_fPTx = 0;		//���a�y��
mat4  mxPT, mxPS;
float _fcount = 0;		//���a�l�u���j�ɶ�

bool _Alive = true;
bool _MobAlive[MOB_NUM];
bool _BossAlive = false;

//----------------------------------------------------------------------------
// �禡���쫬�ŧi
void IdleProcess();
void Collision(float delta);

void init(void)
{
	int RandomColor = rand() % 3;

	g_pBG = new CBG;
	g_pPlayer = new CPlayer;
	for (int i = 0; i < MOB_NUM; i++)
	{
		g_pMob[i] = new CMob();
		_MobAlive[i] = true;
	}

	glClearColor(0.0, 0.0, 0.0, 1.0); // black background
}

void Collision(float delta)
{
	for (int i = 0; i < MOB_NUM; i++)
	{
		if (!_MobAlive[i])
		{
			_BossAlive = true;
		}
	}
}

//----------------------------------------------------------------------------
void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window

	g_pBG->GL_Draw();
	if(_Alive)g_pPlayer->GL_Draw();
	g_pPlayer->GL_DrawMask();
	for (int i = 0; i < MOB_NUM; i++)
	{
		if (_MobAlive[i])g_pMob[i]->GL_Draw();
	}
	glutSwapBuffers();	// �洫 Frame Buffer
}

void onFrameMove(float delta)
{
	//���a�l�u
	_fcount += delta;
	if (_fcount < 0.8f) 
	{
		g_pPlayer->ShootBullet(delta, g_fPTx);	//�o�g�l�u
	}
	else {
		g_pPlayer->NextBullet(g_fPTx);	//�U�@�Ӥl�u
		_fcount -= 0.8f;
	}

	g_pPlayer->UpdateMatrix(delta);
	g_pBG->UpdateMatrix(delta);
	for (int i = 0; i < MOB_NUM; i++)g_pMob[i]->UpdateMatrix(delta);

	Collision(delta);

	GL_Display();
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // �ثe���U���O�ƹ�����
		if (state == GLUT_DOWN)
		{
			for (int i = 0; i < MOB_NUM; i++)
			{
				_MobAlive[i] = !_MobAlive[i];
			}
		}
		break;
	case GLUT_MIDDLE_BUTTON:  // �ثe���U���O�ƹ����� 
		if (state == GLUT_DOWN);
		break;
	case GLUT_RIGHT_BUTTON:   // �ثe���U���O�ƹ��k��
		if (state == GLUT_DOWN);
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------
// The passive motion callback for a window is called when the mouse moves within the window while no mouse buttons are pressed.
void Win_PassiveMotion(int x, int y) {
	float fPlayerScale;
	g_fPTx = 5.0f * (x - HALFX) / (HALFX);
	mxPT = Translate(g_fPTx, PLAYER_Y_AXIS, 0);
	fPlayerScale = g_pPlayer->GetPlayerScale();
	mxPS = Scale(fPlayerScale, fPlayerScale, fPlayerScale);	//�j�p
	g_pPlayer->GL_SetTRSMatrix(mxPT * mxPS);
	g_pPlayer->GL_SetTranslatMatrix(mxPT);
	
}
// The motion callback for a window is called when the mouse moves within the window while one or more mouse buttons are pressed.
void Win_MouseMotion(int x, int y) {
	float fPlayerScale;
	g_fPTx = 5.0f * (x - HALFX) / (HALFX);
	mxPT = Translate(g_fPTx, PLAYER_Y_AXIS, 0);
	fPlayerScale = g_pPlayer->GetPlayerScale();
	mxPS = Scale(fPlayerScale, fPlayerScale, fPlayerScale);	//�j�p
	g_pPlayer->GL_SetTRSMatrix(mxPT * mxPS);
	g_pPlayer->GL_SetTranslatMatrix(mxPT);
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
		if (g_pBG != nullptr) delete g_pBG;
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
	glutKeyboardFunc(Win_Keyboard);	// �B�z ASCII ����p A�Ba�BESC ��...����
	glutSpecialFunc(Win_SpecialKeyboard);	// �B�z NON-ASCII ����p F1�BHome�B��V��...����
	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);

	glutMainLoop();
	return 0;
}
