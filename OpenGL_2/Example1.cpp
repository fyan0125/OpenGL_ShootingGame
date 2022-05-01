#include "header/Angel.h"
#include "Common/CQuad.h"
#include "Header/glfw3.h"
#include <stdlib.h>
#include <vector>
using namespace std;

#define SPACE_KEY 32
#define SCREENX 500
#define SCREENY 800
#define HALFX (SCREENX/2) 
#define HALFY (SCREENY/2) 
#define Update_Per_Second 60

CQuad *g_pQuad;	// 宣告 Quad 指標物件，結束時記得釋放
vector<CQuad *> *ballsAry;
vector<CQuad *> *enemyAry;

// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;

float  g_fQuadT[3];
mat4  mxRT;

GLfloat g_fTx = 0, g_fTy = 0;

bool shooting = false;
int mouseX;
int mouseY;

//----------------------------------------------------------------------------
// 函式的原型宣告
void IdleProcess();

void init( void )
{
	vec4 vColor = vec4(1, 0, 0, 1);
	vec2 position = vec2(0, 0);

	// 必須在 glewInit(); 執行完後,在執行物件實體的取得
	g_pQuad = new CQuad(position);
	g_pQuad->setColor(vColor);
	
	//  產生 projection 矩陣，此處為產生正投影矩陣
    g_mxProjection = Ortho(-12.0f, 12.0f, -12.0f, 12.0f, -12.0f, 12.0f);
	g_pQuad->setShader(g_mxModelView, g_mxProjection);

	ballsAry = new vector<CQuad *>;
	enemyAry = new vector<CQuad *>;

    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background
}
//----------------------------------------------------------------------------
void Shoot(int x, int y)
{
	mat4 mxGT, mxT;
	g_fTx = 20.0f*(x - HALFX) / (HALFX);
	g_fTy = -30.0f*(y - HALFY) / (HALFY);
	vec2 position = vec2(g_fTx, g_fTy);

	CQuad *ball = new CQuad(position);
	vec4 vColor = vec4(1, 0, 1, 1);
	ball->setColor(vColor);
	g_mxProjection = Ortho(-20.0f, 20.0f, -30.0f, 30.0f, -20.0f, 20.0f);
	ball->setShader(g_mxModelView, g_mxProjection);
	ball->setVelocity(vec2(0.0f, 0.01f));
	ballsAry->push_back(ball);
}
//----------------------------------------------------------------------------
void Enemy()
{
	int locationX = rand() % (unsigned int)SCREENX;
	vec2 position = vec2(locationX, 20);
	CQuad *newEnemy = new CQuad(position);
	newEnemy->setColor(vec4(1, 1, 0, 1));
	g_mxProjection = Ortho(-20.0f, 20.0f, -20.0f, 20.0f, -20.0f, 20.0f);
	newEnemy->setShader(g_mxModelView, g_mxProjection);
	newEnemy->setVelocity(vec2(0.0f, -0.01f));
	enemyAry->push_back(newEnemy);
}

bool checkForCollision(CQuad *a, CQuad *b)
{
	return !(
		a->getPosition().x <= b->getPosition().x
		);
}

//----------------------------------------------------------------------------
void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window

	g_pQuad->draw();//draw player

	//draw bullet
	for (vector<CQuad *>::iterator spriteIterator = ballsAry->begin();
		spriteIterator != ballsAry->end(); spriteIterator++)
	{
		(*spriteIterator)->draw();
	}

	//draw enemy
	for (vector<CQuad *>::iterator spriteIterator = enemyAry->begin();
		spriteIterator != enemyAry->end(); spriteIterator++)
	{
		(*spriteIterator)->draw();
	}

	glutSwapBuffers();	// 交換 Frame Buffer
}

