#include<windows.h>
#include <iostream>
#include <GL/glut.h>
#include<stdio.h>
#include<math.h>
using namespace std;
#define DEG2RAD 3.14159/180.0

int pntX1, pntY1, r,a,b,x[50],y[50],w[50],z[50],n,x1,x2,y2;
GLfloat xx[50],yy[50];
int y11;
float xmin=-50,xmax=+50,ymin=-50,ymax=+50,theta;
void Clipping();

void plot(float x, float y)
{   //glPointSize(1.0);
	glBegin(GL_POINTS);
	glVertex2i(x+pntX1, y+pntY1);
	glEnd();
}

/*void init (void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1000.0, 1000.0, -1000.0, 1000.0);
}*/
void Line()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(0,0,0);
    float dx=x2-x1;
    float dy=y2-y11;
    float ddx=dx;
    float ddy=dy;
    if(dx<0){ddx=-dx;}
    if(dy<0){ddy=-dy;}
    float L;
    if (ddx>ddy)
    {
        L=ddx;
    }
    else
    {
        L=ddy;
    }
    float xinc=dx/L;
    float yinc=dy/L;
    float x=x1;
    float y=y11;
    plot(x,y);
    int i=0;
    while(i<=L)
    {
        x=x+xinc;
        y=y+yinc;
        plot(x,y);
        i=i+1;
    }
    //glFlush();

}
void Thick_Line()

{
    //glClear(GL_COLOR_BUFFER_BIT);
    float dx=x2-x1;
    float dy=y2-y11;
    float ddx=dx;
    float ddy=dy;
    if(dx<0){ddx=-dx;}
    if(dy<0){ddy=-dy;}
    float L;
    if (ddx>ddy)
    {
        L=ddx;
    }
    else
    {
        L=ddy;
    }
    float xinc=dx/L;
    float yinc=dy/L;
    float x=x1;
    float y=y11;
    //glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    int i=0;
    while(i<=L)
    {
        x=x+xinc;
        y=y+yinc;
        glVertex2f(x,y);
        i=i+1;
    }
    glEnd();
    //glFlush();

}

void Dotted_Line()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    float dx=x2-x1;
    float dy=y2-y11;
    float ddx=dx;
    float ddy=dy;
    if(dx<0){ddx=-dx;}
    if(dy<0){ddy=-dy;}
    float L;
    if (ddx>ddy)
    {
        L=ddx;
    }
    else
    {
        L=ddy;
    }
    float xinc=dx/L;
    float yinc=dy/L;
    float x=x1;
    float y=y11;
    plot(x,y);
    int i=0;
    while(i<=L)
    { x=x+xinc;
        y=y+yinc;
        if (i%5==0){
        plot(x,y);}
        i=i+1;
    }
    //glFlush();

}
void Circle(void)
{
	//glClear (GL_COLOR_BUFFER_BIT);
	//glColor3f (0.0, 0.0, 0.0);
	//glPointSize(1.0);
	int x = 0;
	int y = r;
	float decision = 5/4 - r;
	plot(x, y);

	while (y > x)
	{
		if (decision < 0)
		{
			x++;
			decision += 2*x+1;
		}
		else
		{
			y--;
			x++;
			decision += 2*(x-y)+1;
		}
		plot( x,  y);
		plot( x, -y);
		plot(-x,  y);
		plot(-x, -y);
		plot( y,  x);
		plot(-y,  x);
		plot( y, -x);
		plot(-y, -x);
	}


	//glFlush ();
}

void polygon()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++)
    {
        glVertex2f(x[i],y[i]);
    }
    glEnd();
    //glFlush();
}

void polygon2()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<n;i++)
    {
        glVertex2f(x[i],y[i]);
    }
    glEnd();
    //glFlush();

}

int code(int x,int y)
{
    int c=0;
    if (y>ymax){c=8;}
    if (y<ymin){c=4;}
    if (x>xmax){c=c|2;}
    if (x<xmin){c=c|1;}
    return c;
}

