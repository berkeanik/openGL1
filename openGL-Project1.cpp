/**********************
  Berke Anık
  22203540
  Section 1


  Additional Functions:
  Left mouse to close panes
  Space to stop animation

  
***********************/
#include <GL\glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600
#define TIMER_PERIOD  100 // Period for the timer.
#define TIMER_ON         1 // 0:Disable timer, 1:Enable timer

bool animationPaused = false; // control animation
int carPositionX = -350; //position of the car
bool leftPaneOpen = true; // left pane
bool rightPaneOpen = true; // right pane


void circle(float x, float y, float radius) {
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= 360; ++i) {
		glVertex2f(x + radius * cos(i * 3.1415926 / 180.0),
			y + radius * sin(i * 3.1415926 / 180.0));
	}
	glEnd();
}

void drawCar(float x, float y) {
	// Car Body
	glColor3f(0.8f, 0.2f, 0.2f); // Red 
	glBegin(GL_POLYGON);
	glVertex2f(x, y);        
	glVertex2f(x + 150, y);   
	glVertex2f(x + 150, y + 50); 
	glVertex2f(x + 120, y + 80); 
	glVertex2f(x + 30, y + 80);  
	glVertex2f(x, y + 50);     
	glEnd();

	// Wheels
	glColor3f(0.2f, 0.2f, 0.2f); 
	circle(x + 30, y - 10, 15); 
	circle(x + 120, y - 10, 15); 

	// Headlight
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow 
	circle(x + 140, y + 22, 5); 


	// mirror
	glColor3f(0.6f, 0.8f, 1.0f); // light blue
	glBegin(GL_QUADS);
	glVertex2f(x + 100, y + 40);
	glVertex2f(x + 145, y + 40);
	glVertex2f(x + 100, y + 75);
	glVertex2f(x + 100, y + 40);
	glEnd();


	// Roof 
	glColor3f(0.4f, 0.4f, 0.4f); // Dark gray 
	glBegin(GL_QUADS);
	glVertex2f(x + 40, y + 80);
	glVertex2f(x + 110, y + 80);
	glVertex2f(x + 100, y + 90);
	glVertex2f(x + 50, y + 90);
	glEnd();

	// Silencer
	glColor3f(0.5f, 0.5f, 0.5f); // Gray 
	glBegin(GL_QUADS);
	glVertex2f(x + 15, y + 10); 
	glVertex2f(x - 17, y + 10);
	glVertex2f(x - 17, y + 20);
	glVertex2f(x + 15, y + 20);
	glEnd();

	//door
	glColor3f(0.0f, 0.0f, 0.0f); // Gray 
	glBegin(GL_QUADS);
	glVertex2f(x + 45, y + 5);
	glVertex2f(x + 85, y + 5);
	glVertex2f(x + 85, y + 60);
	glVertex2f(x + 45, y + 60);
	glEnd();

	//door handle
	glColor3f(1.0f, 1.0f, 1.0f); // white
	circle(x + 75, y + 25, 2);

}


void drawWall() {


	// wall
	glColor3f(0.0f, 0.7f, 1.0f); // blue
	glBegin(GL_POLYGON);
	glVertex2f(-300, -300);
	glVertex2f(-300, 300);
	glVertex2f(300, 300);
	glVertex2f(300, -300);
	glEnd();

}

void drawText(float x, float y, const char* text) {
	glRasterPos2f(x, y);
	int len = strlen(text);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
}


void drawClouds() {
	glColor3f(1.0f, 1.0f, 1.0f); // White 
	circle(-150, 200, 20); 
	circle(-120, 220, 20);
	circle(-90, 200, 20);
	circle(-130, 180, 20);
	circle(-100, 180, 20);
	circle(-120, 200, 20);

	circle(150, 250, 20); 
	circle(180, 270, 20);
	circle(210, 250, 20);
	circle(170, 230, 20);
	circle(200, 230, 20);
	circle(180, 250, 20);
}



