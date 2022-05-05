#include "Keyboard.h"
#include <glut.h>


bool wall = false;
int ex, spotLightAlfa=90;
float rotX, rotY;
bool sun = true, deathStar = true;

int GetKey()
{
	return ex;
}

float GetRotX()
{
	return rotX;
}

float GetRotY()
{
	return rotY;
}

int GetSpotAlfa()
{
	return spotLightAlfa;
}

bool Sun()
{
	return sun;
}

bool DeathStar()
{
	return deathStar;
}

bool GetWall()
{
	return wall;
}

void Specialkeys(int key, int x, int y)
{
	if (GLUT_KEY_F1 == key)
	{
		rotX += 0.01;
	}
	else if (GLUT_KEY_F2 == key)
	{
		rotX -= 0.01;
	}
	else if (GLUT_KEY_F3 == key)
	{
		rotY += 0.01;
	}
	else if (GLUT_KEY_F4 == key)
	{
		rotY -= 0.01;
	}
	else if (GLUT_KEY_F5 == key)
	{
		spotLightAlfa -= 1;
		if (spotLightAlfa > 180)
		{
			spotLightAlfa = 180;
		}
	}
	else if (GLUT_KEY_F6 == key)
	{
		spotLightAlfa += 1;
		if(spotLightAlfa<0)
		{
			spotLightAlfa = 0;
		}
	}
	else if (GLUT_KEY_LEFT==key)
	{
		sun = !sun;
	}
	else if (GLUT_KEY_RIGHT==key)
	{
		deathStar = !deathStar;
	}
	else if (GLUT_KEY_UP == key)
	{
		glDisable(GL_LIGHT2);
	}
	else if (GLUT_KEY_DOWN == key)
	{
		glEnable(GL_LIGHT2);
	}
	else if (GLUT_KEY_F7 == key)
	{
		wall = !wall;
	}
	else
	{
		ex = key;
	}
	glutPostRedisplay();
}