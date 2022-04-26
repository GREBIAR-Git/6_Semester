#include "1.h"
const int winWidth = 1400;

using namespace std;

int rot, alfa, ex,con,tran;

Planet planets[10];

const float rSun = 0.30;
const float rDeathStar = 0.20;
const float offset = 0.03;
double scale = 0.7;
double rBigBall = 0.30;

bool globalLight = true;

float no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
float mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
float mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
float mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
//float mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
float mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
float no_shininess = 0.0;
float low_shininess = 5.0;
float high_shininess = 100.0;
float mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };


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

void InitLight() {
	glShadeModel(GL_SMOOTH);
	//    glShadeModel(GL_FLAT);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT2);
	glEnable(GL_NORMALIZE);
	//  glEnable(GL_CULL_FACE);


	glRotatef(rot, 0, 1, 0);
	float ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	float diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	float specular[] = { 0.4, 0.4, 0.4, 1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	GLfloat light_position[] = { 0, 0.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);

	glPushMatrix();
	float fl[4];
	glRotatef(35, 1, 0, 0);
	fl[0] = 1; fl[1] = 1; fl[2] = 1; fl[3] = 0;
	//    glLightfv(GL_LIGHT2, GL_DIFFUSE, fl);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 80);
	fl[0] = 0; fl[1] = 0; fl[2] = -1; fl[3] = 0;
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, fl);
	fl[0] = 0; fl[1] = -5; fl[2] = 6; fl[3] = 1;
	glLightfv(GL_LIGHT2, GL_POSITION, fl);
	glPopMatrix();
	std:cout << con;
	if (con > 0)  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, con);
	else   glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
	GLfloat light0_position[] = { 0.0, 3.0, 0.0, 1.0 };
	glPushMatrix();
	glTranslatef(0, 0, tran);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glPopMatrix();
	GLfloat light0_dir[] = { 0.0, -1.0, 0.0 ,0.0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_dir);
}

void materia(int c) 
{
	switch (c)
	{
	case 1: // diffuse and specular reflection; low shininess; no ambient
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 2:  // diffuse and specular reflection; high shininess; no ambient
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 3:
		// diffuse and specular reflection; high shininess; no ambient
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 4:
		// diffuse reflection; emission; no ambient or specular reflection
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		break;
	case 5:
		// ambient and diffuse reflection; no specular
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 6:
		// ambient, diffuse and specular reflection; low shininess
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, 3);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 7:
		// ambient, diffuse and specular reflection; high shininess
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 8:
		// ambient and diffuse reflection; emission; no specular
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		break;
	case 9:
		// colored ambient and diffuse reflection; no specular
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 10:
		// colored ambient, diffuse and specular reflection; low shininess
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 11:
		// colored ambient, diffuse and specular reflection; high shininess
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 12:
		float fl[4];
		fl[0] = 0.7; fl[1] = 0.7; fl[2] = 0.7; fl[3] = 0;
		glMaterialfv(GL_FRONT, GL_AMBIENT, fl);
		fl[0] = 0.7; fl[1] = 0.8; fl[2] = 0.7; fl[3] = 0;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, fl);
		break;
	default:
		// colored ambient and diffuse reflection; emission; no specular
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	}
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
	GLfloat front_color[] = { 0,1,0,1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
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
	materia(ex);
	glColor3ub(planet.r, planet.g, planet.b);
	//glutSolidSphere(planet.radius, 100, 100);
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

void DrawAxes() {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);

	glEnd();
}

void DrawAxes2() {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(2, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 2);

	glEnd();
}

double DrawSnowMan()
{
	double rBigBall = 0.30;
	glPushMatrix();
	DrawAxes();
	glRotatef(-90, 0, 1, 0);
	glColor3ub(243, 246, 251);
	glutSolidSphere(rBigBall, 100, 100);
	glTranslated(0, rBigBall + rBigBall / 3.1, 0);
	glutSolidSphere(rBigBall / 3.0, 100, 100);
	glColor3ub(0, 0, 0);
	glPushMatrix();
	glTranslated(rBigBall / 3.0 * Cos20() * Cos20(), rBigBall / 3.0 * Sin20(), rBigBall / 3.0 * Sin20());
	glutSolidSphere(0.02, 100, 100);
	glTranslated(0, 0, -2 * rBigBall / 3.0 * 0.342);
	glutSolidSphere(0.02, 100, 100);
	glPopMatrix();
	glColor3ub(237, 145, 33);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslated(0, 0, rBigBall / 3.0);
	glutSolidCone(0.025, 0.2, 100, 100);
	glPopMatrix();
	glPopMatrix();
	return rBigBall;
}

void Scene()
{
	SolarSystem();
	DrawDeathStar();
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
		alfa = alfa - 2.0; 
	}
	else if (key == GLUT_KEY_DOWN) 
	{ 
		alfa = alfa + 2.0;
	}
	else if (key == GLUT_KEY_LEFT) { rot += 1; }
	else if (key == GLUT_KEY_RIGHT) { rot -= 1; }
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
	glViewport(0, 0, winWidth/2, winWidth/2);
	glLoadIdentity();
	DrawAxes2();
	Scene();
	glViewport(winWidth/2, 0, winWidth/2, winWidth/2);
	glLoadIdentity();
	glRotatef(90, 1, 0, 0);
	DrawAxes2();
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
	InitLight();
	glutMainLoop();
	return 0;
}


