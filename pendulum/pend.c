#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
typedef float Matrix3x3 [3][3];
float ref[2];
float theta;
float fin[3];
int k,inc;
float Centre[120][3];
void matrixSetIdentity(Matrix3x3 m){
   int i, j;
   for (i=0; i<3; i++)
   for (j=0; j<3; j++)
   m[i][j] = (i == j);
}
void matrixSetIdentity(Matrix3x3 m);
void Rotate(float a,float b[3]);

void redisp();

void setPixel(float x,float y){
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}

void Circle(float ax,float ay,float ar,int k){
	
  float xCenter=ax,yCenter=ay,r=ar;
  float x=0,y=r;
  float p = 3/2 - r;	
  	
  	const PI = 3.141592;
    const float X = ax;
    const float Y = ay;
    const float Radius = ar;
    int col;
    if(k==0)	k=1;
	if(k<60)
			col = (60-k)%60;
/*	else if(k==60) {*/
/*		*/
/*	}*/
	else
			col = k%60;
			
    glColor3f (col*0.02,0, 0); 
/*    glColor3f (1,0, 0);  */

    glBegin (GL_POLYGON);
    float angle;
    for(angle=0;angle<=PI*2;angle+=0.01) //  Circumference of circle = 2PI * r
        glVertex2f (X + sin(angle) * Radius, Y + cos(angle) * Radius);
    
    glEnd ();	

/*  glClear(GL_COLOR_BUFFER_BIT);*/
  
/*  glColor3f( 0 ,0, 1);  */
/*  while(x<=y){*/
/*    glVertex2f(xCenter+x,yCenter+y);*/
/*    glVertex2f(xCenter+y,yCenter+x);		*/
/*    glVertex2f(xCenter-x,yCenter+y);*/
/*    glVertex2f(xCenter+y,yCenter-x);*/
/*    glVertex2f(xCenter-x,yCenter-y);*/
/*    glVertex2f(xCenter-y,yCenter-x);*/
/*    glVertex2f(xCenter+x,yCenter-y);*/
/*    glVertex2f(xCenter-y,yCenter+x);*/

/*    if (p<0)*/
/* 	p += (2*x)+3;*/
/*    else {*/
/*	p += (2*(x-y))+5;*/
/*	y -= 1;*/
/*    }*/
/*    x++;*/
/*  }*/
/*  glEnd ();*/
}

void display1(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
		int col;
/*		if(k<60)*/
/*			col = (60-k)%60;*/
/*		else*/
/*			col = k%60;*/
/*/*		if(k<=10)	col=10;*/
		glColor3f(0,1,0);
		glVertex2f(ref[0],ref[1]);
		glVertex2f(Centre[k][0],Centre[k][1]);
	glEnd();
	Circle(Centre[k][0],Centre[k][1],30,k);
	k+=inc;
	if(k>119){
		k=117;
		inc=-1;
	
	}
	else if(k<0){
		k=1;
		inc=1;
	}

	glutSwapBuffers();
	redisp();
}
void calPts(){
	int i;
	for(i=61;i<=119;i++){
		Rotate(theta,Centre[i-1]);
		Centre[i][0]=fin[0];Centre[i][1]=fin[1];Centre[i][2]=1;
	}
	theta=-theta;
	for(i=59;i>=0;i--){
		Rotate(theta,Centre[i+1]);
		Centre[i][0]=fin[0];Centre[i][1]=fin[1];Centre[i][2]=1;
	}
  glutDisplayFunc(display1);
  glutMainLoop();
}
int main(int argc ,char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("My Pendulum");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	ref[0]=250;
	ref[1]=400;
	theta=1;
	k=60;
	inc=1;
	
	Centre[60][0]=250;
	Centre[60][1]=200;
	Centre[60][2]=1;
	calPts();

}

void matrixPreMultiply(Matrix3x3 a , float b[3]){
// Multiplies matrix a times b, putting result in b

   int i,j;
   float tmp[3];
   for (i = 0; i < 3; i++)
     for (j = 0; j < 3; j++)
       tmp[i] = a[i][0]*b[0] + a[i][1]*b[1] + a[i][2]*b[2];
   
   for (i = 0; i < 3; i++)
   	 fin[i] = tmp[i];
}
void Rotate(float a,float b[3]){
   Matrix3x3 m;
   matrixSetIdentity(m);
   a = a*22/1260;
   m[0][0] = cos(a);
   m[0][1] = -sin(a) ;
   m[0][2] = ref[0]*(1 - cos(a)) + ref[1]*sin(a);
   m[1][0] = sin(a);
   m[1][1] = cos(a);
   m[1][2] = ref[1]*(1 - cos(a)) - ref[0]*sin(a);
   matrixPreMultiply(m , b);
}
void redisp(){
	//sleep(1);
	usleep(2*10000);
	glutPostRedisplay();

}

