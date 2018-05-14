#include "GL/glut.h"

#include<stdlib.h>
#include<math.h>



float angle = 0.0f;
float lx=0.0f,lz=-1.0f;
float x=0.0f, z=5.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;

void reshape(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}
void drawSnowMan() 
{
glClearColor(0,0,1,0);
glColor3f(1.0f, 1.0f, 1.0f);


	glTranslatef(0.0f, 0.0f, 0.0f);
	glutSolidCube(2.0);


	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
}

void drawLine() 
{
glClearColor(0,0,1,0);
glColor3f(1.0f, 1.0f, 1.0f);


	glTranslatef(0.0f, 0.0f, 0.0f);
	glutSolidCube(2.0);


	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
}
void computePos(float deltaMove) 
{

	x += deltaMove * lx * 0.5f;
	z += deltaMove * lz * 0.5f;
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
	glColor3f(0.9f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	for(int i = -5; i < 5; i++)
		for(int j=-5; j < 5; j++) 
                                   {
			glPushMatrix();
			glTranslatef(i*3.0,0,j * 10.0);
			drawSnowMan();
			glPopMatrix();
			}

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
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	hellow();
	return 0;
}
