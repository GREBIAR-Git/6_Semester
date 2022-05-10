#include "Main.h"
#include "Cursor.h"
#include "Enemy.h"
#include "House.h"
#include "Movements.h"
#include "Light.h"



void Scene()
{
	glPushMatrix();
	DrawCursor();
	if (GetStateFlashlight())
	{
		DrawFlashlight();
	}
	MoveCamera();
	DrawNaturalLight();
	DrawTerrain();
	glPopMatrix();
}

void Initialize() 
{
	PlaySound(L"anthem.wav", NULL, SND_ASYNC);
	InitTexture();
	glClearColor(0, 0, 0, 1);
	srand(time(0));
	InitMainRoom();
	glEnable(GL_DEPTH_TEST);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	KeyboardProcessing();
	Scene();
	glutSwapBuffers();
}

void ResizeWin(int width, int height)
{
	glViewport(0, 0, width, height);
	float k = width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-k*0.1, k * 0.1, -1 * 0.1, 1 * 0.1, 1.5 * 0.1, 100);
	SetWidth(width);
	SetHeight(height);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Muzenstein");
	glutDisplayFunc(Display);
	glutSpecialFunc(SpecialKeyboardProcessing);
	glutKeyboardFunc(NormalKeyboardProcessing);
	glutPassiveMotionFunc(MouseMove);
	glutReshapeFunc(ResizeWin);
	glutSetCursor(GLUT_CURSOR_NONE);
	Initialize();
	InitLight();
	glutMainLoop();
	return 0;
}


