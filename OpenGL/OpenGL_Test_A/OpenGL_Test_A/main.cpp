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
void Ground(int xStart, int yStart, int xEnd, int yEnd);
void Cube();
void CameraRotateTranslate();
void DrawAxes(double length);
void Textures();
void Light0();
void FlashlightIfOn();
void Flashlight();
void Carpet(float xStart, float yStart, float xEnd, float yEnd);
void Pillar(float x, float y, float height, float width);
void PillarSide(float height, float width);
void Roof();
void RoofPart();

int windowWidth, windowHeight;
float cameraMoveSpeed = 0.35;
bool texturesOn = true;
int timerStep = 1 * CLOCKS_PER_SEC;
long timeCounter = 0;
bool flashlightOn = false;
bool textureOn = true;
bool lightOn = true;

float emissionDefault[] = { 0, 0, 0, 1 };
float diffuseDefault[] = { 0.8, 0.8, 0.8, 1.0 };


struct Position
{
	double x, y, z;
	double xA, zA;
};

struct Textures
{
	unsigned int ground;
	unsigned int carpet;
	unsigned int steel;
	unsigned int green_rock;
	unsigned int strange;
	unsigned int water;
	unsigned int pyramid;
	unsigned int grass;
	unsigned int lava;
};

struct Position cameraPos;
struct Textures textures;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("OpenGL Test Allyanov 92PG");
	glutDisplayFunc(Display);
	glutKeyboardFunc(KeyboardCallbackNormal);
	glutSpecialFunc(KeyboardCallbackSpecial);
	glutPassiveMotionFunc(MouseCallbackPassive);
	glutReshapeFunc(ResizeWin);
	glutSetCursor(GLUT_CURSOR_NONE);
	Initialize();
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
	FlashlightIfOn();

	CameraRotateTranslate();

	Light0();
	DrawAxes(100);
	Ground(-10, -10, 20, 20);
	Carpet(0, 0, 5, 5);
	Cube();
	Pillar(0, 0, 3.5, 0.1);
	Pillar(5, 0, 3.5, 0.1);
	Pillar(0, 5, 3.5, 0.1);
	Pillar(5, 5, 3.5, 0.1);
	Roof();
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
	float ambient[] = { 0.2, 0.15, 0.1, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	// Light0
	float diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	float constant_attenuation[] = { 1 };
	float linear_attenuation[] = { 0 };
	float quadratic_attenuation[] = { 0 };
	glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constant_attenuation);
	glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, linear_attenuation);
	glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadratic_attenuation);

	Flashlight();

	cameraPos.z = 1;
	cameraPos.x = -2.5;
	cameraPos.y = 2.5;
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
	if (GetKeyState('Q') < 0)
	{
		cameraPos.z += 0.1;
	}
	if (GetKeyState('E') < 0)
	{
		cameraPos.z -= 0.1;
		if (cameraPos.z < 1)
		{
			cameraPos.z = 1;
		}
	}
	if (GetKeyState('C') < 0)
	{
		textureOn = !textureOn;
	}
	if (GetKeyState('G') < 0)
	{
		lightOn = !lightOn;
	}
	if (GetKeyState('F') < 0)
	{
		flashlightOn = !flashlightOn;
		if (flashlightOn)
		{
			glEnable(GL_LIGHT1);
		}
		else
		{
			glDisable(GL_LIGHT1);
		}
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
	float zSpeed = 0.5, xSpeed = 0.5;
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

void Ground(int xStart, int yStart, int xEnd, int yEnd)
{
	glPushMatrix();
	for (int i = xStart; i < xEnd; i++)
	{
		for (int f = yStart; f < yEnd; f++)
		{
			if (textureOn)
			{
				glBindTexture(GL_TEXTURE_2D, textures.ground);
			}
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
			if (textureOn)
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			glPopMatrix();
		}
	}
	
	glPopMatrix();
}

void Cube()
{
	int angle = 45;
	glPushMatrix();
	glTranslatef(2.5, 2.5, 2 + 0.1 + 1/2 * 2 * sqrt(3));
	glRotatef(angle, 1, 1, 0);

	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, textures.green_rock);
	}
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1, 0); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1, 1); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0, 1); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, textures.strange);
	}
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glNormal3f(0.0f, -1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1, 0); glNormal3f(0.0f, -1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1, 1); glNormal3f(0.0f, -1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0, 1); glNormal3f(0.0f, -1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, textures.water);
	}
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1, 0); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1, 1); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0, 1); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, textures.lava);
	}
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1, 0); glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1, 1); glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0, 1); glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, textures.grass);
	}
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1, 0); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1, 1); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0, 1); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, textures.pyramid);
	}
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1, 0); glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1, 1); glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0, 1); glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glPopMatrix();
}

