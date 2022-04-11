#pragma once
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
/*

class Planet
{
public:
	void SetPlanet(float radius, float spead, int r, int g, int b);
	Planet(float radius, float spead, int r, int g, int b);
	Planet();
	~Planet();
	float GetRadius();
	float GetSpead();
	int r;
	int g;
	int b;

private:
	float radius;
	float spead;
};

Planet::Planet(float radius, float spead, int r, int g, int b)
{
	this->radius = radius;
	this->spead = spead;
	this->r = r;
	this->g = g;
	this->b = b;
}

Planet::Planet()
{

}

void Planet::SetPlanet(float radius, float spead, int r, int g, int b)
{
	this->radius = radius;
	this->spead = spead;
	this->r = r;
	this->g = g;
	this->b = b;
}

Planet::~Planet()
{
}

float Planet::GetRadius()
{
	return radius;
}

float Planet::GetSpead()
{
	return spead;
}*/
