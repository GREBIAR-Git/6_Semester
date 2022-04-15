#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <glut.h>
#include<vector>

struct Planet
{
	float radius;
	float spead;
	int r;
	int g;
	int b;
};

double Cos20()
{
	return cos((20 * M_PI) / 180);
}

double Sin20()
{
	return sin((20 * M_PI) / 180);
}
