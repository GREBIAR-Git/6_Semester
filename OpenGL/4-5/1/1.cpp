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
	glEnable(GL_DEPTH_TEST); // �������� ���� �������. ���� ����� �� ������� �������� ����� ������� ��  ������������� ����� ����� � �����������, � ��������� ����������.
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
		alfa = alfa + 2.0;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		alfa = alfa - 2.0;
	}
	else
	{
		alfa = 0;
	}
	glutPostRedisplay(); // �������������� ����� ������� ������������

}

void Display() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// ��� ��������
	glViewport(0, winHeight * 2 / 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(alfa, 0, 1, 0);
	glRotatef(rot, 1, 0, 0);
	Scene();

	//��� �������
	glViewport(winWidth / 4, winHeight * 2 / 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Scene();

	//��� �����
	glViewport(winWidth * 2 / 4, winHeight * 2 / 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(90, 0, -1, 0);
	Scene();

	//��� ������
	glViewport(winWidth * 3 / 4, winHeight * 2 / 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(90, 1, 0, 0);
	Scene();

	
	glViewport(0, winHeight / 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Scene();

	glViewport(winWidth / 4, winHeight/ 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Scene();

	//���������
	glViewport(winWidth * 2 / 4, winHeight/ 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(33, 1, -1, 0);
	Scene();

	glViewport(winWidth * 3 / 4, winHeight/ 3, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Scene();

	glViewport(0, 0, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Scene();

	glViewport(winWidth / 4, 0, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Scene();

	glViewport(winWidth * 2 / 4, 0, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Scene();

	glViewport(winWidth * 3 / 4, 0, winWidth / 4, winHeight / 3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Scene();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);// -���������� ����� �������, ������� ����������� � ������������� ����� ������� RGB.
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Our first GLUT application!");
	glutDisplayFunc(Display);//  ��������� ������� ������������
	glutSpecialFunc(Specialkeys);// ��������� ������� ��������� ������� ����������� ������
	Initialize();// �������������� ��������� ���������
	glutMainLoop();
	return 0;
}