void onFrameMove(float delta)
{
	//按下滑鼠發射子彈
	if (shooting == true)Shoot(mouseX, mouseY);
	
	vector<vector<CQuad *>::iterator> deleteArray;

	for (vector<CQuad *>::iterator spriteIteratorEnemy = enemyAry->begin();
		spriteIteratorEnemy != enemyAry->end(); spriteIteratorEnemy++)
	{
		/*if (checkForCollision(*spriteIteratorEnemy, g_pQuad))
		{
			deleteArray.push_back(spriteIteratorEnemy);
		}
		for (vector<CQuad *>::iterator spriteIteratorBullet = ballsAry->begin();
			spriteIteratorBullet != ballsAry->end(); spriteIteratorBullet++)
		{
			if (checkForCollision(*spriteIteratorEnemy, *spriteIteratorBullet))
			{
				deleteArray.push_back(spriteIteratorBullet);
				deleteArray.push_back(spriteIteratorEnemy);
			}
		}*/
		if ((*spriteIteratorEnemy)->getPosition().y < -20)
		{
			deleteArray.push_back(spriteIteratorEnemy);
		}
	}

	//刪掉離開視窗的子彈
	for (vector<CQuad *>::iterator spriteIterator = ballsAry->begin();
		spriteIterator != ballsAry->end(); spriteIterator++)
	{
		if ((*spriteIterator)->getPosition().y > 30)
		{
			deleteArray.push_back(spriteIterator);
		}
	}

	for (vector<vector<CQuad *>::iterator>::iterator deleteIterator = deleteArray.begin();
		deleteIterator != deleteArray.end(); deleteIterator++)
	{
		if ((**deleteIterator)->getVelocity().x > 0)ballsAry->erase(*deleteIterator);
		else enemyAry->erase(*deleteIterator);
	}

	//子彈隨時間移動
	for (vector<CQuad *>::iterator spriteIterator = ballsAry->begin();
		spriteIterator != ballsAry->end(); spriteIterator++)
	{
		(*spriteIterator)->update();
	}

	//出現敵人
	static int updates = 0;
	if (updates >= 60) {
		Enemy();
		updates = 0;
	}
	updates++;

	//敵人隨時間移動
	for (vector<CQuad *>::iterator spriteIterator = enemyAry->begin();
		spriteIterator != enemyAry->end(); spriteIterator++)
	{
		(*spriteIterator)->update();
	}

	GL_Display();
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
		if (state == GLUT_DOWN)
		{
			shooting = true;
			mouseX = x;
			mouseY = y;
		}else shooting = false;
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
	mat4 mxGT, mxT;

	g_fTx = 12.0f*(x - HALFX) / (HALFX);
	g_fTy = -12.0f*(y - HALFY) / (HALFY);
	mxGT = Translate(g_fTx, g_fTy, 0);

	mxT = Translate(g_fQuadT[0], g_fQuadT[1], g_fQuadT[2]);
	mxRT = mxGT*mxT;
	g_pQuad->setTRSMatrix(mxRT);
}
// The motion callback for a window is called when the mouse moves within the window while one or more mouse buttons are pressed.
void Win_MouseMotion(int x, int y) {
	mat4 mxGT, mxT;

	g_fTx = 12.0f*(x - HALFX) / (HALFX);
	g_fTy = -12.0f*(y - HALFY) / (HALFY);
	mxGT = Translate(g_fTx, g_fTy, 0);

	mxT = Translate(g_fQuadT[0], g_fQuadT[1], g_fQuadT[2]);
	mxRT = mxGT*mxT;
	g_pQuad->setTRSMatrix(mxRT);
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
		delete g_pQuad;
		delete ballsAry;
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

int main( int argc, char **argv )
{
    
	glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize(SCREENX, SCREENY);

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion( 3, 2 );
	glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow( "Game" );
	

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE; 
    glewInit();  

    init();

	glutMouseFunc(Win_Mouse);
	glutMotionFunc(Win_MouseMotion);
	glutPassiveMotionFunc(Win_PassiveMotion);
    glutKeyboardFunc( Win_Keyboard );	// 處理 ASCII 按鍵如 A、a、ESC 鍵...等等
	glutSpecialFunc( Win_SpecialKeyboard);	// 處理 NON-ASCII 按鍵如 F1、Home、方向鍵...等等
    glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	
    glutMainLoop();
    return 0;
}
