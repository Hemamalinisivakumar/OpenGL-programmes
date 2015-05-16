#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
typedef struct point{ 
	GLubyte red, green, blue; 
}point;



void boundaryfill(float x,float y, point fill, point boundary){
  point c;
  glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &c);
  if ((c.red!=boundary.red)&&(c.blue!=boundary.blue)&&(c.green!=boundary.green)&&(c.green!=fill.green)&&(c.blue!=fill.blue)&&(c.red!=fill.red)&&\
(x<=400)){

      glBegin(GL_POINTS);
      glColor3ub(fill.red,fill.green,fill.blue);
      glVertex2f(x,y);
      glEnd();
      glFlush();
      glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &c);
      printf("\nCOlOR %d %d %d",(int)c.red,(int)c.green,(int)c.blue);
      printf("\nX=%f,Y=%f",x,y);
                                                                                                                                   
      boundaryfill(x+1,y,fill,boundary);
      boundaryfill(x,y+1,fill,boundary);
      boundaryfill(x-1,y,fill,boundary);
      
      boundaryfill(x,y-1,fill,boundary);

    }

}

void mydisplay(){
      glBegin(GL_POLYGON);
	glColor3ub(0,10,10);
	/*glVertex2f(200,50);
	  glVertex2f(200,100);
	  glVertex2f(300,70);
	  glVertex2f(400,100);
	  glVertex2f(400,50);*/
	glVertex2f(300,200);
	glVertex2f(250,100);
	glVertex2f(200,180);
	glVertex2f(150,100);
	glVertex2f(100,200);
      glEnd();
      glFlush();
      
      point fill,boundary;
      
      fill.red=0;      //fill params       
      fill.green=255;
      fill.blue=0;
      
      boundary.red=0;   //boundary params
      boundary.green=255;
      boundary.blue=255;
      
      boundaryfill(200,175,fill,boundary);
      glEnd();
      glFlush();
}

void boundary()
{
    glClearColor(0.0,0.0,0.0,0.0);        
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);  //Red Boundary
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,400.0,0.0,400.0);
    glBegin(GL_POLYGON);
	glColor3ub(10,10,10);
	glVertex2f(100,50);
	  glVertex2f(200,100);
	  glVertex2f(300,70);
	  glVertex2f(400,100);
	  glVertex2f(400,50);
	/*  
	glVertex2f(300,200);
	glVertex2f(250,100);
	glVertex2f(200,180);
	glVertex2f(150,100);
	glVertex2f(100,200);
	*/
      glEnd();
      glFlush();
}

void main(int argc,char **argv){
	  glutInit(&argc,argv);
	  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	  glutInitWindowSize(400,400);
	  glutInitWindowPosition(600,100);
	  glutCreateWindow("Boundary Fill");
	  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	  glClear(GL_COLOR_BUFFER_BIT);
	  glutDisplayFunc(mydisplay);
	  gluOrtho2D(0.0,400.0,0.0,400.0);
	  
	  
	  glutMainLoop();
}
