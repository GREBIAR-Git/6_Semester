#include "1.h"
#include "Light.h"
#include "Planet.h"
#include "Keyboard.h"

const int winWidth = 1400;

void Scene()
{
	Light();
	DrawDeathStar();
	SolarSystem();
}

void Initialize() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST); // включаем тест глубины. Если этого не сделать видимыми будут объекты не  расположенные ближе всего к наблюдателю, а созданные последними.
	glLoadIdentity();
}

void Display() {
	glClearColor(0.059, 0.059, 0.07, 1.0);// задаем цвет заливки холста
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, winWidth/2, winWidth/2);
	glLoadIdentity();
	Scene();
	glViewport(winWidth/2, 0, winWidth/2, winWidth/2);
	glLoadIdentity();
	glRotatef(-90, 1, 0, 0);
	Scene();
	glutSwapBuffers();
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);// -используем буфер глубины, двойную буферизацию и представление цвета триадой RGB.
	glutInitWindowSize(winWidth, winWidth/2);
	glutCreateWindow("SolarSystem");
	glutDisplayFunc(Display);//  назначаем функцию визуализации
	glutSpecialFunc(Specialkeys);// назначаем функцию обработки нажатия специальных клавиш
	Initialize();// дополнительные настройки конвейера
	InitLight();
	InitPlanet();
	glutMainLoop();
	return 0;
}


