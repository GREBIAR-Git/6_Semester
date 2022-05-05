#include "Planet.h"
#include "Light.h"
#include "Keyboard.h"
#include <glut.h>

Planet planets[10];

double alfa;

float RandOrbit()
{
	return (rand() % 200) / 100.0 - 1;
}

void InitPlanet()
{
	srand(time(0));
	planets[0] = { 0.30, 0, 255, 215, 0, RandOrbit() };
	planets[1] = { 0.015, 4.5, 239, 83, 36, RandOrbit() };
	planets[2] = { 0.045, 1.5, 235, 148, 35, RandOrbit() };
	planets[3] = { 0.05, 1, 121, 195, 97, RandOrbit() };
	planets[4] = { 0.04, 1 / 2.0, 241, 115, 75, RandOrbit() };
	planets[5] = { 0.14, 1 / 12.0, 144, 93, 29, RandOrbit() };
	planets[6] = { 0.16, 1 / 30.0, 165, 110, 79, RandOrbit() };
	planets[7] = { 0.081, 1 / 84.0, 53, 220, 245, RandOrbit() };
	planets[8] = { 0.08, 1 / 165.0, 40, 165, 221, RandOrbit() };
	planets[9] = { 0.02, 1 / 248.0, 255, 215, 0, RandOrbit() };
	HANDLE threadM = CreateThread(NULL, 0, SimulationSolarSystem, NULL, CREATE_ALWAYS, NULL);
}

void DrawDeathStar()
{
	glLoadIdentity();
	GLfloat light_position1[] = { GetRotX(), GetRotY(), 2, 1 };


	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	GLfloat spot_direction[] = { 0,0,-2 };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	GLfloat spot_cutoff[] = { GetSpotAlfa()};
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);
	glPushMatrix();
	glColor3ub(91, 95, 104);
	glTranslated(2, 2, 2);
	glutSolidSphere(rDeathStar, 100, 100);
	glPopMatrix();
}

float DrawPlanet(float orbit, Planet planet)
{
	glPushMatrix();
	glRotatef(alfa * planet.spead, 0, planet.orbit, 1);
	glColor3ub(planet.r, planet.g, planet.b);
	glTranslated(orbit + offset + planet.radius, 0, 0);
	glutSolidSphere(planet.radius, 100, 100);
	orbit += (offset + planet.radius * 2);
	glPopMatrix();
	return orbit;
}

float DrawStar(float orbit, Planet planet)
{
	glPushMatrix();
	Materia(GetKey());
	glColor3ub(255, 215, 0);
	glDisable(GL_LIGHTING);
	glutSolidSphere(planet.radius, 100, 100);
	glEnable(GL_LIGHTING);
	orbit += (planet.radius);
	glPopMatrix();
	return orbit;
}

void DrawRing(Planet planet, float orbitRing)
{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < 50; ii++)
	{
		float theta = 2 * 3.1415926f * float(ii) / float(50);

		float x = (planets[5].radius + orbitRing) * cosf(theta);
		float y = (planets[5].radius + orbitRing) * sinf(theta);

		glVertex2f(x, y);
	}
	glEnd();
}

void DrawRings(float orbit, Planet planet)
{
	glPushMatrix();
	glRotatef(alfa * planet.spead, 0, planet.orbit, 1);
	glColor3ub(planet.r, planet.g, planet.b);
	glTranslated(orbit + offset + planet.radius, 0, 0);
	glRotatef(35, 1, 0, 0);
	glColor3ub(255, 20, 147);
	glBegin(GL_LINE_LOOP);
	DrawRing(planet, 0.03);
	DrawRing(planet, 0.02);
	DrawRing(planet, 0.01);
	glPopMatrix();
}

void SolarSystem()
{
	if (GetWall())
	{
		for (float i = -2; i < 2; i += 0.1)
		{
			for (float f = -2; f < 2; f += 0.1)
			{
				glPushMatrix();
				glTranslated(i, f, 0);
				glutSolidCube(0.1);
				glPopMatrix();
			}
		}
	}
	float orbit = 0;
	orbit = DrawStar(orbit, planets[0]);
	Materia(1);
	for (int i = 1; i < 10; i++)
	{
		if (i == 5)
		{
			DrawRings(orbit, planets[i]);
		}
		orbit = DrawPlanet(orbit, planets[i]);
	}
}

DWORD WINAPI SimulationSolarSystem(LPVOID lpParam)
{
	while (true)
	{
		//alfa += 5;
		Sleep(25);
	}
	return 0;
}