#include "header/Angel.h"
#include "Common/CQuad.h"

#define SPACE_KEY 32
#define SCREEN_SIZE 800
#define HALF_SIZE (SCREEN_SIZE/2) 

// 必須在 glewInit(); 執行完後,在執行物件實體的取得
CQuad *g_pQuad;	// 宣告 Quad 指標物件，結束時記得釋放

// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;

GLfloat g_fTx = 0, g_fTy = 0;

//----------------------------------------------------------------------------
// 函式的原型宣告
void IdleProcess();

void init(void)
{
	vec4 vColor = vec4(1, 0, 0, 1);

	// 必須在 glewInit(); 執行完後,在執行物件實體的取得
	g_pQuad = new CQuad;
	g_pQuad->setColor(vColor);

	//  產生 projection 矩陣，此處為產生正投影矩陣
	g_mxProjection = Ortho(-12.0f, 12.0f, -12.0f, 12.0f, -2.0f, 2.0f);
	g_pQuad->setShader(g_mxModelView, g_mxProjection);

	glClearColor(0.0, 0.0, 0.0, 1.0); // black background
}
//----------------------------------------------------------------------------

void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window
	g_pQuad->draw();
	glutSwapBuffers();	// 交換 Frame Buffer
}

void onFrameMove(float delta)
{
	GL_Display();
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
		exit(EXIT_SUCCESS);
		break;
	}
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
		if (state == GLUT_DOWN);
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

	g_fTx = 12.0f*(x - HALF_SIZE) / (HALF_SIZE);
	g_fTy = -12.0f*(y - HALF_SIZE) / (HALF_SIZE);
	mxGT = Translate(g_fTx, g_fTy, 0);

	g_pQuad->setTRSMatrix(mxGT*mxT);
}
//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {
	
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
	glutInitWindowSize(SCREEN_SIZE, SCREEN_SIZE);

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("OpenGL_Example1");

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutMouseFunc(Win_Mouse);
	glutPassiveMotionFunc(Win_PassiveMotion);
	glutKeyboardFunc(Win_Keyboard);	// 處理 ASCII 按鍵如 A、a、ESC 鍵...等等
	glutSpecialFunc(Win_SpecialKeyboard);	// 處理 NON-ASCII 按鍵如 F1、Home、方向鍵...等等
	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);

	glutMainLoop();
	return 0;
}
