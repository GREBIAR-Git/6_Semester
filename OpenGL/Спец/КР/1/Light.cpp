#include "Light.h"
#include "Movements.h"

float orbitSun = 270;// 360 - 90

void DrawFlashlight()
{
	float position[] = { 0,0,5,1 };
	glLightfv(GL_LIGHT2, GL_POSITION, position);
}

void DrawNaturalLight()
{
	if (int(orbitSun) % 360 >= 270 || int(orbitSun) % 360 <= 90)
	{
		if (GetStateSun())
		{
			DrawSun();//0-90 270-360   
		}
	}
	else
	{
		if (GetStateMoon())
		{
			DrawMoon();//91-268 270-360
		}
	}
}

void DrawSun()
{
	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT0);
	glPushMatrix();
	float position[] = { 0,0,55,1 };
	glRotatef(orbitSun, 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glTranslatef(0, 0, 55);
	glScalef(2, 2, 2);
	glColor3f(0.97, 0.84, 0.1);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glutSolidSphere(1, 100, 100);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
}

void DrawMoon()
{
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glPushMatrix();
	float position[] = { 0,0,55,1 };
	glRotatef(orbitSun-180, 0, 1, 0);
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glTranslatef(0, 0, 55);
	glColor3f(0.88, 0.97, 0.80);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glutSolidSphere(1, 100, 100);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
}

void InitLight()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	float ambient[] = { 0.05, 0.05, 0.05, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	InitSun();
	InitMoon();
	InitFlashlight();
	HANDLE threadM = CreateThread(NULL, 0, SimulationDayNight, NULL, CREATE_ALWAYS, NULL);
}

void InitSun()
{
	float diffuseSun[] = { 0.7, 0.7, 0.7, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseSun);
	float constant_attenuation[] = { 1 };
	float linear_attenuation[] = { 0 };
	float quadratic_attenuation[] = { 0 };
	glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constant_attenuation);
	glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, linear_attenuation);
	glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadratic_attenuation);
}

void InitMoon()
{
	float diffuseMoon[] = { 0.25, 0.25, 0.25, 1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseMoon);
}

void InitFlashlight()
{
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glEnable(GL_LIGHT2);
	float position[] = { 0,0,0,1 };
	glLightfv(GL_LIGHT2, GL_POSITION, position);
	float spot_direction[] = {0.1,0,0};
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
	glPopMatrix();
	float specular1[] = { 0.4, 0.4, 0.4, 1.0 };
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular1);
	float diffuse1[] = { 0.8, 0.8, 0.8, 1.0 };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse1);

	float spot_cutoff[] = {5};
	glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spot_cutoff);
	float spot_exponent[] = { 1 };
	glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, spot_exponent);

	glEnable(GL_LIGHT2);
	float position3[] = { 0,0,5,1 };
	glLightfv(GL_LIGHT2, GL_POSITION, position3);
}

DWORD WINAPI SimulationDayNight(LPVOID lpParam)
{
	while (true)
	{
		orbitSun += 0.1;
		if (orbitSun == 360)
		{
			orbitSun = 0;
		}
		Sleep(25);
	}
	return 0;
}

float no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
float mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
float mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
float mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
float mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
float no_shininess = 0.0;
float low_shininess = 5.0;
float high_shininess = 100.0;
float mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };


void Materia(int c)
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