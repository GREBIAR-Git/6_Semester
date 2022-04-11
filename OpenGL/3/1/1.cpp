#include <iostream>
#include <math.h>
#include <glut.h>

using namespace std;

int rot, alfa, ex;

const float rSun = 0.30;
const float rDeathStar = 0.20;
const float rMercury = 0.015;
const float rVenus = 0.045;
const float rEarth = 0.05;
const float rMars = 0.04;
const float rJupiter = 0.14;
const float rSaturn = 0.16;
const float rUranus = 0.081;
const float rNeptune = 0.08;
const float rPluto = 0.02;
const float offset = 0.03;

void DrawDeathStar()
{
	if (alfa%360 >= -49 && alfa%360<=-39|| alfa % 360 >= 311 && alfa % 360 <= 321)
	{
		glPushMatrix();
		glTranslated(2- rDeathStar, -2 + rDeathStar, -2 + rDeathStar-0.15);
		glRotatef(45, -2, -2, 0);
		glColor3ub(4, 202, 96);
		glutSolidCone(rDeathStar / 5, 2.8, 100, 100);
		glPopMatrix();
	}
	glPushMatrix();
	glColor3ub(91, 95, 104);
	glTranslated(2- rDeathStar, -2 + rDeathStar, -2+ rDeathStar - 0.15);
	glutSolidSphere(rDeathStar, 100, 100);

	glPopMatrix();
}

float DrawSun()
{
	float orbit;
	glPushMatrix();
	glColor3ub(255, 215, 0);
	glTranslated(0, 0, 0);
	glutSolidSphere(rSun, 100, 100);
	orbit =+ rSun;
	glPopMatrix();
	return orbit;
}

float DrawMercury(float orbit)
{
	glPushMatrix();
	glRotatef(alfa* 4.5f, 0, 0, 1);
	glColor3ub(239, 83, 36);
	glTranslated(orbit + offset + rMercury, 0, 0);
	glutSolidSphere(rMercury, 100, 100);
	orbit += (offset + rMercury*2);
	glPopMatrix();
	return orbit;
}

float DrawVenus(float orbit)
{
	glPushMatrix();
	glRotatef(alfa * 1.5f, 0, 0, 1);
	glColor3ub(235, 148, 35);
	glTranslated(orbit + offset + rVenus, 0, 0);
	glutSolidSphere(rVenus, 100, 100);
	orbit += (offset + rVenus*2);
	glPopMatrix();
	return orbit;
}

float DrawEarth(float orbit)
{
	glPushMatrix();
	glRotatef(alfa, 0, 0, 1);
	glColor3ub(121, 195, 97);
	glTranslated(orbit + offset + rEarth, 0, 0);
	glutSolidSphere(rEarth, 100, 100);
	orbit += (offset + rEarth*2);
	glPopMatrix();
	return orbit;
}

float DrawMars(float orbit)
{
	glPushMatrix();
	glRotatef(alfa * 1/2.0, 0, 0, 1);
	glColor3ub(241, 115, 75);
	glTranslated(orbit + offset+ rMars, 0, 0);
	glutSolidSphere(rMars, 100, 100);
	orbit += (offset + rMars*2);
	glPopMatrix();
	return orbit;
}

float DrawJupiter(float orbit)
{
	glPushMatrix();
	glRotatef(alfa * 1/12.0, 0, 0, 1);
	glColor3ub(144, 93, 29);
	glTranslated(orbit + offset + rJupiter, 0, 0);
	glutSolidSphere(rJupiter, 100, 100);
	orbit += (offset + rJupiter*2);
	glPopMatrix();
	return orbit;
}

void DrawRing(float orbit)
{
	glPushMatrix();
	glRotatef(35, 1, 0, 0);
	glColor3ub(255, 20, 147);
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < 50; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(50);//get the current angle

		float x = (rSaturn+0.02) * cosf(theta);//calculate the x component
		float y = (rSaturn + 0.02) * sinf(theta);//calculate the y component

		glVertex2f(x + orbit+ rSaturn+0.03, y);//output vertex

	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < 50; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(50);//get the current angle

		float x = (rSaturn + 0.01) * cosf(theta);//calculate the x component
		float y = (rSaturn + 0.01) * sinf(theta);//calculate the y component

		glVertex2f(x + orbit + rSaturn + 0.025, y);//output vertex

	}
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < 50; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(50);//get the current angle

		float x = (rSaturn + 0.03) * cosf(theta);//calculate the x component
		float y = (rSaturn + 0.03) * sinf(theta);//calculate the y component

		glVertex2f(x + orbit + rSaturn + 0.03, y);//output vertex

	}
	glEnd();

	glPopMatrix();
}

