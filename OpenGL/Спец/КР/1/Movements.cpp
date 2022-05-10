#include "Movements.h"
#include "Light.h"

int width, height;

bool flashlight = true;

bool sun = true;

bool moon = true;

int key1;

bool GetStateSun()
{
	return sun;
}

bool GetStateMoon()
{
	return moon;
}

bool GetStateFlashlight()
{
	return flashlight;
}

int GetKey()
{
	return 1;
}

void SetWidth(int w)
{
	width = w;
}

void SetHeight(int h)
{
	height = h;
}

Player player = {0,0,85,0};

bool fullScreen = false;

float GetSpeed()
{
	if (GetKeyState(VK_SHIFT) < 0)
	{
		return 0.2;
	}
	else
	{
		return 0.1;
	}
}

void KeyboardProcessing()
{
	if (GetKeyState('W') < 0)
	{
		float speed = GetSpeed();
		player.x += sin(-player.zAlfa / 180 * M_PI) * speed;
		player.y += cos(-player.zAlfa / 180 * M_PI) * speed;
	}
	if (GetKeyState('S') < 0)
	{
		float speed = -GetSpeed();
		player.x += sin(-player.zAlfa / 180 * M_PI) * speed;
		player.y += cos(-player.zAlfa / 180 * M_PI) * speed;
	}
	if (GetKeyState('A') < 0)
	{
		float speed = GetSpeed();
		player.x += sin(-player.zAlfa / 180 * M_PI - 0.5 * M_PI) * speed;
		player.y += cos(-player.zAlfa / 180 * M_PI - 0.5 * M_PI) * speed;
	}
	if (GetKeyState('D') < 0)
	{
		float speed = GetSpeed();
		player.x += sin(-player.zAlfa / 180 * M_PI + 0.5 * M_PI) * speed;
		player.y += cos(-player.zAlfa / 180 * M_PI + 0.5 * M_PI) * speed;
	}

	if (GetKeyState('F') < 0)
	{
		flashlight = !flashlight;
		if (flashlight)
		{
			glEnable(GL_LIGHT2);
		}
		else
		{
			glDisable(GL_LIGHT2);
		}
	}
	if (GetKeyState('1') < 0)
	{
		glEnable(GL_LIGHT0);
		sun = true;
	}
	if (GetKeyState('2') < 0)
	{
		glDisable(GL_LIGHT0);
		sun = false;
	}
	if (GetKeyState('3') < 0)
	{
		glEnable(GL_LIGHT1);
		moon = true;
	}
	if (GetKeyState('4') < 0)
	{
		glDisable(GL_LIGHT1);
		moon = false;
	}

}

void NormalKeyboardProcessing(unsigned char key, int x, int y)
{
	/*
	if (key == 'w' || key == 'W' || key == 246 || key == 214 || keys.up)
	{
		keys.up = true;
		float speed = GetSpeed();
		player.x += sin(-player.zAlfa / 180 * M_PI) * speed;
		player.y += cos(-player.zAlfa / 180 * M_PI) * speed;
	}
	if (key == 's' || key == 'S' || key == 251 || key == 219 || keys.down)
	{
		keys.down = true;
		float speed = -GetSpeed();
		player.x += sin(-player.zAlfa / 180 * M_PI) * speed;
		player.y += cos(-player.zAlfa / 180 * M_PI) * speed;
	}
	if (key == 'a' || key == 'A' || key == 244 || key == 212 || keys.left)
	{
		keys.left = true;
		float speed = GetSpeed();
		player.x += sin(-player.zAlfa / 180 * M_PI - 0.5 * M_PI) * speed;
		player.y += cos(-player.zAlfa / 180 * M_PI - 0.5 * M_PI) * speed;
	}
	if (key == 'D' || key == 'd' || key == 226 || key == 194 || keys.right)
	{
		keys.right = true;
		float speed = GetSpeed();
		player.x += sin(-player.zAlfa / 180 * M_PI + 0.5 * M_PI) * speed;
		player.y += cos(-player.zAlfa / 180 * M_PI + 0.5 * M_PI) * speed;
	}*/
	if (key == 27)
	{
		exit(0);
	}
	glutPostRedisplay();
}

void SpecialKeyboardProcessing(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		player.xAlfa = ++player.xAlfa > 180 ? 180 : player.xAlfa;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		player.xAlfa = --player.xAlfa < 0 ? 0 : player.xAlfa;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		player.zAlfa += 1;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		player.zAlfa -= 1;
	}
	else if (key == GLUT_KEY_F11)
	{
		if (fullScreen)
		{
			glutInitWindowSize(700, 700);
			glutPositionWindow(0, 0);
		}
		else
		{
			glutFullScreen();
		}
		fullScreen = !fullScreen;
	}
	else
	{
		key1 = key;
	}
	glutPostRedisplay();
}

void MoveCamera()
{
	glRotatef(-player.xAlfa, 1, 0, 0);
	glRotatef(-player.zAlfa, 0, 0, 1);
	glTranslatef(-player.x, -player.y, -1);
}

void MouseMove(int x, int y)
{
	float zSpeed = 0.55, xSpeed = 0.5;
	player.zAlfa += (width / 2 - x) * zSpeed;
	int offset = (height / 2 - y);
	if (player.xAlfa + offset > 180)
	{
		player.xAlfa = 180;
	}
	else if (player.xAlfa + offset < 0)
	{
		player.xAlfa = 0;
	}
	else
	{
		player.xAlfa += offset * xSpeed;
	}
	glutWarpPointer(width / 2, height / 2);
	glutPostRedisplay();
}