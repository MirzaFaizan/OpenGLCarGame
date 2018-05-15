#include "GL/glut.h"
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<curses.h>
#include<cstdio>
#include<iostream>
#include<string.h>
#include<sstream>

using namespace std;


void *font = GLUT_BITMAP_TIMES_ROMAN_24;
void *fonts[] =

{

  GLUT_BITMAP_9_BY_15,
  GLUT_BITMAP_TIMES_ROMAN_10,
  GLUT_BITMAP_TIMES_ROMAN_24
};

// structure of block

struct block {
	int x;
	int y;
};

float angle = 0.0f;
float lx=0.0f,lz=-1.0f;
float x=0.0f, z=5.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;
block blocks[10];
#define PI 3.1415927

/************************** draw_cylinder() **************************
* This function will draw the cylinder
*
*   @parameter1: radius = The radius of cylinder
*   @parameter2: height = Height of the cylinder
*   @parameter3: R = Red value of the cylinder's color
*   @parameter4: G = Green value of the cylinder's color
*   @parameter5: B = Blue value of the cylinder's color
*
*   @return: Nothing
*/
void draw_cylinder(GLfloat radius,
	GLfloat height,
	GLubyte R,
	GLubyte G,
	GLubyte B)
{
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	/** Draw the tube */
	glColor3ub(R - 40, G - 40, B - 40);
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	/** Draw the circle on top of cylinder */
	glColor3ub(R, G, B);
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();
}

void reshape(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(2, 2, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}
void drawRoadBlock() 
{
	glClearColor(0,0,1,0);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(1,0.7,0.3);
	glColor3f(0.0f, 1.0f , 0.0f);
	glutSolidCube(2.0);
	glPopMatrix();
	
}

void drawPointSphere(float z){
	glClearColor(0,0,1,0);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, z);
	glScalef(2,0.7,0.3);
	glColor3f(1.0f, 1.0f , 0.0f);
	glutSolidSphere(0.5,20,20);
	glPopMatrix();
}

void drawCloud(){
	glClearColor(0,0,1,0);
	glColor3f(1,1,0.9);
	glPushMatrix();
	glTranslatef(5,5,-0.3);
	glutSolidSphere(1,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,4.5,0);
	glutSolidSphere(1,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5,5,0.2);
	glutSolidSphere(1.2,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5,4.3,0.5);
	glutSolidSphere(1,20,20);
	glPopMatrix();
	
}

// for displaying score

void output(int x, int y, char *string)
{
  int len, i;

  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}


void drawStrip(){
	glClearColor(0,0,1,0);
	glTranslatef(0.0f, 0.0f, 5.0f);
	glScalef(1,0.01,0.2);
	glColor3f(1.0f, 1.0f , 1.0f);
	glutSolidCube(2.0);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
}

void drawCar(float x, float z){
	glClearColor(0,0,1,0);
	glTranslatef(x+6, 0.0f, z);
	glScalef(2,0.3,0.5);
	glColor3f(255.0f, 0.0f , 0.0f);
	glutSolidCube(3.0);
	glPushMatrix();
	glTranslatef(0.0f, 0.2f, -2.0f);
	glScalef(1,0.3,0.3);
	glColor3f(0.5f, 0.5f , 0.5f);
	glutSolidCube(3.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.2f, 2.0f);
	glScalef(1,0.3,0.3);
	glColor3f(0.5f, 0.5f , 0.5f);
	glutSolidCube(3.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 0.0f);
	glScalef(1,0.3,0.3);
	glColor3f(0.5f, 0.5f , 0.5f);
	glutSolidCube(3.0);
	glPopMatrix();
	glColor3f(1,1,1);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);

}

void computePos(float deltaMove) 
{
	if(z>9){
		z=z-1;
	}
	if(z<1.2){
		z=z+1;
	}
	else{
	x += deltaMove * lx * 0.5f;
	z += deltaMove * lz * 0.5f;
	}
}

void computeDir(float deltaAngle)
{

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}


void display(void) {

	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(x, 1.0f, z, x+lx , 1.0f,  z+lz,0.0f, 1.0f,  0.0f);
	glColor3f(0.1f, 0.1f, 0.1f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 400.0f, 0.0f,  400.0f);
		glVertex3f( 400.0f, 0.0f, -400.0f);
	glEnd();

	bool check = true;
	for(int i = 0; i < 100; i++){
		for(int j=0; j < 2; j++){
			glPushMatrix();
			glTranslatef(i*2.5,0,j * 10.0);
			drawRoadBlock();
			if(check && i%8==0){
				drawPointSphere(4);
			}
			if(check && i%4==0){
				drawCloud();
			}
			drawStrip();
			glPopMatrix();
			
		}
	}
		drawCar(x,z);
// TO print OUTPUT
		stringstream stream;
		stream << (x);
		string s = stream.str();
		int size = s.length();
		char aa[size+1];
		strcpy(aa,s.c_str());
		output(0,3,aa);
		glutSwapBuffers();
}

void pressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.05f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.05f; break;
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}
}


void releaseKey(int key, int x, int y) {
switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}	
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Racing Game");
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glEnable(GL_DEPTH_TEST);
	
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}
