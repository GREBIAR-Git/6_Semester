#include <windows.h>
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
struct Planet
{
	float radius;
	float spead;
	float r;
	float g;
	float b;
	float orbit;
};

const float rDeathStar = 0.20;
const float offset = 0.03;

void InitPlanet();

void DrawDeathStar();

float DrawPlanet(float orbit, Planet planet);

float DrawStar(float orbit, Planet planet);

void SolarSystem();

DWORD WINAPI SimulationSolarSystem(LPVOID lpParam);