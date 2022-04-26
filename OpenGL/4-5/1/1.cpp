#include "1.h"

float alfa,rot;

void DrawAxes()
{
	glBegin(GL_LINES);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);

	glEnd();
}

void DrawModel() 
{

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0, 0.5, 0.5);
	glVertex3f(0, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.7, 0.9);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0, 0.5, -0.5);
	glVertex3f(0, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0, 0.5, 0.5);
	glVertex3f(0, 0.5, -0.5);
	glVertex3f(0, 0, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0, -0.5, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 1);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 1);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();

	glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslated(0.2, 0.2, 0.2);
		glutSolidSphere(0.2, 100, 100);
	glPopMatrix();
}

void Scene()
{
	DrawAxes();
	DrawModel();
}

void Initialize() {
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST); // включаем тест глубины. Если этого не сделать видимыми будут объекты не  расположенные ближе всего к наблюдателю, а созданные последними.
	glLoadIdentity();
}

void Specialkeys(int key, int x, int y) 
{
	if (key == GLUT_KEY_UP) 
	{
		rot = rot - 2.0; 
	}
	else if (key == GLUT_KEY_DOWN) 
	{ 
		rot = rot + 2.0;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		alfa = alfa - 2.0;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		alfa = alfa + 2.0;
	}
	else
	{
		alfa = 0;
		rot = 0;
	}
	glutPostRedisplay(); // принудительный вызов функции визуализации

}

void Display() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// для вращения ✓
	glViewport(0, winHeight * 2 / 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(alfa, 0, 1, 0);
	glRotatef(rot, 1, 0, 0);
	Scene();

	//вид спереди ✓
	glViewport(winWidth / 4, winHeight * 2 / 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Scene();

	//вид сбоку ✓
	glViewport(winWidth * 2 / 4, winHeight * 2 / 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(90, 0, -1, 0);
	Scene();

	//вид сверху ✓
	glViewport(winWidth * 3 / 4, winHeight * 2 / 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(90, 1, 0, 0);
	Scene();

	//одноточечная
	glViewport(0, winHeight / 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glFrustum(-1.5, 0.5, -1.5, 0.5, 2, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.5, -0.5, -3);
	Scene();

	//триметрическая
	glViewport(winWidth / 4, winHeight/ 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(20, 1, 0, 0);
	glRotatef(15, 0, 1, 0);
	Scene();

	//диметрическая
	glViewport(winWidth * 2 / 4, winHeight/ 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	double f = (5.0 / 8);
	glRotatef(asin(f/ sqrt(2)) * 180 / M_PI, 1, 0, 0);
	glRotatef(asin(f / sqrt(2 - f * f)) * 180 / M_PI, 0, -1, 0);
	Scene();

	//изометрическая
	glViewport(winWidth * 3 / 4, winHeight/ 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(asin(tan(30 * M_PI / 180))*180/M_PI, 1, 0, 0);
	glRotatef(45, 0, -1, 0);
	Scene();

	//двуточечная
	glViewport(0, 0, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 2, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -3);
	glRotatef(30, 1, 0, 0);
	Scene();

	//трёхточечная
	glViewport(winWidth / 4, 0, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 2, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -3);
	glRotatef(30, 1, 0, 0);
	glRotatef(45, 0, -1, 0);
	glRotatef(22.44, 0, 0, 1);
	Scene();

	//кавалье
	glViewport(winWidth * 2 / 4, 0, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat  a[16];
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, a);
	double angle = 45 * M_PI / 180;
	double gamma = 45 * M_PI / 180;
	a[8] = (M_PI / 2 - atan(gamma)) * (-cos(angle));
	a[9] = (M_PI / 2 - atan(gamma)) * (-sin(angle));
	glLoadMatrixf(a);
	Scene();
	
	//кабине
	glViewport(winWidth * 3 / 4, 0, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, a);
	angle = 30 * M_PI / 180;
	gamma = (M_PI/2 - atan(1/2));
	a[8] = (M_PI / 2 - atan(gamma)) * (-cos(angle));
	a[9] = (M_PI / 2 - atan(gamma)) * (-sin(angle));
	glLoadMatrixf(a);
	Scene();
	
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);// -используем буфер глубины, двойную буферизацию и представление цвета триадой RGB.
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Our first GLUT application!");
	glutDisplayFunc(Display);//  назначаем функцию визуализации
	glutSpecialFunc(Specialkeys);// назначаем функцию обработки нажатия специальных клавиш
	Initialize();// дополнительные настройки конвейера
	glutMainLoop();
	return 0;
}


