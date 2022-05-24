#include "1.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
const int winWidth = 1400;

using namespace std;

float rot, alfa, beta=0.01, ex;

Planet planets[10];

const float rSun = 0.30;
const float rDeathStar = 0.20;
const float offset = 0.03;
double scale = 0.7;
double rBigBall = 0.30;


unsigned int texture[8];


void InitTexture()
{
	glEnable(GL_TEXTURE_2D);
	int width1 = 1, height1 = 1, cnt;

	unsigned char* image = stbi_load("bmp\\128.bmp", &width1, &height1, &cnt, 0);
	glGenTextures(8, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);


	image = stbi_load("cube\\1.bmp", &width1, &height1, &cnt, 0);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("cube\\2.bmp", &width1, &height1, &cnt, 0);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("cube\\3.bmp", &width1, &height1, &cnt, 0);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("cube\\4.bmp", &width1, &height1, &cnt, 0);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("cube\\5.bmp", &width1, &height1, &cnt, 0);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("cube\\6.bmp", &width1, &height1, &cnt, 0);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);


	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	image = stbi_load("bmp\\1.bmp", &width1, &height1, &cnt, 0);
	glTexImage2D(GL_TEXTURE_2D, 8, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = stbi_load("bmp\\2.bmp", &width1, &height1, &cnt, 0);
	glTexImage2D(GL_TEXTURE_2D, 7, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = stbi_load("bmp\\4.bmp", &width1, &height1, &cnt, 0);
	glTexImage2D(GL_TEXTURE_2D, 6, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = stbi_load("bmp\\8.bmp", &width1, &height1, &cnt, 0);
	glTexImage2D(GL_TEXTURE_2D, 5, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = stbi_load("bmp\\16.bmp", &width1, &height1, &cnt, 0);
	glTexImage2D(GL_TEXTURE_2D, 4, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = stbi_load("bmp\\32.bmp", &width1, &height1, &cnt, 0);
	glTexImage2D(GL_TEXTURE_2D, 3, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = stbi_load("bmp\\64.bmp", &width1, &height1, &cnt, 0);
	glTexImage2D(GL_TEXTURE_2D, 2, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = stbi_load("bmp\\128.bmp", &width1, &height1, &cnt, 0);
	glTexImage2D(GL_TEXTURE_2D, 1, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = stbi_load("bmp\\256.bmp", &width1, &height1, &cnt, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);
}

void DrawSnowScene1()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);
	int x = 1;
	glTexCoord2f(0, 0); glVertex3f(-0.25, -0.25, 0);
	glTexCoord2f(0, x); glVertex3f(-0.25, 0.25, 0);
	glTexCoord2f(x, x); glVertex3f(0.25, 0.25, 0);
	glTexCoord2f(x, 0); glVertex3f(0.25, -0.25, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void DrawSnowScene2()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);
	int x = 2;
	glTexCoord2f(0, 0); glVertex3f(-0.25, -0.25, 0);
	glTexCoord2f(0, x); glVertex3f(-0.25, 0.25, 0);
	glTexCoord2f(x, x); glVertex3f(0.25, 0.25, 0);
	glTexCoord2f(x, 0); glVertex3f(0.25, -0.25, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void DrawSnowScene3()
{
	glPushMatrix();
	glRotatef(alfa, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);
	int x = 4;
	glTexCoord2f(0, 0); glVertex3f(-0.25, -0.25, 0);
	glTexCoord2f(0, x); glVertex3f(-0.25, 0.25, 0);
	glTexCoord2f(x, x); glVertex3f(0.25, 0.25, 0);
	glTexCoord2f(x, 0); glVertex3f(0.25, -0.25, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void DrawSnowScene4()
{
	glPushMatrix();
	glRotatef(alfa, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);
	int x = 1;
	glTexCoord2f(0, 0); glVertex3f(-0.25, -0.25, 0);
	glTexCoord2f(0, x); glVertex3f(-0.25, 0.25, 0);
	glTexCoord2f(x, x); glVertex3f(0.25, 0.25, 0);
	glTexCoord2f(x, 0); glVertex3f(0.25, -0.25, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}


void DrawSnowScene5()
{
	glPushMatrix();
	glRotatef(alfa, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.5); glVertex3f(-0.25, -0.25, 0);
	glTexCoord2f(0.5, 1); glVertex3f(-0.25, 0.25, 0);
	glTexCoord2f(1, 0.5); glVertex3f(0.25, 0.25, 0);
	glTexCoord2f(0.5, 0); glVertex3f(0.25, -0.25, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void DrawSnowScene6()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glRotatef(alfa, 0, 0, 1);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	int x = 2;
	GLdouble ss[4] = { x, 0, 0, 0.25*x};
	glTexGendv(GL_S, GL_OBJECT_PLANE, ss);
	GLdouble ss1[4] = { 0, x, 0, 0.25*x };
	glTexGendv(GL_T, GL_OBJECT_PLANE, ss1);
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, -0.25, 0);
	glVertex3f(-0.25, 0.25, 0);
	glVertex3f(0.25, 0.25, 0);
	glVertex3f(0.25, -0.25, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_S);
}

void DrawSnowScene7()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glRotatef(alfa, 0, 0, 1);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	
	int x = 4;
	GLdouble ss[4] = { x, 0, 0, 0.25 * x };
	glTexGendv(GL_S, GL_OBJECT_PLANE, ss);
	GLdouble ss1[4] = { 0, x, 0, 0.25 * x };
	glTexGendv(GL_T, GL_OBJECT_PLANE, ss1);
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, -0.25, 0);
	glVertex3f(-0.25, 0.25, 0);
	glVertex3f(0.25, 0.25, 0);
	glVertex3f(0.25, -0.25, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_S);
}

void DrawSnowScene8()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glRotatef(alfa, 0, 0, 1);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	int x = 8;
	GLdouble ss[4] = { x, 0, 0, 0.25 * x };
	glTexGendv(GL_S, GL_OBJECT_PLANE, ss);
	GLdouble ss1[4] = { 0, x, 0, 0.25 * x };
	glTexGendv(GL_T, GL_OBJECT_PLANE, ss1);
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, -0.25, 0);
	glVertex3f(-0.25, 0.25, 0);
	glVertex3f(0.25, 0.25, 0);
	glVertex3f(0.25, -0.25, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_S);
}

void DrawSnowScene9()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glRotatef(alfa, 0, 0, 1);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	int x = 2;
	GLdouble ss[4] = { x, 0, 0, 0.25 * x };
	glTexGendv(GL_S, GL_OBJECT_PLANE, ss);
	GLdouble ss1[4] = { 0, x, 0, 0.25 * x };
	glTexGendv(GL_T, GL_OBJECT_PLANE, ss1);
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, -0.25, 0);
	glVertex3f(-0.25, 0.25, 0);
	glVertex3f(0.25, 0.25, 0);
	glVertex3f(0.25, -0.25, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_S);
}

void DrawSnowScene10()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glRotatef(alfa, 0, 0, 1);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	int x = 1;
	GLdouble ss[4] = { x, x, 0, 0.25 * x*2 };
	glTexGendv(GL_S, GL_OBJECT_PLANE, ss);
	GLdouble ss1[4] = { -x, x, 0, 0.25 * x*2};
	glTexGendv(GL_T, GL_OBJECT_PLANE, ss1);
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, -0.25, 0);
	glVertex3f(-0.25, 0.25, 0);
	glVertex3f(0.25, 0.25, 0);
	glVertex3f(0.25, -0.25, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_S);
}

void DrawSnowScene11()
{
	glPushMatrix();
	glRotatef(alfa, 0, 1, 0);
	glRotatef(rot, 1, 0, 0);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	int x = 1;
	GLdouble ss[4] = { 0, -x, x, 0.5 * x *2 };
	glTexGendv(GL_S, GL_OBJECT_PLANE, ss);
	GLdouble ss1[4] = { -x, 0, x, 0.5 * x*2 };
	glTexGendv(GL_T, GL_OBJECT_PLANE, ss1);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	GLdouble ss4[4] = {x, 0, 0, 0.5 * x};
	glTexGendv(GL_S, GL_OBJECT_PLANE, ss4);
	GLdouble ss5[4] = { 0, x, x, 0.5 * x * 2 };
	glTexGendv(GL_T, GL_OBJECT_PLANE, ss5);

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();


	GLdouble ss2[4] = {x, 0, x, 0.5 * x * 2};
	glTexGendv(GL_S, GL_OBJECT_PLANE, ss2);
	GLdouble ss3[4] = { 0, x, 0, 0.5 * x  };
	glTexGendv(GL_T, GL_OBJECT_PLANE, ss3);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_S);
}


void DrawSnowScene12()
{
	glPushMatrix();
	glScalef(beta, beta, 1);
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_POLYGON);
	int x = 1;
	glTexCoord2f(0, 0); glVertex3f(-0.25, -0.25, 0);
	glTexCoord2f(0, x); glVertex3f(-0.25, 0.25, 0);
	glTexCoord2f(x, x); glVertex3f(0.25, 0.25, 0);
	glTexCoord2f(x, 0); glVertex3f(0.25, -0.25, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}


void Scene()
{
	if (ex == 1)
	{
		DrawSnowScene1();
	}
	else if (ex == 2)
	{
		DrawSnowScene2();
	}
	else if (ex == 3)
	{
		DrawSnowScene3();
	}
	else if (ex == 4)
	{
		DrawSnowScene4();
	}
	else if (ex == 5)
	{
		DrawSnowScene5();
	}
	else if (ex == 6)
	{
		DrawSnowScene6();
	}
	else if (ex == 7)
	{
		DrawSnowScene7();
	}
	else if (ex == 8)
	{
		DrawSnowScene8();
	}
	else if (ex == 9)
	{
		DrawSnowScene9();
	}
	else if (ex == 10)
	{
		DrawSnowScene10();
	}
	else if (ex == 11)
	{
		DrawSnowScene11();
	}
	else if (ex == 12)
	{
		DrawSnowScene12();
	}
}

void Initialize() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);// задаем ортографическую проекцию и видимый объем
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST); // включаем тест глубины. Если этого не сделать видимыми будут объекты не  расположенные ближе всего к наблюдателю, а созданные последними.
	glLoadIdentity();
}

