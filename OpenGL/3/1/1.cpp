#include <iostream>

#include <glut.h>

using namespace std;

int rot, alfa, ex;

void DrawSun()
{
	glColor3ub(255, 215, 0);
	glTranslated(0, -1, 0);
	glutSolidSphere(0.3f, 100, 100);
	glEnd();
}

void DrawMercury()
{
	glColor3ub(239, 83, 36);
	glTranslated(-0.1f, 0, 0);
	glutSolidSphere(0.1f, 100, 100);
}

void DrawVenus()
{
	glColor3ub(235, 148, 35);
	glTranslated(0, -1, 0);
	glutSolidSphere(0.3f, 100, 100);
}

void DrawEarth()
{
	glColor3ub(121, 195, 97);
	glTranslated(0, -1, 0);
	glutSolidSphere(0.3f, 100, 100);
}

void DrawMars()
{
	glColor3ub(241, 115, 75);
	glTranslated(0, -1, 0);
	glutSolidSphere(0.3f, 100, 100);
}

void DrawJupiter()
{
	glColor3ub(144, 93, 29);
	glTranslated(0, -1, 0);
	glutSolidSphere(0.3f, 100, 100);
}

void DrawSaturn()
{
	glColor3ub(165, 110, 79);
	glTranslated(0, -1, 0);
	glutSolidSphere(0.3f, 100, 100);
}

void DrawUranus()
{
	glColor3ub(53, 220, 245);
	glTranslated(0, -1, 0);
	glutSolidSphere(0.3f, 100, 100);
}

void DrawNeptune()
{
	glColor3ub(40, 165, 221);
	glTranslated(0, -1, 0);
	glutSolidSphere(0.3f, 100, 100);
}

void DrawPluto()
{
	glColor3ub(255, 215, 0);
	glTranslated(0, -1, 0);
	glutSolidSphere(0.3f, 100, 100);
}

void DrawAxes()
{
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3d(0, 0, 0); //х
	glVertex3d(2, 0, 0);

	glVertex3d(0, 0, 0); //у
	glVertex3d(0, 2, 0);

	glVertex3d(-1, -1, 0);//z
	glVertex3d(-1, -1, 2);
	glEnd();
}

void SolarSystem()
{
	DrawMercury();
	DrawVenus();
	DrawEarth();
	DrawMars();
	DrawJupiter();
	DrawSaturn();
	DrawUranus();
	DrawNeptune();
	DrawPluto();
}

void Scene()
{
	DrawAxes();
	//SolarSystem();
}


void Initialize() {
	glClearColor(0.3, 0.3, 0.3, 1.0);// задаем цвет заливки холста
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);// задаем ортографическую проекцию и видимый объем
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST); // включаем тест глубины. Если этого не сделать видимыми будут объекты не  расположенные ближе всего к наблюдателю, а созданные последними.
	glLoadIdentity();
}

void Specialkeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) { rot = rot - 2.0; }
	else
		if (key == GLUT_KEY_RIGHT) { rot = rot + 2.0; }
		else
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

	glViewport(0, 0, 800, 800);
	glLoadIdentity();
	glRotatef(45, 1, 0, 0);
	//drawAxes();
	Scene();

	glViewport(800, 0, 800, 800);
	glLoadIdentity();
	glRotatef(90, 1, 0, 0);
	//drawAxes();
	Scene();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);// -используем буфер глубины, двойную буферизацию и представление цвета триадой RGB.
		glutInitWindowSize(800, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Our first GLUT application!");
	glutDisplayFunc(Display);//  назначаем функцию визуализации
		glutSpecialFunc(Specialkeys);// назначаем функцию обработки нажатия специальных клавиш
		Initialize();// дополнительные настройки конвейера
		glutMainLoop();
	return 0;
}


