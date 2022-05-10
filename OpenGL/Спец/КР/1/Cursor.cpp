#include "Cursor.h"

void DrawCursor()
{
	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glScalef(0.1, 0.1, 1);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-0.04, 0, 0);
	glVertex3f(-0.01, 0, 0);

	glVertex3f(0.01, 0, 0);
	glVertex3f(0.04, 0, 0);

	glVertex3f(0, -0.04, 0);
	glVertex3f(0, -0.01, 0);

	glVertex3f(0, 0.01, 0);
	glVertex3f(0, 0.04, 0);

	glEnd();
	glPopMatrix();
}