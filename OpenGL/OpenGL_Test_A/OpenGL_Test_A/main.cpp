#include <glut.h>
#include <iostream>
#include <ctime>
#include <math.h>
#include <windows.h>
#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"

#define _USE_MATH_DEFINES
#ifndef M_PI
#define M_PI 3.14159265
#endif

int main(int argc, char** argv);
void Scene();
void Initialize();
void Display();
void ResizeWin(int width, int height);
void KeyboardCallbackNormal(unsigned char key, int x, int y);
void KeyboardCallbackSpecial(int key, int x, int y);
void MouseCallbackNormal(int x, int y);
void MouseCallbackPassive(int x, int y);
void Crosshair();
void Ground(int xStart, int yStart, int xEnd, int yEnd);
void Cube();
void CameraRotateTranslate();
void DrawAxes(double length);
void Textures();
void Sun();

int windowWidth, windowHeight;
int cameraMoveSpeed = 1;
bool xRay = false;
bool texturesOn = true;
int timerStep = 1 * CLOCKS_PER_SEC;
long timeCounter = 0;
clock_t beginningOfTime;

struct Position
{
	double x, y;
	double xA, zA;
};

struct Textures
{
	unsigned int ground;
};

struct Position cameraPos;
struct Textures textures;


int main(int argc, char** argv)
{
	beginningOfTime = clock();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutCreateWindow("OpenGL TEST");
	glutDisplayFunc(Display);
	glutKeyboardFunc(KeyboardCallbackNormal);
	glutSpecialFunc(KeyboardCallbackSpecial);
	glutPassiveMotionFunc(MouseCallbackPassive);
	glutReshapeFunc(ResizeWin);
	glutSetCursor(GLUT_CURSOR_NONE);
	Initialize();
	//InitLight();
	glutMainLoop();

	return 0;
}

void Scene()
{
	if (texturesOn)
	{
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
	glPushMatrix();
	Crosshair();

	CameraRotateTranslate(); // !!!

	Sun();
	DrawAxes(100);
	if (!xRay)
	{
		Ground(-10, -10, 20, 20);
		Cube();
	}
	glPopMatrix();
}

void Initialize()
{
	Textures();
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	float ambient[] = { 0.05, 0.05, 0.05, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	// Sunlight
	float diffuseSun[] = { 0.7, 0.7, 0.7, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseSun);
	float constant_attenuation[] = { 1 };
	float linear_attenuation[] = { 0 };
	float quadratic_attenuation[] = { 0 };
	glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constant_attenuation);
	glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, linear_attenuation);
	glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadratic_attenuation);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Scene();
	glutSwapBuffers();
}

void ResizeWin(int width, int height)
{
	glViewport(0, 0, width, height);
	float k = width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-k * 0.1, k * 0.1, -1 * 0.1, 1 * 0.1, 1.5 * 0.1, 100);
	windowWidth = width;
	windowHeight = height;
}

void KeyboardCallbackNormal(unsigned char key, int x, int y)
{
	if (GetKeyState('W') < 0)
	{
		double angle = (cameraPos.zA + 90) * M_PI / 180.0f;
		cameraPos.x += cos(angle) * cameraMoveSpeed;
		cameraPos.y += sin(angle) * cameraMoveSpeed;
	}
	if (GetKeyState('S') < 0)
	{
		double angle = (cameraPos.zA - 90) * M_PI / 180.0f;
		cameraPos.x += cos(angle) * cameraMoveSpeed;
		cameraPos.y += sin(angle) * cameraMoveSpeed;
	}
	if (GetKeyState('A') < 0)
	{
		double angle = (cameraPos.zA + 180) * M_PI / 180.0f;
		cameraPos.x += cos(angle) * cameraMoveSpeed;
		cameraPos.y += sin(angle) * cameraMoveSpeed;
	}
	if (GetKeyState('D') < 0)
	{
		double angle = (cameraPos.zA) * M_PI / 180.0f;
		cameraPos.x += cos(angle) * cameraMoveSpeed;
		cameraPos.y += sin(angle) * cameraMoveSpeed;
	}
	if (GetKeyState('X') < 0)
	{
		xRay = !xRay;
	}
	if (key == 27)
	{
		exit(0);
	}
	glutPostRedisplay();
}