float DrawSaturn(float orbit)
{
	glPushMatrix();
	glRotatef(alfa*1/30.0, 0, 0, 1);
	DrawRing(orbit);
	glColor3ub(165, 110, 79);
	glTranslated(orbit + offset + rSaturn, 0, 0);
	glutSolidSphere(rSaturn, 100, 100);
	orbit += (offset + rSaturn*2);
	glPopMatrix();
	return orbit;
}

float DrawUranus(float orbit)
{
	glPushMatrix();
	glRotatef(alfa * 1/84.0, 0, 0, 1);
	glColor3ub(53, 220, 245);
	glTranslated(orbit + offset + rUranus, 0, 0);
	glutSolidSphere(rUranus, 100, 100);
	orbit += (offset + rUranus*2);
	glPopMatrix();
	return orbit;
}

float DrawNeptune(float orbit)
{
	glPushMatrix();
	glRotatef(alfa * 1/165.0, 0, 0, 1);
	glColor3ub(40, 165, 221);
	glTranslated(orbit + offset + rNeptune, 0, 0);
	glutSolidSphere(rNeptune, 100, 100);
	orbit += (offset + rNeptune*2);
	glPopMatrix();
	return orbit;
}

float DrawPluto(float orbit)
{
	glPushMatrix();
	glRotatef(alfa * 1/248.0, 0, 0, 1);
	glColor3ub(255, 215, 0);
	glTranslated(orbit + offset + rPluto, 0, 0);
	glutSolidSphere(rPluto, 100, 100);
	orbit += offset + rPluto*2;
	glPopMatrix();
	return orbit;
}

void SolarSystem()
{
	DrawPluto(
		DrawNeptune(
		DrawUranus(
		DrawSaturn(
		DrawJupiter(
		DrawMars(
		DrawEarth(
		DrawVenus(
		DrawMercury(
		DrawSun()
		)))))))));
}

void Scene()
{
	SolarSystem();
	DrawDeathStar();
}


void Initialize() {
	glClearColor(0.059, 0.059, 0.07, 1.0);// задаем цвет заливки холста
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);// задаем ортографическую проекцию и видимый объем
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST); // включаем тест глубины. Если этого не сделать видимыми будут объекты не  расположенные ближе всего к наблюдателю, а созданные последними.
	glLoadIdentity();
}

void Specialkeys(int key, int x, int y) {
	/*if (key == GLUT_KEY_LEFT) { rot = rot - 2.0; }
	else
		if (key == GLUT_KEY_RIGHT) { rot = rot + 2.0; }
		else*/
			if (key == GLUT_KEY_UP) { alfa = alfa - 2.0; }
			else
				if (key == GLUT_KEY_DOWN) { alfa = alfa + 2.0; }
				else {
					ex = key;
					rot = 0;
					alfa = 0;
				}
	glutPostRedisplay(); // принудительный вызов функции визуализации

}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, (glutGet(GLUT_SCREEN_HEIGHT) - 5)/2, (glutGet(GLUT_SCREEN_HEIGHT) - 5)/2);
	glLoadIdentity();
	Scene();

	glViewport((glutGet(GLUT_SCREEN_HEIGHT) - 5) / 2, 0, (glutGet(GLUT_SCREEN_HEIGHT) - 5) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 5) / 2);
	glLoadIdentity();
	glRotatef(90, 1, 0, 0);
	Scene();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);// -используем буфер глубины, двойную буферизацию и представление цвета триадой RGB.
	glutInitWindowSize(glutGet(GLUT_SCREEN_HEIGHT)-5, (glutGet(GLUT_SCREEN_HEIGHT)-5)/2);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_HEIGHT)-5) / 4, 0);
	glutCreateWindow("Our first GLUT application!");
	glutDisplayFunc(Display);//  назначаем функцию визуализации
	glutSpecialFunc(Specialkeys);// назначаем функцию обработки нажатия специальных клавиш
	Initialize();// дополнительные настройки конвейера
	glutMainLoop();
	return 0;
}


