#include <stdio.h>
#include <stdlib.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <math.h>
#include<ctype.h>

float tx,ty,sx,sy,theta=50;
int choice,n,vertex,shx,shy;
float xd[10],yd[10],X1[10],Y1[10];
float WlengthX, WlengthY;
float VlengthX, VlengthY;
float WXMax=600, WXMin=100, WYMax=600, WYMin=100;
float VXMax=800, VXMin=600, VYMax=800, VYMin=200,VX[10], VY[10],VX1[10], VY1[10];

float SX, SY, TX, TY;


void initt()  
{
	glClearColor(0,0,0,0.0);  
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D(-1000,1000,-1000,1000);
}

void translation(){                            
	 int i;
	for(i=1;i<=vertex;i++){
		X1[i]=xd[i]+tx;
		Y1[i]=yd[i]+ty;
	}
}

void scaling(){                                 
	float xh[10],yh[10]; int i=1;
	
    for(i=1;i<=vertex;i++){            
    	xh[i]=xd[i]-xd[1];
    	yh[i]=yd[i]-yd[1];
    }
    	
	for(i=1;i<=vertex;i++){
		xh[i]=xh[i]*sx;       
		yh[i]=yh[i]*sy;
	}
 	for(i=1;i<=vertex;i++){               
   		X1[i]=xh[i]+2*xd[1];
   		Y1[i]=yh[i]+yd[1];
	}
}

void rotation(){                                   
	float t,xh[10],yh[10]; 
	int i;	
	t= -1*(theta * 3.14/180);
	double coss = cos(t);
	double sinn = sin(t);
	
	for(i=1;i<=vertex;i++){
    			xh[i]=xd[i]-xd[1];
    			yh[i]=yd[i]-yd[1];
    			
    			xh[i]= (xh[i]*coss) - (yh[i]*sinn);
			yh[i]= (xh[i]*sinn) + (yh[i]*coss);
			
			X1[i]=xh[i]+xd[1];
    			Y1[i]=yh[i]+yd[1];
    	}
}
void shearX(){
	int i;
	for(i=0;i<vertex;i++){
		X1[i]=xd[i]+shx*yd[i];
		Y1[i]=yd[i];
	}
}
void shearY(){
	int i;
	for(i=0;i<vertex;i++){
		Y1[i]=yd[i]+shy*xd[i];
		X1[i]=xd[i];
	}
}


void reflectionX(){
	int i;
	for(i=0;i<vertex;i++){
		Y1[i]=-yd[i];
		X1[i]=xd[i];
	}
}
void reflectionY(){
	int i;
	for(i=0;i<vertex;i++){
		X1[i]=-xd[i];
		yd[i]=xd[i];
	}
	
}

void worldWindow(){	
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    if(vertex==2){
		glBegin(GL_LINES);
		for(i=1;i<=vertex;i++){
        	glVertex2f(xd[i], yd[i]);
		}
   }
    else{
	glBegin(GL_POLYGON);
		for(i=1;i<=vertex;i++){
	    	glVertex2f(xd[i], yd[i]);
		}
    } 
    glEnd();
    glColor3f(1.0, 0.0, 1.0);

    if(vertex==2){
	glBegin(GL_LINES);
	for(i=1;i<=vertex;i++){
        	glVertex2f(X1[i], Y1[i]);
	}
   }
    else{
	glBegin(GL_POLYGON);
	for(i=1;i<=vertex;i++){
        	glVertex2f(X1[i], Y1[i]);
	}
    }
           
    glEnd();
    glutSwapBuffers();
    glFlush();
}

							
void viewPort(){	
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    if(vertex==2){
		glBegin(GL_LINES);
		for(i=1;i<=vertex;i++){
		    	glVertex2f(VX[i], VY[i]);
			}
	}
    else{
		glBegin(GL_POLYGON);
		for(i=1;i<=vertex;i++){
		    	glVertex2f(VX[i], VY[i]);
		}
	}
    glEnd();
    glColor3f(1.0, 0.0, 1.0);
 
    if(vertex==2){
		glBegin(GL_LINES);
		for(i=1;i<=vertex;i++){
        	glVertex2f(VX1[i], VY1[i]);
		}
	}
    else{
		glBegin(GL_POLYGON);
		for(i=1;i<=vertex;i++){
        	glVertex2f(VX1[i], VY1[i]);
		}
	}
    glEnd();
    glutSwapBuffers();
    glFlush();
}

