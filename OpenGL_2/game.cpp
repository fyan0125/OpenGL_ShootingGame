//(8 % ) 操控與背景部分
//		V(1 % ) 滑鼠可以控制戰鬥機的左右移動
//		V(1 % ) 戰鬥機傭有防禦裝置，並以父子關係方式呈現
//		V(1 % ) 可以發射飛彈
//		V(3 % ) 能提供連續發射(LINKED LIST，自己撰寫，使用STL 2分)
//		V(2 % )  能產生有速度感的背景物件，或是其他裝飾性的物件
//(11 % ) 敵人部分
//		V(2 % )  有至少三種以上不同外形的敵人(不同的顏色)，基本的四方型不算在內
//		V(3 % ) 以物件導向的多型來控制所有的敵人
//		V(1 % )  敵人可以不斷的產生，而且具有不同的顏色
//		V(1 % )  敵人能隨機朝向玩家發射子彈攻擊
//		V(2 % )  戰鬥機發射的子彈可以打到敵人，而且敵人會消失
//		V(2 % )  有 BOSS 級的敵人，且至會根據被攻擊的多寡至少三種不同的狀態(外型改變或攻擊方式)可以切換
//(4 % ) (玩家部分)
//		V(2 % )  能判斷玩家是否被打中 並做出合理的反應
//		V(2 % )  玩家的船艦至少有三種狀態(外型改變)，且有提供玩家的船艦可改變狀態的機制
//(8 % ) 其他你覺得可以展示的技術，包含物理或是數學的運算
//		(2 % )提供階層式動態控制，並以時間為基礎進行動態的展示(如: OpenGL_2 的 Example4 ，以自動產生的軌跡去控制相關的物件運動)
//		(2 % )發射導向飛彈攻擊移動的 Boss
//		敵人被打到有其他的效果
//		戰鬥機被打到時有其他的效果
//		背景除了速度感物件外，有其他的效果
#include "header/Angel.h"
#include "Common/CPlayer.h"
#include "Common/CBG.h"
#include "Common/CMob.h"
#include "Common/CBoss.h"
#include "Common/CHealth.h"
#include <stdlib.h>
#include <vector>
using namespace std;

#define SPACE_KEY 32
#define SCREENX 500
#define SCREENY 800
#define HALFX (SCREENX/2) 
#define HALFY (SCREENY/2) 
#define MOB_NUM 15

CPlayer *g_pPlayer;
CBG *g_pBG;
CMob *g_pMob[MOB_NUM];
CBoss *g_pBoss;
CHealth *g_pBossHP;;

GLfloat g_fPTx = 0;		//玩家座標
mat4  mxPT, mxPS;

bool _Alive = true;
bool _MobAlive[MOB_NUM];
bool _BossAlive = false;

int _MobSurvive = MOB_NUM;
float g_fBossHPT[3] = { 0.0f, 6.95f , 0.0f };
mat4 g_mxBossHPT;
int _MobStatus = 1;
int _BossStatus = 1;

int _killedMob = 0;
int _playerStatus = 1;
float playerScale = 0.1f;
int _playerBulletTime = 1000;

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
	g_pBossHP = new CHealth;

	glClearColor(0.0509, 0.0235, 0.1882, 1.0);
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
		if (_killedMob >= 10)
		{
			_playerStatus = 3;
			playerScale = 0.15f;
			g_pPlayer->UpdateScale(playerScale);
		}
		else if (_killedMob >= 5)
		{
			_playerStatus = 2;
			_playerBulletTime = 500;
			playerScale = 0.2f;
			g_pPlayer->UpdateScale(playerScale);
		}
		if (g_pPlayer->GetMaskNum() < 0)_Alive = false;
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
			if (fMob_y[i] < 7.0f)
			{
				if (fPBullet_y > fMob_y[i] - 1.0f && fPBullet_y < fMob_y[i] + 1.0f &&
					fPBullet_x < fMob_x[i] + 1.0f && fPBullet_x > fMob_x[i] - 1.0f) {
					g_pPlayer->DeleteBullet();
					_MobSurvive -= 1;
					cout << _MobSurvive << " mobs are alived." << endl;
					_MobAlive[i] = false;
					_killedMob += 1;
				}
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
			g_pPlayer->DeleteBullet();
			g_fBossHPT[0] -= delta * 5;
			g_mxBossHPT = Translate(g_fBossHPT[0], g_fBossHPT[1], g_fBossHPT[2]);
			g_pBossHP->GL_SetTranslatMatrix(g_mxBossHPT);
			if (g_fBossHPT[0] >= -3.33f)_BossStatus = 1;
			else if (g_fBossHPT[0] >= -6.66f)_BossStatus = 2;
			else if (g_fBossHPT[0] >= -10.0f)_BossStatus = 3;
			else if (g_fBossHPT[0] < -10.0f)_BossAlive = false;
		}
		//boss子彈擊中玩家
		if (fBBullet_y < PLAYER_Y_AXIS + 1.5f && fBBullet_y > PLAYER_Y_AXIS - 1.5f &&
			fBBullet_x < g_fPTx + 1.5f && fBBullet_x > g_fPTx - 1.5f) {
			g_pBoss->DeleteBullet();
			g_pPlayer->AttackedByEnemies(delta);
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
	for (int i = 0; i < MOB_NUM; i++)if (_MobAlive[i])g_pMob[i]->GL_Draw();
	if (_BossAlive)
	{
		g_pBoss->GL_Draw();
		g_pBossHP->GL_Draw();
	}
	
	glutSwapBuffers();	// 交換 Frame Buffer
}

void onFrameMove(float delta)
{
	//玩家子彈
	if (_playerStatus == 3)
	{
		g_pPlayer->ShootBullet(delta, g_fPTx -0.3f, _playerBulletTime);	//發射子彈
		g_pPlayer->ShootBullet2(delta, g_fPTx + 0.3f, _playerBulletTime);	//發射子彈
	}
	else g_pPlayer->ShootBullet(delta, g_fPTx, _playerBulletTime);	//發射子彈
	//小怪子彈
	for (int i = 0; i < MOB_NUM; i++)g_pMob[i]->ShootBullet(delta);
	g_pBoss->ShootBullet(delta);

	g_pPlayer->UpdateMatrix(delta);
	g_pBG->UpdateMatrix(delta);
	for (int i = 0; i < MOB_NUM; i++)g_pMob[i]->UpdateMatrix(delta, _MobStatus);
	g_pBoss->UpdateMatrix(delta, _BossStatus);
	g_pBossHP->UpdateMatrix(delta);
	

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
		for (int i = 0; i < MOB_NUM; i++) {
			if (g_pMob[i] != nullptr) delete g_pMob[i];
		}
		if (g_pBoss != nullptr) delete g_pBoss;
		if (g_pBossHP != nullptr) delete g_pBossHP;
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
