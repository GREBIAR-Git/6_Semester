#include "House.h"
#include "Movements.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
const float w = 0.1;

Room room;

unsigned int texture[6];

void InitTexture()
{
	int width1 = 2, height1 = 2, cnt;

	unsigned char* image = stbi_load("floor.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("ceiling.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("wall.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("russia.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	image = stbi_load("9may.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);


	image = stbi_load("USSR.jpg", &width1, &height1, &cnt, 0);
	glGenTextures(1, &texture[5]);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);
}

void InitMainRoom()
{
	room.width = rand() % 10 + 10;
	room.height = rand() % 10 + 10;
	room.left = rand() % 5 + 1;
	room.top = rand() % 5 + 1;
	room.right = rand() % 5 + 1;
	room.bottom = rand() % 5 + 1;
}

void DrawRoof(float x1, float y1, float x2, float y2, float height, float width)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glColor3f(1, 1, 1);
	if (y1 > y2)
	{
		float y3 = y1;
		y1 = y2;
		y2 = y3;
	}
	if (x1 > x2)
	{
		float x3 = x1;
		x1 = x2;
		x2 = x3;
	}
	glBegin(GL_QUADS);
	for (float x = x1 ; x < x2 ; x += 0.1)
	{
		for (float y = y1 ; y < y2 ; y += 0.1)
		{
			glTexCoord2f(0, 0); glNormal3f(0, 0, -1); glVertex3f(x, y, height);
			glTexCoord2f(0, 1); glNormal3f(0, 0, -1); glVertex3f(x, y + 0.1, height);
			glTexCoord2f(1, 1); glNormal3f(0, 0, -1); glVertex3f(x + 0.1, y + 0.1, height);
			glTexCoord2f(1, 0); glNormal3f(0, 0, -1); glVertex3f(x + 0.1, y, height);
		}
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
}

void DrawWall(float x1, float y1, float x2, float y2, float height)
{
	DrawWall(x1, y1, x2, y2, height, w);
}

void DrawWall(float x1, float y1, float x2, float y2, float z1, float z2, float width)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	if (x1 == x2)
	{
		float normal = -1;
		if (width < 0)
		{
			normal = -normal;
		}
		if (y1 > y2)
		{
			float y3 = y1;
			y1 = y2;
			y2 = y3;
			width = -width;
			normal = -normal;
		}
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		float temp = y1;
		for (float i = y1; i + 0.1 <= y2; i += 0.1)
		{
			for (float f = z1; f + 0.1 <= z2; f += 0.1)
			{
				glTexCoord2f(0, 0); glNormal3f(normal, 0, 0); glVertex3f(x1, i, f);
				glTexCoord2f(0, 1); glNormal3f(normal, 0, 0); glVertex3f(x1, i, f + 0.1);
				glTexCoord2f(1, 1); glNormal3f(normal, 0, 0); glVertex3f(x2, i + 0.1, f + 0.1);
				glTexCoord2f(1, 0); glNormal3f(normal, 0, 0); glVertex3f(x2, i + 0.1, f);

				glTexCoord2f(0, 0); glNormal3f(-normal, 0, 0); glVertex3f(x1 + width, i, f);
				glTexCoord2f(0, 1); glNormal3f(-normal, 0, 0); glVertex3f(x1 + width, i, f + 0.1);
				glTexCoord2f(1, 1); glNormal3f(-normal, 0, 0); glVertex3f(x2 + width, i + 0.1, f + 0.1);
				glTexCoord2f(1, 0); glNormal3f(-normal, 0, 0); glVertex3f(x2 + width, i + 0.1, f);
			}
			temp = i;
		}

		for (float f = z1; f + 0.1 <= z2; f += 0.1)
		{
			glTexCoord2f(0, 0); glNormal3f(normal, 0, 0); glVertex3f(x1, temp, f);
			glTexCoord2f(0, 1); glNormal3f(normal, 0, 0); glVertex3f(x1, temp, f + 0.1);
			glTexCoord2f(1, 1); glNormal3f(normal, 0, 0); glVertex3f(x2, y2, f + 0.1);
			glTexCoord2f(1, 0); glNormal3f(normal, 0, 0); glVertex3f(x2, y2, f);

			glTexCoord2f(0, 0); glNormal3f(-normal, 0, 0); glVertex3f(x1 + width, temp, f);
			glTexCoord2f(0, 1); glNormal3f(-normal, 0, 0); glVertex3f(x1 + width, temp, f + 0.1);
			glTexCoord2f(1, 1); glNormal3f(-normal, 0, 0); glVertex3f(x2 + width, y2, f + 0.1);
			glTexCoord2f(1, 0); glNormal3f(-normal, 0, 0); glVertex3f(x2 + width, y2, f);
		}

		if (width < 0)
		{
			normal = -normal;
		}
		for (float f = z1; f + 0.1 <= z2; f += 0.1)
		{
			glNormal3f(0, normal, 0); glVertex3f(x1, y1, f);
			glNormal3f(0, normal, 0); glVertex3f(x1, y1, f + 0.1);
			glNormal3f(0, normal, 0); glVertex3f(x2 + width, y1, f + 0.1);
			glNormal3f(0, normal, 0); glVertex3f(x2 + width, y1, f);

			glNormal3f(0, -normal, 0); glVertex3f(x1, y2, f);
			glNormal3f(0, -normal, 0); glVertex3f(x1, y2, f + 0.1);
			glNormal3f(0, -normal, 0); glVertex3f(x2 + width, y2, f + 0.1);
			glNormal3f(0, -normal, 0); glVertex3f(x2 + width, y2, f);
		}

		for (float i = y1; i + 0.1 <= y2; i += 0.1)
		{
			glTexCoord2f(0, 0); glNormal3f(0, 0, -1); glVertex3f(x1, i, z1);
			glTexCoord2f(0, 1); glNormal3f(0, 0, -1); glVertex3f(x1 + width, i, z1);
			glTexCoord2f(1, 1); glNormal3f(0, 0, -1); glVertex3f(x1 + width, i + 0.1, z1);
			glTexCoord2f(1, 0); glNormal3f(0, 0, -1); glVertex3f(x1, i + 0.1, z1);
		}
		glEnd();
	}
	else
	{
		float normal = -1;
		if (width < 0)
		{
			normal = -normal;
		}
		if (x1 > x2)
		{
			float x3 = x1;
			x1 = x2;
			x2 = x3;
			width = -width;
			normal = -normal;
		}
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		float temp = x1;
		for (float i = x1; i + 0.1 <= x2; i += 0.1)
		{
			for (float f = z1; f + 0.1 <= z2; f += 0.1)
			{
				glTexCoord2f(0, 0); glNormal3f(0, normal, 0); glVertex3f(i, y1, f);
				glTexCoord2f(0, 1); glNormal3f(0, normal, 0); glVertex3f(i, y1, f + 0.1);
				glTexCoord2f(1, 1); glNormal3f(0, normal, 0); glVertex3f(i + 0.1, y2, f + 0.1);
				glTexCoord2f(1, 0); glNormal3f(0, normal, 0); glVertex3f(i + 0.1, y2, f);

				glTexCoord2f(0, 0); glNormal3f(0, -normal, 0); glVertex3f(i, y1 + width, f);
				glTexCoord2f(0, 1); glNormal3f(0, -normal, 0); glVertex3f(i, y1 + width, f + 0.1);
				glTexCoord2f(1, 1); glNormal3f(0, -normal, 0); glVertex3f(i + 0.1, y2 + width, f + 0.1);
				glTexCoord2f(1, 0); glNormal3f(0, -normal, 0); glVertex3f(i + 0.1, y2 + width, f);
			}
			temp = i;
		}

		for (float f = z1; f + 0.1 <= z2; f += 0.1)
		{
			glTexCoord2f(0, 0); glNormal3f(0, normal, 0); glVertex3f(temp, y1, f);
			glTexCoord2f(0, 1); glNormal3f(0, normal, 0); glVertex3f(temp, y1, f + 0.1);
			glTexCoord2f(1, 1); glNormal3f(0, normal, 0); glVertex3f(x2, y2, f + 0.1);
			glTexCoord2f(1, 0); glNormal3f(0, normal, 0); glVertex3f(x2, y2, f);

			glTexCoord2f(0, 0); glNormal3f(0, -normal, 0); glVertex3f(temp, y1 + width, f);
			glTexCoord2f(0, 1); glNormal3f(0, -normal, 0); glVertex3f(temp, y1 + width, f + 0.1);
			glTexCoord2f(1, 1); glNormal3f(0, -normal, 0); glVertex3f(x2, y2 + width, f + 0.1);
			glTexCoord2f(1, 0); glNormal3f(0, -normal, 0); glVertex3f(x2, y2 + width, f);
		}

		if (width < 0)
		{
			normal = -normal;
		}
		for (float f = z1; f + 0.1 <= z2; f += 0.1)
		{
			glNormal3f(normal, 0, 0); glVertex3f(x1, y1, f);
			glNormal3f(normal, 0, 0); glVertex3f(x1, y1, f + 0.1);
			glNormal3f(normal, 0, 0); glVertex3f(x1, y1 + width, f + 0.1);
			glNormal3f(normal, 0, 0); glVertex3f(x1, y1 + width, f);

			glNormal3f(-normal, 0, 0); glVertex3f(x2, y2, f);
			glNormal3f(-normal, 0, 0); glVertex3f(x2, y2, f + 0.1);
			glNormal3f(-normal, 0, 0); glVertex3f(x2, y2 + width, f + 0.1);
			glNormal3f(-normal, 0, 0); glVertex3f(x2, y2 + width, f);
		}

		for (float i = x1; i + 0.1 <= x2; i += 0.1)
		{
			glTexCoord2f(0, 0); glNormal3f(0, 0, -1); glVertex3f(i, y1, z1);
			glTexCoord2f(0, 1); glNormal3f(0, 0, -1); glVertex3f(i, y1 + width, z1);
			glTexCoord2f(1, 1); glNormal3f(0, 0, -1); glVertex3f(i + 0.1, y1 + width, z1);
			glTexCoord2f(1, 0); glNormal3f(0, 0, -1); glVertex3f(i + 0.1, y1, z1);
		}
		glEnd();
	}
	glBindTexture(GL_TEXTURE_2D, texture[2]);
}

void DrawWall(float x1, float y1, float x2, float y2, float height, float width)
{
	DrawWall(x1, y1, x2, y2, 0, height, width);
}

void DrawRoom(int x1, int y1, int x2, int y2, int height)
{
	DrawWall(x1, y1, x1, y2, height);
	DrawWall(x1, y2, x2, y2, height);
	DrawWall(x2, y2, x2, y1, height);
	DrawWall(x2, y1, x1, y1, height);
}

void DrawRoom3x(float x1, float y1, float x2, float y2, float height)
{
	DrawRoom3x(x1, y1, x2, y2, height, w);
}

void DrawRoom3x(float x1, float y1, float x2, float y2, float height, float width)
{
	DrawRoof(x1, y1, x2, y2, height, width);
	DrawWall(x1, y2, x2, y2, height, width);
	DrawWall(x2, y2, x2, y1, height, width);
	DrawWall(x2, y1, x1, y1, height, width);
}

void DrawRoom3y(int x1, int y1, int x2, int y2, int height)
{
	DrawRoom3y(x1, y1, x2, y2, height, w);
}

void DrawRoom3y(int x1, int y1, int x2, int y2, int height, float width)
{
	DrawRoof(x1, y1, x2, y2, height, width);
	DrawWall(x1, y1, x1, y2, height, width);
	DrawWall(x1, y2, x2, y2, height, width);
	DrawWall(x2, y2, x2, y1, height, width);
}

void DrawWallDoor(float x1, float y1, float x2, float y2, float height, float countDoor)
{
	DrawWallDoor(x1, y1, x2, y2, height, countDoor, true);
}

void DrawWallDoor(float x1, float y1, float x2, float y2, float height, float countDoor, bool nextRooms)
{
	float sizeDoor = 1;
	if (countDoor > 0)
	{
		if (x1 == x2)
		{
			float sizeWall = abs(y1 - y2);
			if (sizeWall >= sizeDoor * 3)
			{
				while (sizeWall < (sizeDoor * 2 * countDoor) + sizeDoor)
				{
					countDoor--;
				}
				float offsets = (sizeWall - (sizeDoor * countDoor)) / (countDoor + 1);
				bool inverse = false;
				float width = w;
				int normal = -1;
				if (y1 > y2)
				{
					int y3 = y1;
					y1 = y2;
					y2 = y3;
					width = -w;
					inverse = true;
					normal = -normal;
				}
				float y = y1;
				for (int i = 0; i < countDoor; i++)
				{
					DrawWall(x1, y, x2, y + offsets, height, width);
					y += offsets;
					DrawWall(x1, y, x2, y + sizeDoor, 2.2, height, width);
					y += sizeDoor;
					if (nextRooms)
					{
						if (inverse)
						{
							DrawRoom3x(x1, y - sizeDoor - offsets / 2, x2 + offsets + sizeDoor, y + offsets / 2, 3, width);
						}
						else
						{
							DrawRoom3x(x1, y - sizeDoor - offsets / 2, x2 - offsets - sizeDoor, y + offsets / 2, 3);
						}
					}
				}
				DrawWall(x1, y, x2, y + offsets, height, width);
			}
			else
			{
				DrawWall(x1, y1, x2, y2, height);
			}
		}
		else
		{
			float sizeWall = abs(x1 - x2);
			if (sizeWall >= sizeDoor * 3)
			{
				while (sizeWall < (sizeDoor * 2 * countDoor) + sizeDoor)
				{
					countDoor--;
				}
				float offsets = (sizeWall - (sizeDoor * countDoor)) / (countDoor + 1);
				bool inverse = false;
				float width = -w;
				int normal = 1;
				if (x1 > x2)
				{
					int x3 = x1;
					x1 = x2;
					x2 = x3;
					width = -width;
					inverse = true;
					normal = -normal;
				}
				float x = x1;
				for (int i = 0; i < countDoor; i++)
				{
					DrawWall(x, y1, x + offsets, y2, height, width);
					x += offsets;
					DrawWall(x, y1, x + sizeDoor, y1, 2.2, height, width);
					x += sizeDoor;
					if (nextRooms)
					{
						if (inverse)
						{
							DrawRoom3y(x - sizeDoor - offsets / 2, y1, x + offsets / 2, y2 - offsets - sizeDoor, 3, width);
						}
						else
						{
							DrawRoom3y(x - sizeDoor - offsets / 2, y1, x + offsets / 2, y2 + offsets + sizeDoor, 3);
						}
					}
				}
				DrawWall(x, y1, x + offsets, y2, height, width);
			}
			else
			{
				DrawWall(x1, y1, x2, y2, height);
			}
		}
	}
	else
	{
		DrawWall(x1, y1, x2, y2, height);
	}
}

void DrawRoomDoor(int x1, int y1, int x2, int y2, int height, int lDoor, int tDoor, int rDoor, int bDoor)
{
	DrawWallDoor(x1, y1, x1, y2, height, lDoor, true);
	DrawWallDoor(x1, y2, x2, y2, height, tDoor, true);
	DrawWallDoor(x2, y2, x2, y1, height, rDoor, true);
	DrawWallDoor(x2, y1, x1, y1, height, bDoor, false);
}

void DrawRoomDoor3x(int x1, int y1, int x2, int y2, int height, int tDoor, int rDoor, int bDoor)
{
	DrawRoof(x1, y1, x2, y2, height, w);
	DrawWallDoor(x1, y2, x2, y2, height, tDoor);
	DrawWallDoor(x2, y2, x2, y1, height, rDoor);
	DrawWallDoor(x2, y1, x1, y1, height, bDoor);
}

void DrawRoomDoor3y(int x1, int y1, int x2, int y2, int height, int lDoor, int tDoor, int rDoor)
{
	DrawRoof(x1, y1, x2, y2, height, w);
	DrawWallDoor(x1, y1, x1, y2, height, lDoor);
	DrawWallDoor(x1, y2, x2, y2, height, tDoor);
	DrawWallDoor(x2, y2, x2, y1, height, rDoor);
}

void DrawFloor()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	for (float x = 0; x < 1; x += 0.1)
	{
		for (float y = 0; y < 1; y += 0.1)
		{
			glTexCoord2f(0, 0); glNormal3f(0, 0, 1); glVertex3f(x, y, 0);
			glTexCoord2f(1, 0); glNormal3f(0, 0, 1); glVertex3f(x, y + 0.1, 0);
			glTexCoord2f(1, 1); glNormal3f(0, 0, 1); glVertex3f(x + 0.1, y + 0.1, 0);
			glTexCoord2f(0, 1); glNormal3f(0, 0, 1); glVertex3f(x + 0.1, y, 0);
		}
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void DrawPictures()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);

	glPushMatrix();
	glTranslated(20, 0, 2);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);


	glTexCoord2f(1, 1); glNormal3f(0, 0, 1); glVertex3f(0, -1, 0);
	glTexCoord2f(1, 0); glNormal3f(0, 0, 1); glVertex3f(0, -1, 1);
	glTexCoord2f(0, 0); glNormal3f(0, 0, 1); glVertex3f(0, 1, 1);
	glTexCoord2f(0, 1); glNormal3f(0, 0, 1); glVertex3f(0, 1, 0);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20, 0, 2);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);


	glTexCoord2f(1, 1); glNormal3f(0, 0, 1); glVertex3f(0, -1, 0);
	glTexCoord2f(1, 0); glNormal3f(0, 0, 1); glVertex3f(0, -1, 1);
	glTexCoord2f(0, 0); glNormal3f(0, 0, 1); glVertex3f(0, 1, 1);
	glTexCoord2f(0, 1); glNormal3f(0, 0, 1); glVertex3f(0, 1, 0);

	glEnd();
	glPopMatrix();

	//вверху
	glPushMatrix();
	glTranslated(0, -20, 2);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1); glNormal3f(0, 1, 0); glVertex3f(-4, 0, 0);
	glTexCoord2f(0, 0); glNormal3f(0, 1, 0); glVertex3f(-4, 0, 4);
	glTexCoord2f(1, 0); glNormal3f(0, 1, 0); glVertex3f(4, 0, 4);
	glTexCoord2f(1, 1); glNormal3f(0, 1, 0); glVertex3f(4, 0, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1); glNormal3f(0, 1, 0); glVertex3f(-13, 0, 0);
	glTexCoord2f(0, 0); glNormal3f(0, 1, 0); glVertex3f(-13, 0, 4);
	glTexCoord2f(1, 0); glNormal3f(0, 1, 0); glVertex3f(-5, 0, 4);
	glTexCoord2f(1, 1); glNormal3f(0, 1, 0); glVertex3f(-5, 0, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glNormal3f(0, 1, 0); glVertex3f(5, 0, 0);
	glTexCoord2f(0, 0); glNormal3f(0, 1, 0); glVertex3f(5, 0, 4);
	glTexCoord2f(1, 0); glNormal3f(0, 1, 0); glVertex3f(13, 0, 4);
	glTexCoord2f(1, 1); glNormal3f(0, 1, 0); glVertex3f(13, 0, 0);

	glEnd();
	glPopMatrix();
	//внизу
	glPushMatrix();
	glTranslated(0, 20, 2);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1); glNormal3f(0, -1, 0); glVertex3f(-4, 0, 0);
	glTexCoord2f(0, 0); glNormal3f(0, -1, 0); glVertex3f(-4, 0, 4);
	glTexCoord2f(1, 0); glNormal3f(0, -1, 0); glVertex3f(4, 0, 4);
	glTexCoord2f(1, 1); glNormal3f(0, -1, 0); glVertex3f(4, 0, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1); glNormal3f(0, -1, 0); glVertex3f(-13, 0, 0);
	glTexCoord2f(0, 0); glNormal3f(0, -1, 0); glVertex3f(-13, 0, 4);
	glTexCoord2f(1, 0); glNormal3f(0, -1, 0); glVertex3f(-5, 0, 4);
	glTexCoord2f(1, 1); glNormal3f(0, -1, 0); glVertex3f(-5, 0, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glNormal3f(0, -1, 0); glVertex3f(5, 0, 0);
	glTexCoord2f(0, 0); glNormal3f(0, -1, 0); glVertex3f(5, 0, 4);
	glTexCoord2f(1, 0); glNormal3f(0, -1, 0); glVertex3f(13, 0, 4);
	glTexCoord2f(1, 1); glNormal3f(0, -1, 0); glVertex3f(13, 0, 0);

	glEnd();
	glPopMatrix();




	glBindTexture(GL_TEXTURE_2D, 0);

}

void DrawTerrain()
{
	DrawPictures();
	DrawRoom(-20, -20, 20, 20, 2);
	for (int i = -20; i < 20; i++)
	{
		for (int f = -20; f < 20; f++)
		{
			glPushMatrix();
			glTranslated(i, f, 0);
			DrawFloor();
			glPopMatrix();
		}
	}
	float w = room.width / 2.0;
	float h = room.height / 2.0;
	DrawRoomDoor(-w, -h, w, h, 3, room.left, room.top, room.right, room.bottom);
}