void wall() {



	glColor3f(1.0f, 0.5f, 0.0f);
	glRectf(-300, 250, 300, 300);

	glColor3f(1.0f, 0.5f, 0.0f);
	glRectf(-300, -300, 300, -250);

	glColor3f(1.0f, 0.5f, 0.0f);
	glRectf(-300, -250, -250, 250);

	glColor3f(1.0f, 0.5f, 0.0f);
	glRectf(250, -250, 300, 250);

	for (int i = 0; i <= WINDOW_WIDTH; i += 15) 
		if (i >= 550 || i<=50) {
			glColor3f(0, 0, 0.5);
			glLineWidth(3);
			glBegin(GL_LINES);
			glVertex2f(-300, 300-i);
			glVertex2f(300, 300-i);
			glEnd();
		}
	for (int i = 50; i <= 550; i += 15) 
		{
			glColor3f(0, 0, 0.5);
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2f(-300, 300 - i);
		glVertex2f(-250, 300 - i);
		glEnd();
		glLineWidth(3);
		glColor3f(0, 0, 0.5);
		glBegin(GL_LINES);
		glVertex2f(300, 300 - i);
		glVertex2f(250, 300 - i);
		glEnd();
	}

	
	glColor3f(0, 0, 0);
	glLineWidth(20);
	glBegin(GL_LINE_STRIP);
	glVertex2f(250, 250);
	glVertex2f(-250, 250);
	glVertex2f(-250, -250);
	glVertex2f(250, -250);
	glVertex2f(250, 250);
	glEnd();
	
	glColor3f(0.5f, 0.5f, 0.5f);
	glRectf(-50, -290, 65, -260);
	
	}
	



void display() {

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);


	//wall
	drawWall();

	//clouds
	drawClouds();

	//road
	glColor3f(0.5f, 0.5f, 0.5f); // Gray 
	glBegin(GL_POLYGON);
	glVertex2f(-300, -150);
	glVertex2f(-300, -300);
	glVertex2f(300, -300);
	glVertex2f(300, -150);
	glEnd();

	//road stripes
	glColor3f(1.0f, 1.0f, 1.0f); // White 
	glLineWidth(5.0);
	glBegin(GL_LINES);
	for (int i = -250; i <= 250; i += 50) {
		glVertex2f(i, -225);
		glVertex2f(i + 30, -225);
	}
	glEnd();



	//car
	drawCar(carPositionX, -150);




	// left pane
	if (leftPaneOpen == false) {

		glColor3f(0.0f, 0.0f, 0.0f); // black 
		glBegin(GL_POLYGON);
		glVertex2f(-300, -300);
		glVertex2f(-300, 300);
		glVertex2f(0, 300);
		glVertex2f(0, -300);
		glEnd();
	}

	// right pane
	if (rightPaneOpen == false) {
		glColor3f(0.0f, 0.0f, 0.0f); // black 
		glBegin(GL_POLYGON);
		glVertex2f(300, -300);
		glVertex2f(300, 300);
		glVertex2f(0, 300);
		glVertex2f(0, -300);
		glEnd();
	}
	// lines
	glColor3ub(0, 0, 0); // black 
	glBegin(GL_LINES);

	
	glVertex2f(0, -400);
	glVertex2f(0, 400);
	glEnd();

	wall();

	//name 
	glColor3f(1.0f, 1.0f, 1.0f); // White 
	drawText(-48, -280, "BERKE ANIK");


	glutSwapBuffers();
}

void onTimer(int value) {
	if (!animationPaused) {
		carPositionX += 15; // Move the car
		if (carPositionX > 300) // reset car pos
			carPositionX = -400;
	}
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	glutPostRedisplay();
}


void onMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (x < WINDOW_WIDTH / 2)
			leftPaneOpen = !leftPaneOpen;
		else
			rightPaneOpen = !rightPaneOpen;
		glutPostRedisplay();
	}
}


void onKeyDown(unsigned char key, int x, int y) {
	if (key == 27) // ESC key
		exit(0);
	else if (key == ' ') // Spacebar = pause and resume 
		animationPaused = !animationPaused;
}


void onResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("BERKE ANIK");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);
	glutKeyboardFunc(onKeyDown);
	glutTimerFunc(0, onTimer, 0);
	glutMouseFunc(onMouseClick);

	glutMainLoop();

	return 0;
}