#pragma once
#include <glut.h>
#include <math.h>
#include <iostream>
#include "Light.h"

struct Room
{
	int width;
	int height;
	int left;
	int top;
	int right;
	int bottom;
};
void Materia(int c);

void InitMainRoom();

void DrawRoof(float x1, float y1, float x2, float y2, float height, float width);

void DrawWall(float x1, float y1, float x2, float y2, float height);

void DrawWall(float x1, float y1, float x2, float y2, float height, float width);

void DrawRoom(int x1, int y1, int x2, int y2, int height);

void DrawRoom3x(float x1, float y1, float x2, float y2, float height);

void DrawRoom3x(float x1, float y1, float x2, float y2, float height, float width);

void DrawRoom3y(int x1, int y1, int x2, int y2, int height);

void DrawRoom3y(int x1, int y1, int x2, int y2, int height, float width);

void DrawWallDoor(float x1, float y1, float x2, float y2, float height, float countDoor, bool nextRooms);

void DrawRoomDoor(int x1, int y1, int x2, int y2, int height, int lDoor, int tDoor, int rDoor, int bDoor);

void DrawRoomDoor3x(int x1, int y1, int x2, int y2, int height, int tDoor, int rDoor, int bDoor);

void DrawRoomDoor3y(int x1, int y1, int x2, int y2, int height, int lDoor, int tDoor, int rDoor);

void DrawFloor();

void DrawTerrain();

void InitTexture();
