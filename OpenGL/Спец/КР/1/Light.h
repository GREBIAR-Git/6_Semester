#pragma once
#include <glut.h>
#include <windows.h>

void DrawFlashlight();

void DrawNaturalLight();

void DrawMoon();

void DrawSun();

void InitSun();

void InitMoon();

void InitFlashlight();

void InitLight();

void Materia(int c);


DWORD WINAPI SimulationDayNight(LPVOID lpParam);