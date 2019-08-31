#include<windows.h>
#include <iostream>
#include <GL/glut.h>
#include<stdio.h>
#include<math.h>
#include "library.cpp"
//#include "curve.cpp"

using namespace std;
int f=0;
void animation();
void Timer(int);

void init (void)
{
	glClearColor(.0, .0, 0.9, 0);
}
void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500,500,-500,500);
    glMatrixMode(GL_MODELVIEW);
}


void animation()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2);
	glColor3f(1,1,0);
	n=4;
	//Base Polygon
	x[0]=-500;y[0]=-200;x[1]=500;y[1]=200;x[2]=500;y[2]=-500;x[3]=-500;y[3]=-500;
	polygon();



	//cloud
	r=50;
	glPointSize(5);
	pntX1=10;pntY1=300;
	while(r!=0){
            r=r-5;
	glColor3f(1,1,1);
	Circle();}

    r=50;
	pntX1=75;pntY1=320;
	while(r!=0){
            r=r-5;
	glColor3f(1,1,1);
	Circle();}

    r=50;
	pntX1=140;pntY1=300;
	while(r!=0){
            r=r-5;
	glColor3f(1,1,1);
	Circle();}

		r=50;
	pntX1=90;pntY1=270;
	while(r!=0){
            r=r-5;
	glColor3f(1,1,1);
	Circle();}
// cloud hyperbola
int i=0;
glPointSize(2);
pntX1=20;pntY1=290;
while(i<8){
    pntX1=pntX1+4*i;
    a=5;b=4;
    glColor3f(1,1,1);
    hyperbola();
    i=i+1;


	//sun
	r=50;
	glColor3f(1,0,0);
	pntX1=f-350;pntY1=350;

	while(r!=0){
            glPointSize(5);
            r=r-5;
	glColor3f(1,1,0);
	Circle();}

	glPointSize(2);
	glColor3f(1,1,0);
    //Sunlines
	pntX1=pntX1+350-f;pntY1=pntY1-350;
	x1=-300+f;y11=350;x2=-240+f;y2=350;
	Line();
	x1=-400+f;y11=350;x2=-460+f;y2=350;
	Line();
	x1=-350+f;y11=400;y2=470;x2=f-350;
	Line();
	x1=f-350;y11=300;y2=240;x2=f-350;
	Line();
	x1=0;x2=0;y11=0;y2=0;


	//sand
	x1=-500;y11=-200;
	y2=200;  x2=500;
	glColor3f(1,0,0);
	while(y2>-500){
            y11=y11-5;
            y2=y2-5;
            Dotted_Line();

	}
	//lighthouse
	x[0]=330;y[0]=-400;x[1]=330;y[1]=-300;x[2]=450;y[2]=-300;x[3]=450;y[3]=-400;
	n=4;
	glColor3f(0,0,0);
	polygon();
	n=5;
	x[0]=300;y[0]=-400;x[1]=300;y[1]=0;x[2]=390;y[2]=400;x[3]=480;y[3]=0;x[4]=480;y[4]=-400;
	glColor3f(1,0,0);
	polygon();
	x[4]=NULL;y[4]=NULL;

	int i=0;
	y11=0;y2=0;
	//Lighthouse line
	while(i<20){
	x1=300;y11=-i*50;x2=480;y2=-i*50;;
	glPointSize(5);
	glColor3f(1,1,1);
	Thick_Line();i=i+1;}

	x[0]=350;y[0]=-400;x[1]=430;y[1]=-400;x[2]=430;y[2]=-275;x[3]=350;y[3]=-275;
	n=4;
	glColor3f(0,0,0);
	polygon();
	pntX1=390;pntY1=150;
	r=35;
	//light house circle
	while(r!=0){
            r=r-5;
	glColor3f(0,1,0);
	Circle();}


	//Net
	glColor3f(0,0,0);
	x1=-300-100;y11=-400;x2=-300-100;y2=-600;
	Line();

	glColor3f(0,0,0);
	x1=-100-100;y11=-340;x2=-100-100;y2=-540;
	Line();
	i=-20;int j=0;
	x1=-300-100;y11=-400;x2=-100-100;y2=-340;
	while(j<5)
    {
    glColor3f(0,0,0);
    glPointSize(3);
	y11=y11+i;y2=y2+i;
	Line();
	j=j+1;
    }

}


	glutSwapBuffers();

}


int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_DOUBLE);
glutInitWindowSize (1000,1000);
glutInitWindowPosition (0,0);
x1=0;x2=700;y11=90;y2=890;
glutCreateWindow("Animation");
glutDisplayFunc(animation);
glutReshapeFunc(reshape);
glutTimerFunc(2000,Timer,0);
init();
glutMainLoop();
}

void Timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60,Timer,0);
    f=(f+5)%600;

}
