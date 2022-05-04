#include "Light.h"
#include "Keyboard.h"
#include <glut.h>

float no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
float mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
float mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
float mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
float mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
float no_shininess = 0.0;
float low_shininess = 5.0;
float high_shininess = 100.0;
float mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

void Light()
{
	if (Sun())
	{
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}
	if(DeathStar())
	{
		glEnable(GL_LIGHT1);
	}
	else
	{
		glDisable(GL_LIGHT1);
	}
}

void InitLight() {
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	//glShadeModel(GL_SMOOTH);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHT0);
	float diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	float specular[] = { 0.4, 0.4, 0.4, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	GLfloat light_position[] = { 0, 0.0, 0.0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHT1);
	float specular1[] = { 0.4, 0.4, 0.4, 1.0 };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
	float diffuse1[] = { 0.8, 0.8, 0.8, 1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
}

void Materia(int c)
{
	switch (c)
	{
	case 1: // diffuse and specular reflection; low shininess; no ambient
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 2:  // diffuse and specular reflection; high shininess; no ambient
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 3:
		// diffuse and specular reflection; high shininess; no ambient
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 4:
		// diffuse reflection; emission; no ambient or specular reflection
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		break;
	case 5:
		// ambient and diffuse reflection; no specular
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 6:
		// ambient, diffuse and specular reflection; low shininess
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, 3);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 7:
		// ambient, diffuse and specular reflection; high shininess
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 8:
		// ambient and diffuse reflection; emission; no specular
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		break;
	case 9:
		// colored ambient and diffuse reflection; no specular
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 10:
		// colored ambient, diffuse and specular reflection; low shininess
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 11:
		// colored ambient, diffuse and specular reflection; high shininess
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 12:
		float fl[4];
		fl[0] = 0.7; fl[1] = 0.7; fl[2] = 0.7; fl[3] = 0;
		glMaterialfv(GL_FRONT, GL_AMBIENT, fl);
		fl[0] = 0.7; fl[1] = 0.8; fl[2] = 0.7; fl[3] = 0;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, fl);
		break;
	default:
		// colored ambient and diffuse reflection; emission; no specular
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	}
}