float scalingX(float WXMax, float WXMin, float VXMax, float VXMin){
	float sx = (VXMax - VXMin)/(WXMax - WXMin);
	return sx;
}

float scalingY(float WYMax, float WYMin, float VYMax, float VYMin){
	float sy = (VYMax - VYMin)/(WYMax - WYMin);
	return sy;
}


float transX(float WXMax, float WXMin, float VXMax, float VXMin){
	float tx = ((WXMax * VXMin) - (WXMin * VXMax))/(WXMax - WXMin);
	return tx;
}


float transY(float WYMax, float WYMin, float VYMax, float VYMin){
	float ty = ((WYMax * VYMin) - (WYMin * VYMax))/(WYMax - WYMin);
	return ty;
}

void operation(GLubyte key, GLint x, GLint y)
{
	float currentX,currentY;
	switch(key)
	{
		case 97://a
				translation();
				glutPostRedisplay();
				break;
		case 98://b 
				scaling();
	            		glutPostRedisplay();
				break;
		case 99://c
				rotation();
				glutPostRedisplay();
				break;
		case 100://d
				reflectionX();
				glutPostRedisplay();
				break;
		case 101://e
				reflectionY();
				glutPostRedisplay();
				break;
		case 102://f 
				shearX();
				glutPostRedisplay();
				break;
		case 103://g
				shearY();
				glutPostRedisplay();
				break;
	}
}

int main(int argc, char **argv){
	int i;
	
//	printf("dee1\n");
	printf("ENTER NO. OF VERTICES(max=10):-\n");
	scanf("%d",&vertex);	
	if(vertex<2 || vertex>10){
		printf("Invalid Input......Exiting......\n");
		exit(0);
	}
//	printf("dee3\n");
	for(i=1;i<=vertex;i++){
		printf("Enter coordinates(x,y):-\n");
		scanf("%f %f", &xd[i], &yd[i]);
	}
//	printf("dee4\n");
	WlengthX = WXMax - WXMin;
	WlengthY = WYMax - WYMin;
	VlengthX = VXMax - VXMin;
	VlengthY = VYMax - VYMin;
	printf("Translation Factors:- ");
	scanf("%f %f",&tx,&ty);
	
	printf("Scaling Factors:- ");
	scanf("%f %f",&sx,&sy);
	
	printf("Angle of Rotation:-\n");
	scanf("%f",&theta);
	
	printf("Shearing Factors:-");
	scanf("%d %d",&shx,&shy);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WlengthX, WlengthY);
	glutInitWindowPosition(WXMin, WYMin);
	glutCreateWindow("2D TRANSFORMATION ");
	initt();
	glutDisplayFunc(worldWindow);
	glutKeyboardFunc(operation);

	SX = scalingX(WXMax, WXMin, VXMax, VXMin);
	SY = scalingY(WYMax, WYMin, VYMax, VYMin);
	TX = transX(WXMax, WXMin, VXMax, VXMin);
	TY = transY(WYMax, WYMin, VYMax, VYMin);
	for(i=1;i<=vertex;i++){	
		VX[i] = SX * xd[i] + TX;
		VY[i] = SY * yd[i] + TY;
		VX1[i] = SX * X1[i] + TX;
		VY1[i] = SY * Y1[i] + TY;
	}
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(VlengthX, VlengthY);
	glutInitWindowPosition(VXMin, VYMin);
	glutCreateWindow("OpenGL - View Port Transformation");
	initt();
	glutDisplayFunc(viewPort);	
	glutMainLoop(); 
	return 0;
}