void Specialkeys(int key, int x, int y) 
{
	if (key == GLUT_KEY_UP) 
	{
		alfa -= 1; 
	}
	else if (key == GLUT_KEY_DOWN) 
	{ 
		alfa += 1;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		rot += 1;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		rot -= 1;
	}
	else if (key == GLUT_KEY_END)
	{
		beta += 0.01;
	}
	else if (key == GLUT_KEY_HOME)
	{
		if (beta > 0.01)
		{
			beta -= 0.01;
		}
	}
	else
	{
		ex = key;
		rot = 0;
		alfa = 0;
	}
	glutPostRedisplay(); // принудительный вызов функции визуализации

}

void Display() {
	glClearColor(0.059, 0.059, 0.07, 1.0);// задаем цвет заливки холста
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);// -используем буфер глубины, двойную буферизацию и представление цвета триадой RGB.
	glutInitWindowSize(800, 800);
	glutCreateWindow("Our first GLUT application!");
	glutDisplayFunc(Display);//  назначаем функцию визуализации
	glutSpecialFunc(Specialkeys);// назначаем функцию обработки нажатия специальных клавиш
	glutReshapeFunc(ResizeWin);
	Initialize();// дополнительные настройки конвейера
	InitTexture();
	glutMainLoop();
	return 0;
}