void cohen_line(int x1,int y1,int x2,int y2,int i)
{
    int c1=code(x1,y1);
    int c2=code(x2,y2);
    float m = (y2-y1)/(x2-x1);
    while((c1|c2)>0)
    {
        if((c1 & c2) >0){
            exit(0);
        }
        int c=c1;
        float xi=x1;
        float yi=y1;
        if(c1==0)
        {
            c=c2;
            xi=x2;
            yi=y2;
        }
        float ii,jj;
        if ((c & 8)>0)
        {
            jj=ymax;
            ii=xi+(1.0/m)*(ymax-yi);
        }
        else if((c & 4)>0)
        {
            jj=ymin;
            ii=xi+(1.0/m)*(ymin-yi);

        }
        else if((c & 2) >0)
        {
            ii=xmax;
            jj=yi+m*(xmax-xi);
        }
        else if ((c & 1)>0)
        {
            ii=xmin;
            jj=yi+m*(xmin-xi);
        }
        if (c==c1){
            x[i]=ii;
            y[i]=jj;
            c1=code(x[i],y[i]);
        }
        if(c==c2){
            w[i]=ii;
            z[i]=jj;
            c2=code(w[i],z[i]);
        }
    }
    Clipping();

}
void keyfunc(unsigned char key,int xw,int yz)
{

    if (key=='c')
    {
        for(int i=0;i<n;i++)
        {
            cohen_line(x[i],y[i],w[i],z[i],i);
        }
        glFlush();
    }
}
void Clipping()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmin,ymax);
    glVertex2f(xmax,ymax);
    glVertex2d(xmax,ymin);
    glEnd();
    glColor3f(0,0,1);
    glBegin(GL_LINES);
    for(int i=0;i<n;i++)
    {
        glVertex2f(x[i],y[i]);
        glVertex2f(w[i],z[i]);
    }
    glEnd();
    glFlush();
}


void hyperbola()
{
//glClear(GL_COLOR_BUFFER_BIT);
//glColor3f(0.0,0.0,0.0);
for(int i=0;i<360;i++)
{
float rad = i*DEG2RAD;
plot((1/cos(rad))*a,(sin(rad)/cos(rad))*b);
}

//glFlush();
}

void Ellipse()
{
//glClear(GL_COLOR_BUFFER_BIT);
//glColor3f(0.0,0.0,0.0);
int i;
for(i=0;i<360;i++)
{
float rad = i*DEG2RAD;
plot(sin(rad)*a,-cos(rad)*b);
}

glFlush();
}
void translate()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(1,0,0);
    /*glBegin(GL_POLYGON);
    for(int i=0;i<n;i++)
    {
        glVertex2f(x[i],y[i]);
    }
    glEnd();
    */
    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++)
    {
        glVertex2f(x[i]+pntX1,y[i]+pntY1);
    }
    glEnd();
    //glFlush();

}
void  Rotate()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++)
    {
        glVertex2f(x[i],y[i]);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++)
    {
        glVertex2f((x[i]*cos(theta)-y[i]*sin(theta))+pntX1,(x[i]*sin(theta)+y[i]*cos(theta))+pntY1);
    }
    glEnd();
    //glFlush();

}
void Scale()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++)
    {
        glVertex2f(x[i],y[i]);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++)
    {
        glVertex2f((x[i]*theta)+pntX1,(y[i]*theta)+pntY1);
    }
    glEnd();
    //glFlush();

}

void drawpixel(int x,int y)
{
    //glColor3f(0.0,1.0,1.0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
void edgedetect(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,int *le,int *re)
{
    float mx,x,temp;
    int i,k;

    if((y2-y1)<0)
    {
        temp=x1;
        x1=x2;
        x2=temp;
        temp=y1;
        y1=y2;
        y2=temp;
    }
    if((y2-y1)!=0)
        mx=(x2-x1)/(y2-y1);
    else
        mx=x2-x1;
    x=x1;
    for(i=(int)y1;i<(int)y2;i++)
    {
        int t=0;                //flag
        if(x<(float)le[i])
        {
            if((float)le[i]!=500)
            {
                le[i]=(int)x;
                for(k=re[i]-1;k>le[i];k--)
                    drawpixel(k, i);
                le[i]=500;
                re[i]=0;
                t=1;
            }
            else
                le[i]=(int)x;
        }
        if(t==0)
        if(x>(float)re[i])
        {
            if((float)re[i]!=0)
            {
                re[i]=(int)x;
                for(k=le[i]+1;k<re[i]-1;k++)
                    drawpixel(k,i);
                le[i]=500;
                re[i]=0;
            }
            else
                re[i]=(int)x;
        }
        x+=mx;
    }
}


void scanfill(GLfloat *x,GLfloat *y)
{
    int le[500],re[500];
    int i;
    for(i=0;i<500;i++)
    {
        le[i]=500;
        re[i]=0;
    }

    for(int k=0;k<n-1;k++)
    {
        edgedetect(x[k],y[k],x[k+1],y[k+1],le,re);

    }
    edgedetect(x[n-1],y[n-1],x[0],y[0],le,re);
}

void display_scanfill()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    for(int k=0;k<n;k++)
    {
        glVertex2f(xx[k],yy[k]);
    }
    glEnd();

    scanfill(xx,yy);

    //glFlush();

}

