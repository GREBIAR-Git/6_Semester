#pragma once
#include <glut.h>
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>

struct Player
{
	double x;
	double y;
	double xAlfa;
	double zAlfa;
};

bool GetStateSun();

bool GetStateMoon();

bool GetStateFlashlight();

int GetKey();

float GetSpeed();

void KeyboardProcessing();

void NormalKeyboardProcessing(unsigned char key, int x, int y);

void SpecialKeyboardProcessing(int key, int x, int y);

void MoveCamera();

void MouseMove(int x, int y);

void SetWidth(int w);

void SetHeight(int h);