void CameraRotateTranslate()
{
	glRotatef(-cameraPos.xA, 1, 0, 0);
	glRotatef(-cameraPos.zA, 0, 0, 1);
	glTranslatef(-cameraPos.x, -cameraPos.y, -cameraPos.z);
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

	image = stbi_load("textures\\carpet.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &textures.carpet);
	glBindTexture(GL_TEXTURE_2D, textures.carpet);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("textures\\steel.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &textures.steel);
	glBindTexture(GL_TEXTURE_2D, textures.steel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("textures\\green_rock.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &textures.green_rock);
	glBindTexture(GL_TEXTURE_2D, textures.green_rock);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("textures\\strange.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &textures.strange);
	glBindTexture(GL_TEXTURE_2D, textures.strange);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("textures\\water.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &textures.water);
	glBindTexture(GL_TEXTURE_2D, textures.water);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("textures\\pyramid.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &textures.pyramid);
	glBindTexture(GL_TEXTURE_2D, textures.pyramid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("textures\\grass.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &textures.grass);
	glBindTexture(GL_TEXTURE_2D, textures.grass);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("textures\\lava.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &textures.lava);
	glBindTexture(GL_TEXTURE_2D, textures.lava);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);
}

void Light0()
{
	if (clock() - timeCounter > 0)
	{
		timeCounter += timerStep / CLOCKS_PER_SEC;
	}
	int cycle = 1;
	int angle = (int)(timeCounter / (float)cycle) % 360;
	int distance = 2;

	glPushMatrix();
	glTranslatef(2.5, 2.5, 0);

	if (lightOn)
	{
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}
	glPushMatrix();
	glRotatef(angle, 0, 0, 1);
	glTranslatef(0, distance, 2);
	float position[] = { 0, 0, 0, 1 };
	float emission[] = { 0, 0.78, 0.95, 1 };
	float diffuse[] = { 0.75, 0.9, 1, 1 };
	float specular[] = { 0, 0.75, 1, 1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glColor3f(0, 0.78, 0.95);
	glBegin(GL_LINES);
	glutSolidSphere(0.3, 100, 100);
	glEnd();
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionDefault);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseDefault);
	glPopMatrix();

	glPopMatrix();
}

void Flashlight()
{
	float position[] = { 0, 0, 1, 1 };
	float direction[] = { 1, 0, 0 };
	float cutoff[] = { 6.5 };
	float diffuse[] = { 0.8, 0.8, 1, 1.0 };
	float specular[] = { 0.4, 0.4, 0.6, 1.0 };
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glPopMatrix();
	if (!flashlightOn)
	{
		glDisable(GL_LIGHT1);
	}
}

void FlashlightIfOn()
{
	float position[] = { 0,0,5,1 };
	glLightfv(GL_LIGHT1, GL_POSITION, position);
}

void Carpet(float xStart, float yStart, float xEnd, float yEnd)
{
	glPushMatrix();
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, textures.carpet);
	}
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0); glNormal3f(0, 0, 1); glVertex3f(xStart, yStart, 0.1);
	glTexCoord2f(1, 0); glNormal3f(0, 0, 1); glVertex3f(xStart, yEnd, 0.1);
	glTexCoord2f(1, 1); glNormal3f(0, 0, 1); glVertex3f(xEnd, yEnd, 0.1);
	glTexCoord2f(0, 1); glNormal3f(0, 0, 1); glVertex3f(xEnd, yStart, 0.1);

	glEnd();
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glPopMatrix();
}

void Pillar(float x, float y, float height, float width)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	glPushMatrix();

	glPushMatrix();
	glTranslatef(-width / 2, -width / 2, 0);
	PillarSide(height, width);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glTranslatef(-width / 2, -width / 2, 0);
	PillarSide(height, width);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glTranslatef(-width / 2, -width / 2, 0);
	PillarSide(height, width);
	glPopMatrix();

	glPushMatrix();
	glRotatef(270, 0, 0, 1);
	glTranslatef(-width / 2, -width / 2, 0);
	PillarSide(height, width);
	glPopMatrix();
	
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y, height + 0.1);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(- width / 2, 0, -width / 2);
	PillarSide(width, width);
	glPopMatrix();
	glPopMatrix();
}

void PillarSide(float height, float width)
{
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, textures.steel);
	}
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	for (float i = 0; i < width; i += 0.1)
	{
		for (float j = 0; j < height; j += 0.1)
		{
			glPushMatrix();
			glTranslated(i, j, 0);
			glTexCoord2f(0, 0); glNormal3f(0, -1, 0); glVertex3f(i, 0, j);
			glTexCoord2f(1, 0); glNormal3f(0, -1, 0); glVertex3f(i, 0, j + 0.1);
			glTexCoord2f(1, 1); glNormal3f(0, -1, 0); glVertex3f(i + 0.1, 0, j + 0.1);
			glTexCoord2f(0, 1); glNormal3f(0, -1, 0); glVertex3f(i + 0.1, 0, j);
			glPopMatrix();
		}
	}
	glEnd();
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Roof()
{
	glPushMatrix();
	glTranslatef(2.5, 2.5, 3.5 + 0.1);
	glPushMatrix();

	glPushMatrix();
	RoofPart();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	RoofPart();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	RoofPart();
	glPopMatrix();

	glPushMatrix();
	glRotatef(270, 0, 0, 1);
	RoofPart();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}

void RoofPart()
{
	float angle = -30;
	float angleRad = angle * M_PI / 180.0f;
	glTranslatef(0, 0, 2.5 * sin(-angleRad));
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, textures.pyramid);
	}
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glNormal3f(0, 0, -1); glVertex3f(-2.5 / cos(angleRad), -2.5 / cos(angleRad), 0);
	glTexCoord2f(1, 0); glNormal3f(0, 0, -1); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1); glNormal3f(0, 0, -1); glVertex3f(-2.5 / cos(angleRad), 2.5 / cos(angleRad), 0);
	glEnd();
	if (textureOn)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glPopMatrix();
}