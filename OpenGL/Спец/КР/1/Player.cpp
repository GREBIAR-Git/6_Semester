#include "Player.h"
Player player = { 0,0,85,0 };

double GetXPlayer()
{
	return player.x;
}

double GetYPlayer()
{
	return player.y;
}

double GetXAlfaPlayer()
{
	return player.xAlfa;
}

double GetzAlfaPlayer()
{
	return player.zAlfa;
}

void SetXPlayer(double x)
{
	player.x = x;
}

void SetYPlayer(double y)
{
	player.y = y;
}

void SetXAlfaPlayer(double xAlfa)
{
	player.xAlfa = xAlfa;
}

void SetZAlfaPlayer(double zAlfa)
{
	player.zAlfa = zAlfa;
}

void PlusXPlayer(double x)
{
	player.x += x;
}

void PlusYPlayer(double y)
{
	player.y += y;
}

void PlusXAlfaPlayer(double xAlfa)
{
	player.xAlfa += xAlfa;
}

void PlusZAlfaPlayer(double zAlfa)
{
	player.zAlfa += zAlfa;
}