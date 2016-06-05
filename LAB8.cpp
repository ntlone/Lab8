#include "stdafx.h"
#include <GL/freeglut.h>

float angle = 0.0f;

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	glEnable(GL_STENCIL_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotated(angle, 1, 0, 0);
	glRotated(angle, 0, 1, 0);
	glRotated(angle, 0, 0, 1);

	glStencilFunc(GL_ALWAYS, 1, 0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glPushMatrix();
	glutSolidCube(2);
	glPopMatrix();

	glStencilFunc(GL_ALWAYS, 2, 0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glutSolidSphere(1.2, 100, 100);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_STENCIL_TEST);
	glColor3d(5.0, 1, 0.3);
	glutSolidSphere(0.5, 100, 100);
	glColor3d(3.0, 0.1, 2.0);
	glutSolidTorus(0.15, 0.6, 80, 100);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_EQUAL, 1, 255);
	glColor3d(2, 6, 10);
	glutSolidCube(10);

	glPopMatrix();

	angle += 0.5f;

	glutSwapBuffers();
}


void resize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(70.0f, (float)width / (float)height, 0.1, 1000);

}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);
	glutCreateWindow("Lab 8");

	glClearColor(1.0, 1.0, 1.0, 1.0);

	float pos[4] = { 3, 3, 3, 1 };
	float dir[3] = { -1, -1, -1 };

	GLfloat mat_specular[] = { 1, 1, 1, 1 };

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutIdleFunc(idle);

	glEnable(GL_DEPTH_TEST);


	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

	glutMainLoop();

	return 0;
}