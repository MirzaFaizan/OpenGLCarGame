#include "GL/glut.h"
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<curses.h>
#include<cstdio>
#include<iostream>
#include<string.h>
#include<sstream>

void drawvehicle(){
    glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	glColor3f(0, 1, 0);
	glTranslatef(0.97, 0.19, 0);  //right path of road
	glScalef(0.56, 1.925, 0);
	glutSolidCube(2);



	glLoadIdentity();
	glColor3f(0, 1, 0);
	glTranslatef(-0.97, 0.19, 0);   //left path of road
	glScalef(0.56, 1.925, 0);
	glutSolidCube(2);

	glLoadIdentity();
	glColor3f(0.1f, 0.1f, 0.1f);
	glTranslatef(-0.01, 0.19, 0);   //left path of road
	glScalef(0.37, 1.925, 0);
	glutSolidCube(2);


	///white loans accoors rooad


	glLoadIdentity();
	glColor3f(1, 1, 1);
	glTranslatef(-0.01, 0.06, 0);   //left path of road
	glScalef(0.01, 0.3, 0);
	glutSolidCube(0.7);


	glLoadIdentity();
	glColor3f(1, 1, 1);
	glTranslatef(-0.01, 0.46, 0);   //left path of road
	glScalef(0.01, 0.3, 0);
	glutSolidCube(0.7);

	glLoadIdentity();
	glColor3f(1, 1, 0);
	glTranslatef(-0.01, -0.34, 0);   //center path of road
	glScalef(0.01, 0.3, 0);
	glutSolidCube(0.7);

	glLoadIdentity();
	glColor3f(1, 1, 1);
	glTranslatef(-0.01, -0.74, 0);   //center path of road
	glScalef(0.01, 0.3, 0);
	glutSolidCube(0.7);

	glLoadIdentity();
	glColor3f(0, 0, 1);
	glTranslatef(-0.01, -0.35, 0);   //truck rear cube
	glScalef(0.5, 0.5, 0);
	glutSolidCube(0.7);

	glLoadIdentity();
	glColor3f(0, 0, 1);
  	glTranslatef(-0.01, -0.15, 0);   //truck front cube
    glScalef(0.4, 0.5, 0);
	glutSolidCube(0.7);

	glLoadIdentity();
	glColor3f(0.5,0.5,0.5);
	glTranslatef(-0.01, -0.35, 0);   //rear cube inner black cube
	glScalef(0.45, 0.45, 0);
	glutSolidCube(0.7);

	glLoadIdentity();
	glColor3f(0, 0, 1);
	glTranslatef(-0.01, -0.35, 0);   //rear cube inner blue cube
	glScalef(0.4, 0.4, 0);
	glutSolidCube(0.7);

	glLoadIdentity();
	glColor3f(0.5,0.5,0.5);
	glTranslatef(-0.01, -0.09, 0);   //wind screen
	glScalef(0.3, 0.15, 0);
	glutSolidCube(0.7);


	glLoadIdentity();
	glColor3f(1,1,0);
	glTranslatef(-0.1, 0.013, 0);   //left light
	glScalef(0.1,0.05,0);
	glutSolidCube(0.7);


	glLoadIdentity();
	glColor3f(1, 1, 0);
	glTranslatef(0.08, 0.013, 0);   //right light
	glScalef(0.1, 0.05, 0);
	glutSolidCube(0.7);


	glFlush();
}

void display()
{
    drawvehicle();
    glFlush();
}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Racing Game");
	glutIdleFunc(display);

	glEnable(GL_DEPTH_TEST);
	
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}