void KeyboardCallbackSpecial(int key, int x, int y)
{
	
	glutPostRedisplay();
}

void MouseCallbackNormal(int x, int y)
{

	glutPostRedisplay();
}

void MouseCallbackPassive(int x, int y)
{
	float zSpeed = 0.55, xSpeed = 0.5;
	cameraPos.zA += (windowWidth / 2 - x) * zSpeed;
	int offset = (windowHeight / 2 - y);
	if (cameraPos.xA + offset > 180)
	{
		cameraPos.xA = 180;
	}
	else if (cameraPos.xA + offset < 0)
	{
		cameraPos.xA = 0;
	}
	else
	{
		cameraPos.xA += offset * xSpeed;
	}
	glutWarpPointer(windowWidth / 2, windowHeight / 2);
	glutPostRedisplay();
}

void Crosshair()
{
	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glutSolidSphere(0.001, 100, 100);
	glEnd();
	glPopMatrix();
}

void Ground(int xStart, int yStart, int xEnd, int yEnd)
{
	glPushMatrix();
	for (int i = xStart; i < xEnd; i++)
	{
		for (int f = yStart; f < yEnd; f++)
		{
			glBindTexture(GL_TEXTURE_2D, textures.ground);
			glColor3f(1, 1, 1);
			glPushMatrix();
			glTranslated(i, f, 0);
			glBegin(GL_QUADS);
			for (float x = 0; x < 1; x += 0.1)
			{
				for (float y = 0; y < 1; y += 0.1)
				{
					glTexCoord2f(0, 0); glNormal3f(0, 0, 1); glVertex3f(x, y, 0);
					glTexCoord2f(1, 0); glNormal3f(0, 0, 1); glVertex3f(x, y + 0.1, 0);
					glTexCoord2f(1, 1); glNormal3f(0, 0, 1); glVertex3f(x + 0.1, y + 0.1, 0);
					glTexCoord2f(0, 1); glNormal3f(0, 0, 1); glVertex3f(x + 0.1, y, 0);
				}
			}
			glEnd();
			glBindTexture(GL_TEXTURE_2D, 0);
			glPopMatrix();
		}
	}
	
	glPopMatrix();
}

void Cube()
{
	int angle = 30;
	glPushMatrix();
	glTranslatef(5, 5, 2 * cos(angle * M_PI / 180.0f));
	glRotatef(angle, 1, 1, 0);
	glBegin(GL_QUADS);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);


	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);


	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);


	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);


	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);


	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glPopMatrix();
}

void CameraRotateTranslate()
{
	glRotatef(-cameraPos.xA, 1, 0, 0);
	glRotatef(-cameraPos.zA, 0, 0, 1);
	glTranslatef(-cameraPos.x, -cameraPos.y, -1);
}

void DrawAxes(double length) {
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(length, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, length, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, length);

	glEnd();
	glPopMatrix();
}

void Textures()
{
	int width1 = 2, height1 = 2, cnt;

	unsigned char* image = stbi_load("textures\\ground.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &textures.ground);
	glBindTexture(GL_TEXTURE_2D, textures.ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);
}

void Sun()
{
	if (clock() - timeCounter > 0)
	{
		timeCounter += timerStep / CLOCKS_PER_SEC;
	}
	int cycle = 60;
	int angle = (int)(timeCounter / (float)cycle) % 180;
	int distance = 70;

	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT0);
	glPushMatrix();
	glRotatef(angle, 1, 0, 0);
	float position[] = { 0, distance, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glTranslatef(0, distance, 0);
	glColor3f(1, 0.78, 0.0);
	glBegin(GL_LINES);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glutSolidSphere(5, 100, 100);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnd();
	glPopMatrix();
}