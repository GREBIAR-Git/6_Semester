#include "Keyboard.h"
#include <glut.h>

int ex,rot;
bool sun = true, deathStar = true;

int GetKey()
{
	return ex;
}

int GetRot()
{
	return rot;
}

bool Sun()
{
	return sun;
}

bool DeathStar()
{
	return deathStar;
}

void Specialkeys(int key, int x, int y)
{
	if (GLUT_KEY_LEFT)
	{
		sun = !sun;
	}
	else if (GLUT_KEY_RIGHT)
	{
		deathStar = !deathStar;
	}
	ex = key;
	glutPostRedisplay();
}