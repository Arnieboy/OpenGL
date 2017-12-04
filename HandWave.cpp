#include <stdio.h>
#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <gl/glut.h>

int rightHandAngle = 180;
bool mouseLeftState = false;
bool mouseRightState = false;
int rightHandMove = 2;
int leftLegMove = 1;
int rightLegMove = -1;
int leftLegAngle = 90;
int rightLegAngle = 90;
float zMove = 0.0;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	glPushMatrix(); //HEAD
	glColor3f(1.0, 0.8, 0.6);
	glPushMatrix();
	glTranslatef(0.0, 300, zMove);
	GLUquadricObj* head = gluNewQuadric();
	gluQuadricDrawStyle(head, GLU_FILL);
	gluDisk(head, 0, 100, 50, 1);
	glPopMatrix();

	glPushMatrix(); //BODY  
	glColor3f(0, 0.5, 0.2);
	glTranslatef(0.0, 200, zMove);
	glRotatef(90, 1.0, 0.0, 0.0);
	GLUquadricObj* body = gluNewQuadric();
	gluQuadricDrawStyle(body, GLU_FILL);
	gluCylinder(body, 100, 100, 300, 30, 1);
	glPopMatrix();  

	glPushMatrix(); //LEFT ARM
	glColor3f(1.0, 0.8, 0.6);
	glTranslatef(-120, 200, zMove);
	glRotatef(0, 0.0, 0.0, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	GLUquadricObj* leftLowerArm = gluNewQuadric();
	gluQuadricDrawStyle(leftLowerArm, GLU_FILL);
	gluCylinder(leftLowerArm, 20, 20, 250, 30, 1);
	glPopMatrix();  

	glPushMatrix(); //RIGHT ARM
	glColor3f(1.0, 0.8, 0.6);
	glTranslatef(100, 180, zMove);
	glRotatef((GLfloat)rightHandAngle, 0.0, 0.0, 1.0);
	glRotatef(90, 1.0, -1.0, 0.0);
	GLUquadricObj* rightLowerArm = gluNewQuadric();
	gluQuadricDrawStyle(rightLowerArm, GLU_FILL);
	gluCylinder(rightLowerArm, 20, 20, 250, 30, 1);
	glPopMatrix();  

         glPushMatrix(); //LEFT LEG  
         glColor3f(0, 0.3f, 0.5f);  
         glTranslatef(-50, -100, zMove);  
         glRotatef(0, 0.0, 0.0, 1.0);  
         glRotatef((GLfloat)leftLegAngle, 1.0, 0.0, 0.0);  
         GLUquadricObj* leftLeg = gluNewQuadric();  
         gluQuadricDrawStyle(leftLeg, GLU_FILL);  
         gluCylinder(leftLeg, 20, 20, 200, 30, 30);  
         glPopMatrix();  

         glPushMatrix(); //RIGHT LEG  
         glColor3f(0, 0.3f, 0.5f);  
         glTranslatef(50, -100, zMove);  
         glRotatef(0, 0.0, 0.0, 1.0);  
         glRotatef((GLfloat)rightLegAngle, 1.0, 0.0, 0.0);  
         GLUquadricObj* rightLeg = gluNewQuadric();  
         gluQuadricDrawStyle(rightLeg, GLU_FILL);  
         gluCylinder(rightLeg, 20, 20, 200, 30, 30);  
         glPopMatrix();  
  
         if (mouseLeftState == true)
		 { // If left mouse clicked right hand of object will shake its lower arm  
             if (rightHandAngle >= 225) 
			 { // If angle is greater than 225 incrementing degree will become decrement  
                 rightHandMove = -rightHandMove;  
             }  
             else if (rightHandAngle <= 135)
			 { // If angle is lower than 135 decrementing degree will become increment  
                 rightHandMove = -rightHandMove;  
             }  
             rightHandAngle = (rightHandAngle + rightHandMove) % 360; // changing angle of right hand.  
         }  
         if (mouseRightState == true)
		 { // If right mouse clicked the object will ve moved and legs' angles will be changed.  
             if (leftLegAngle > 110)
			 {  
                 leftLegMove = -leftLegMove;  
             }  
             else if (leftLegAngle < 70)
			 {  
                 leftLegMove = -leftLegMove;  
             }  
             leftLegAngle = (leftLegAngle + leftLegMove) % 360; // Changing angle of left leg  
   
             if (rightLegAngle > 110) 
			 {  
                 rightLegMove = -rightLegMove;  
             }  
             else if (rightLegAngle < 70)
			 {  
                 rightLegMove = -rightLegMove;  
             }  
             rightLegAngle = (rightLegAngle + rightLegMove) % 360; // Changing angle of right leg  
             zMove += 1.5f; // Moving object on the z-axis  
         }  
     glutSwapBuffers();  
}

void keyboard(unsigned char key, int x, int y)
{  
    if (key == 27) // exit when user hits <esc>  
        exit(EXIT_SUCCESS);  
}

void mouse(int button, int state, int x, int y)
{  
     if (GLUT_LEFT_BUTTON == button && state == GLUT_DOWN && mouseLeftState == false)
	 { // If left button is clicked, left state will be true for shaking lower arm  
         mouseLeftState = true;  
     }  
     else if (GLUT_LEFT_BUTTON == button && state == GLUT_DOWN && mouseLeftState == true)
	 { // If left button is clicked again, left state will be false and shaking will stop.  
         mouseLeftState = false;  
     }  
     else if (GLUT_RIGHT_BUTTON == button && state == GLUT_DOWN && mouseRightState == false)
	 { // If right button is clicked again, moving of object and rotation of legs will stop.  
         mouseRightState = true;  
     }  
     else if (GLUT_RIGHT_BUTTON == button && state == GLUT_DOWN && mouseRightState == true)
	 { // If right button is clicked, right state will be true and moving object and rotation of legs will start  
         mouseRightState = false;  
     }  
}

void timer(int notUsed)
{
	glutPostRedisplay();
	glutTimerFunc(100, timer, 0);  
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST); // Hidden surface removal
	glutInitWindowSize(1200, 700);
	glutCreateWindow(argv[0]);
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-750.0, 750.0, -500.0, 500.0, -500.0, 500.0); // Changing the coordinate system.
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	timer(0);
	glutMainLoop();
	return EXIT_SUCCESS;
}