#include "header/Angel.h"
#include "Common/CPlayer.h"
#include "Common/CBG.h"
#include "Common/CMob.h"
#include "Common/CBoss.h"
#include <stdlib.h>
#include <vector>
using namespace std;

#define SPACE_KEY 32
#define SCREENX 500
#define SCREENY 800
#define HALFX (SCREENX/2) 
#define HALFY (SCREENY/2) 
#define PLAYER_BULLET 0.45f
#define MOB_BULLET 1.0f
#define MOB_NUM 1

CPlayer *g_pPlayer;
CBG *g_pBG;
CMob *g_pMob[MOB_NUM];
CBoss *g_pBoss;

GLfloat g_fPTx = 0;		//玩家座標
mat4  mxPT, mxPS;
float _fcount = 0;		//玩家子彈間隔時間
float _fMcount = 0;

bool _Alive = true;
bool _MobAlive[MOB_NUM];
bool _BossAlive = false;

int _MobSurvive = MOB_NUM;
int _life = 4;

//----------------------------------------------------------------------------
// 函式的原型宣告
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
	g_pBoss = new CBoss;

	glClearColor(0.0509, 0.0235, 0.1882, 1.0); // black background
}

void Collision(float delta)
{
	mat4 mxPlayerPos, mxPBulletPos, mxMobPos[MOB_NUM], mxMBulletPos[MOB_NUM], mxBossPos, mxBBulletPos;
	float fPlayer_x, fPlayer_y;			//player position
	float fPBullet_x, fPBullet_y;		//player bullet position
	float fMob_x[MOB_NUM], fMob_y[MOB_NUM];				//mob position
	float fMBullet_x[MOB_NUM], fMBullet_y[MOB_NUM];		//mob bullet position
	float fBoss_x, fBoss_y;				//boss position
	float fBBullet_x, fBBullet_y;		//boss bullet position

	if (_Alive) {		//玩家存在
		mxPlayerPos = g_pPlayer->GetTranslateMatrix();			//取得玩家位置
		fPlayer_x = mxPlayerPos._m[0][3];
		fPlayer_y = mxPlayerPos._m[1][3];
		mxPBulletPos = g_pPlayer->GetBulletTranslateMatrix();	//取得玩家子彈位置
		fPBullet_x = mxPBulletPos._m[0][3];
		fPBullet_y = mxPBulletPos._m[1][3];
	}

	for (int i = 0; i < MOB_NUM; i++)
	{
		if (_MobAlive[i]) {
			mxMobPos[i] = g_pMob[i]->GetTranslateMatrix();
			fMob_x[i] = mxMobPos[i]._m[0][3];
			fMob_y[i] = mxMobPos[i]._m[1][3];
			mxMBulletPos[i] = g_pMob[i]->GetBulletTranslateMatrix();
			fMBullet_x[i] = mxMBulletPos[i]._m[0][3];
			fMBullet_y[i] = mxMBulletPos[i]._m[1][3];
			//玩家子彈擊中小怪
			if (fPBullet_y > fMob_y[i] - 1.0f && fPBullet_y < fMob_y[i] + 1.0f &&
				fPBullet_x < fMob_x[i] + 1.0f && fPBullet_x > fMob_x[i] - 1.0f) {
				g_pPlayer->DeleteBullet();
				_MobSurvive -= 1;
				cout << _MobSurvive << " mobs are alived." << endl;
				_MobAlive[i] = false;
			}
			//離開視窗死亡
			if (_MobAlive[i] && fMob_y[i] < -7.f)
			{
				_MobAlive[i] = false;
				_MobSurvive -= 1;
				cout << _MobSurvive << " mobs are alived." << endl;
			}
			//小怪子彈擊中玩家
			if (fMBullet_y[i] < PLAYER_Y_AXIS + 1.5f && fMBullet_y[i] > PLAYER_Y_AXIS +1.3f &&
				fMBullet_x[i] < g_fPTx + 1.5f && fMBullet_x[i] > g_fPTx - 1.5f) {						//小怪子彈碰撞玩家
				g_pMob[i]->DeleteBullet();
				g_pPlayer->AttackedByEnemies(delta);
			}
			if (_MobSurvive == 0)_BossAlive = true;
		}
	}

	if (_BossAlive)
	{
		mxBossPos = g_pBoss->GetTranslateMatrix();
		fBoss_x = mxBossPos._m[0][3];
		fBoss_y = mxBossPos._m[1][3];
		mxBBulletPos = g_pBoss->GetBulletTranslateMatrix();
		fBBullet_x = mxBBulletPos._m[0][3];
		fBBullet_y = mxBBulletPos._m[1][3];
		//玩家子彈擊中BOSS
		if (fPBullet_y > fBoss_y - 1.0f && fPBullet_y < fBoss_y + 1.0f&&
			fPBullet_x < fBoss_x + 1.0f && fPBullet_x > fBoss_x - 1.0f) {
			cout << "hit boss" << endl;
		}
	}
	
}

//----------------------------------------------------------------------------
void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window

	g_pBG->GL_Draw();
	if (_Alive)
	{
		g_pPlayer->GL_Draw();
		g_pPlayer->GL_DrawMask();
	}
	for (int i = 0; i < MOB_NUM; i++)
	{
		if (_MobAlive[i])g_pMob[i]->GL_Draw();
	}
	if (_BossAlive)
	{
		g_pBoss->GL_Draw();
	}
	
	glutSwapBuffers();	// 交換 Frame Buffer
}

void onFrameMove(float delta)
{
	//玩家子彈
	g_pPlayer->ShootBullet(delta, g_fPTx);	//發射子彈
	//小怪子彈
	for (int i = 0; i < MOB_NUM; i++)
	{
		g_pMob[i]->ShootBullet(delta);
	}
	g_pBoss->ShootBullet(delta);

	g_pPlayer->UpdateMatrix(delta);
	g_pBG->UpdateMatrix(delta);
	for (int i = 0; i < MOB_NUM; i++)
	{
		g_pMob[i]->UpdateMatrix(delta);
	}
	g_pBoss->UpdateMatrix(delta);
	

	Collision(delta);

	GL_Display();
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
		if (state == GLUT_DOWN)
		{
			
		}
		break;
	case GLUT_MIDDLE_BUTTON:  // 目前按下的是滑鼠中鍵 
		if (state == GLUT_DOWN);
		break;
	case GLUT_RIGHT_BUTTON:   // 目前按下的是滑鼠右鍵
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
	mxPS = Scale(fPlayerScale, fPlayerScale, fPlayerScale);	//大小
	g_pPlayer->GL_SetTRSMatrix(mxPT * mxPS);
	g_pPlayer->GL_SetTranslatMatrix(mxPT);
	
}
// The motion callback for a window is called when the mouse moves within the window while one or more mouse buttons are pressed.
void Win_MouseMotion(int x, int y) {
	float fPlayerScale;
	g_fPTx = 5.0f * (x - HALFX) / (HALFX);
	mxPT = Translate(g_fPTx, PLAYER_Y_AXIS, 0);
	fPlayerScale = g_pPlayer->GetPlayerScale();
	mxPS = Scale(fPlayerScale, fPlayerScale, fPlayerScale);	//大小
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
	glutKeyboardFunc(Win_Keyboard);	// 處理 ASCII 按鍵如 A、a、ESC 鍵...等等
	glutSpecialFunc(Win_SpecialKeyboard);	// 處理 NON-ASCII 按鍵如 F1、Home、方向鍵...等等
	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);

	glutMainLoop();
	return 0;
}
