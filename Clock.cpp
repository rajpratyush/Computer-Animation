#include <GL/glut.h>
#include <math.h>

struct Point {
	GLint x;
	GLint y;
};

Point C = {500, 00};
GLint radius = 150;

Point V ={500,150};

double bAngle = 1.01;
double bAngle_inc= 0.05;
GLint bRadius = 500;

GLint hRadius = 120;
GLint mRadius = 130;
GLint sRadius = 140;

double hAngle = 0;
double mAngle = 0;
double sAngle = 0;


void draw_circle(Point pC, GLfloat radius) {
	GLfloat step = 1/radius;
	GLfloat x, y;

	for(GLfloat theta = 0; theta <= 360; theta += step) {
		x = pC.x + (radius * cos(theta));
		y = pC.y + (radius * sin(theta));
		glVertex2i(x, y);
	}
}

void draw_line(Point p1, Point p2) {
	GLfloat dx = p2.x - p1.x;
	GLfloat dy = p2.y - p1.y;

	GLfloat x1 = p1.x;
	GLfloat y1 = p1.y;

	GLfloat step = 0;

	if(abs(dx) > abs(dy)) {
		step = abs(dx);
	} else {
		step = abs(dy);
	}

	GLfloat xInc = dx/step;
	GLfloat yInc = dy/step;

	for(float i = 1; i <= step; i++) {
		glVertex2i(x1, y1);
		x1 += xInc;
		y1 += yInc;
	}
}

void construct() {
	glClearColor(1.0, 1.0, 1.0, 0.0);		// background colour
	glColor3f(0.0f, 0.0f, 0.0f);			//pixel color
	glPointSize(1.0f);				//pixel size
	gluOrtho2D(0.0f, 1000.0f, 800.0f, -200.0f);		//Orthographic Projection (left clipping plane,right clipping plane, bottom clipping plane, topclipping plane)
}

void display(void) {
	Point pHour, pMinute, pSecond, bob;

	pHour.y = C.y + (hRadius * sin(hAngle));
	pHour.x = C.x + (hRadius * cos(hAngle));

	pMinute.y = C.y + (mRadius * sin(mAngle));
	pMinute.x = C.x + (mRadius * cos(mAngle));

	pSecond.y = C.y + (sRadius * sin(sAngle));
	pSecond.x = C.x + (sRadius * cos(sAngle));
	
	bob.y = (C.y) + (bRadius * sin(bAngle));
	bob.x = (C.x) + (bRadius * cos(bAngle));
 
	
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	
	glColor3f(1.0, 0.0, 0.0);
	draw_circle(C, radius);
	
	glColor3f(1.0, 0.0, 0.0);
	draw_line(C, pHour);

	glColor3f(0.0, 1.0, 1.0);
	draw_line(C, pMinute);

	glColor3f(0.0, 0.0, 1.0);
	draw_line(C, pSecond);
	
	glColor3f(0.0,0.0,0.0);
	draw_line(V, bob);
	
	glColor3f(1.0,0.0,0.0);
	for(GLint temp=radius/3; temp>0; temp=temp-1){
		draw_circle(bob, temp);
	}
	
		
	glEnd();
	glFlush();

	sAngle += 0.01;
	mAngle += 0.001;
	hAngle += 0.0001;
	if(bAngle>2){
		bAngle = 2;
		bAngle_inc =-bAngle_inc;
	}if(bAngle<1){
		bAngle = 1;
		bAngle_inc=-bAngle_inc;
	}
	bAngle += bAngle_inc;
}

void Timer(int value) {
	glutTimerFunc(33, Timer, 0);
	glutPostRedisplay();
}



int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Clock");
	glutDisplayFunc(display);
	construct();
	Timer(0);
	glutMainLoop();

	return 0;
}

