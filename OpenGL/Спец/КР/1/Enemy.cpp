#include "Enemy.h"

double Cos20()
{
	return cos((20 * M_PI) / 180);
}

double Sin20()
{
	return sin((20 * M_PI) / 180);
}

double DrawSnowMan()
{
	double rBigBall = 0.30;
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glColor3ub(243, 246, 251);
	glTranslated(0, rBigBall, 0);
	glutSolidSphere(rBigBall, 100, 100);
	glTranslated(0, rBigBall + rBigBall / 3.1, 0);
	glutSolidSphere(rBigBall / 3.0, 100, 100);
	glColor3ub(0, 0, 0);
	glPushMatrix();
	glTranslated(rBigBall / 3.0 * Cos20() * Cos20(), rBigBall / 3.0 * Sin20(), rBigBall / 3.0 * Sin20());
	glutSolidSphere(0.02, 100, 100);
	glTranslated(0, 0, -2 * rBigBall / 3.0 * 0.342);
	glutSolidSphere(0.02, 100, 100);
	glPopMatrix();
	glColor3ub(237, 145, 33);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslated(0, 0, rBigBall / 3.0);
	glutSolidCone(0.025, 0.2, 100, 100);
	glPopMatrix();
	glPopMatrix();
	return rBigBall;
}