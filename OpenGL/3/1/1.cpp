#include "1.h"

const int winWidth = 1400;

using namespace std;

int rot, alfa, ex;

Planet planets[10];

const float rSun = 0.30;
const float rDeathStar = 0.20;
const float offset = 0.03;

void InitPlanet()
{
	planets[0] = { 0.30, 0, 255, 215, 0 };
	planets[1] = { 0.015, 4.5, 239, 83, 36 };
	planets[2] = { 0.045, 1.5, 235, 148, 35 };
	planets[3] = { 0.05, 1, 121, 195, 97 };
	planets[4] = { 0.04, 1 / 2.0, 241, 115, 75 };
	planets[5] = { 0.14, 1 / 12.0, 144, 93, 29 };
	planets[6] = { 0.16, 1 / 30.0, 165, 110, 79 };
	planets[7] = { 0.081, 1 / 84.0, 53, 220, 245 };
	planets[8] = { 0.08, 1 / 165.0, 40, 165, 221 };
	planets[9] = { 0.02, 1 / 248.0, 255, 215, 0 };
}

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

float DrawPlanet(float orbit, Planet planet)
{
	glPushMatrix();
	glRotatef(alfa * planet.spead, 0, 0, 1);
	glColor3ub(planet.r,planet.g,planet.b);
	glTranslated(orbit + offset + planet.radius, 0, 0);
	glutSolidSphere(planet.radius, 100, 100);
	orbit += (offset + planet.radius * 2);
	glPopMatrix();
	return orbit;
}

float DrawStar(float orbit, Planet planet)
{
	glPushMatrix();
	glColor3ub(planet.r, planet.g, planet.b);
	glutSolidSphere(planet.radius, 100, 100);
	orbit += (planet.radius);
	glPopMatrix();
	return orbit;
}


void DrawRing(float orbit)
{
	glPushMatrix();
	glRotatef(alfa * planets[5].spead, 0, 0, 1);
	glRotatef(35, 1, 0, 0);
	glColor3ub(255, 20, 147);
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < 50; ii++)
	{
		float theta = 2 * 3.1415926f * float(ii) / float(50);

		float x = (planets[5].radius + 0.02) * cosf(theta);
		float y = (planets[5].radius + 0.02) * sinf(theta);

		glVertex2f(x + orbit+ planets[5].radius + 0.03, y);

	}
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < 50; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(50);

		float x = (planets[5].radius + 0.01) * cosf(theta);
		float y = (planets[5].radius + 0.01) * sinf(theta);

		glVertex2f(x + orbit + planets[5].radius + 0.025, y);

	}
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < 50; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(50);

		float x = (planets[5].radius + 0.03) * cosf(theta);
		float y = (planets[5].radius + 0.03) * sinf(theta);

		glVertex2f(x + orbit + planets[5].radius + 0.03, y);

	}
	glEnd();

	glPopMatrix();
}

void SolarSystem()
{
	float orbit = 0;
	orbit = DrawStar(orbit, planets[0]);
	for (int i = 1; i < 10; i++)
	{
		if (i == 5)
		{
			DrawRing(orbit);
		}
		orbit = DrawPlanet(orbit, planets[i]);
	}
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

	glViewport(0, 0, winWidth/2, winWidth/2);
	glLoadIdentity();
	Scene();
	//glutGet(GLUT_SCREEN_HEIGHT)
	glViewport(winWidth/2, 0, winWidth/2, winWidth/2);
	glLoadIdentity();
	glRotatef(90, 1, 0, 0);
	Scene();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	InitPlanet();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);// -используем буфер глубины, двойную буферизацию и представление цвета триадой RGB.
	glutInitWindowSize(winWidth, winWidth/2);
	glutCreateWindow("Our first GLUT application!");
	glutDisplayFunc(Display);//  назначаем функцию визуализации
	glutSpecialFunc(Specialkeys);// назначаем функцию обработки нажатия специальных клавиш
	Initialize();// дополнительные настройки конвейера
	glutMainLoop();
	return 0;
}


