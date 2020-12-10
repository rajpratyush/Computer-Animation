#include <iostream>
#include <GL/glut.h>
#include "DrawPanel.cpp"
#include <cmath>
using namespace std;
class Color{
public :
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    Color(){}
    Color(float r, float g, float b){
        tranform(r,g,b);
    }
    void tranform(float r, float g, float b){
        red = float(r/255.0000);
        green = float(g/255.0000);
        blue = float(b/255.0000);
    } 
    void setColor(float r, float g, float b){
         tranform(r,g,b);
    }
};

void drawCircle(double xCor, double yCor, double radius){
    
    glBegin(GL_POLYGON);
    for(int i =0; i <= 300; i++){
        double angle = 2 * 3.14 * i / 300;
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        glVertex2d(x +xCor,y+yCor);
    }
    glEnd();
}

Color c;
DrawPanel panel;
int seconds = 0;
int minutes = 0;
int hours = 0;

void drawClock(){
    glLoadIdentity();
    drawCircle(0,0,.3);
    int second = seconds%60 * 6;
    int minute =( minutes % 60) *6;
    int hour = (hours %12 )*6;
    hour+= (minutes/12) * 6;
    
    
    cout <<second <<"::" <<minute <<"::"<< hour<<endl;
    Color clock;
    clock.setColor(0,0,0);
    glColor3f(clock.red, clock.green,clock.blue);
    
    glRotatef(-hour+90, 0.0,0.0,1.0);
    panel.drawRect(0,0,.25, .01,9);
    glRotatef(hour-90, 0.0,0.0,1.0);
    
    glRotatef(-minute+90, 0.0,0.0, 1.0);
    panel.drawRect(0,0,.4, .01,9);
    glRotatef(-minute-90, 0.0,0.0, 1.0);
    
    glRotatef(-second+90, 0.0,0.0, 1.0);
    panel.drawRect(0,0,.4, .01,9);
    glRotatef(-second-90, 0.0,0.0, 1.0);
    
    drawCircle(0,0,.05);
    
    glEnd();
}

void drawBob(){
    drawCircle(.01, .5, .083);
}

void drawPendulum(double angle)
{
    glLoadIdentity();
    
    glRotatef(angle-90, 0.0,0.0,1.0);
    panel.drawRect(0,0, .5,.02,-90);
    
    glRotatef(-90, 0.0,0.0,1.0);
    drawBob();
    glRotatef(90, 0.0,0.0,1.0);
    
    glRotatef(-angle+90, 0.0,0.0,1.0);
    glEnd();
}

double angle =-60;
bool direction = true;
double angularAcc = 0, angularVec = 0, timeShift = 0.1;
double lengthPendulum = 50;

int clockSpeed;
void call_back_display(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    c.setColor(120,255,255);
    glColor3f(c.red, c.green,c.blue);
    
    angularAcc = -9.81 / lengthPendulum * sin(angle/180 * 3.1415);  
    angularVec = angularVec + angularAcc*timeShift;
    angle+= angularVec*timeShift;
    drawPendulum(angle);
    drawClock();
    
    if(angle <= -120) {angle = -120;}
    else if(angle >= 60) angle = 60;
    clockSpeed++;
    if(clockSpeed%60 == 0)
        seconds ++;
    minutes = seconds/60;
    hours = minutes/60;
    glEnd();
    glutSwapBuffers();
}


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    panel.setCallBack(call_back_display);
    panel.display();
    glutMainLoop();
    return 0;
}
