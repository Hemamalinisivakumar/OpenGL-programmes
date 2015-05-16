#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>

typedef float Matrix3x3 [3][3];
Matrix3x3 theMatrix;
float ptsIni[20][2];
float ptsFin[20][2];
float fin[3];
float refpt[2];
float RotAngle;
float TransDistX,TransDistY;
float ScaleX,ScaleY;
int choice,choiceRef,choiceShear;
float slope,yIntercept;
float shearValue;
float X1,Y1,X2,Y2;
float bx1,by1,bx2,by2;
int flg=0;
float btx,bty;
void matrixSetIdentity(Matrix3x3 m)
// Initialises the matrix as Unit Matrix
{
   int i, j;
   for (i=0; i<3; i++)
   for (j=0; j<3; j++)
   m[i][j] = (i == j);
}

/*void display1(void){*/
/*int i;*/
/*glClear(GL_COLOR_BUFFER_BIT);*/
/*glBegin(GL_LINES);*/
/*	glVertex2f(0.0,250.0);*/
/*	glVertex2f(0.0,-250.0);*/
/*glEnd();*/
/*glBegin(GL_LINES);*/
/*	glVertex2f(-250.0,0.0);*/
/*	glVertex2f(250.0,0.0);*/
/*glEnd();*/

/*glBegin(GL_POLYGON);*/
/*	glColor3f(1,1,1);*/
/*	for(i=0;i<NEdges;i++){*/
/*		glVertex2f(ptsIni[i][0],ptsIni[i][1]);*/
/*	}*/
/*glEnd();*/
/*glBegin(GL_POLYGON);*/
/*	glColor3f(1,1,0);*/
/*	for( i=0;i<NEdges;i++){*/
/*		glVertex2f(ptsFin[i][0],ptsFin[i][1]);*/
/*	}*/
/*glEnd();*/

/*glFlush();*/
/*for( i=0;i<NEdges;i++){*/
/*		ptsIni[i][0] = ptsFin[i][0];*/
/*		ptsIni[i][1] = ptsFin[i][1];*/
/*	}*/
/*TransformPoints();*/
/*}*/


void matrixPreMultiply(Matrix3x3 a , float b[3])
// Multiplies matrix a times b, putting result in b
{
   int i,j;
   float tmp[3];
   for (i = 0; i < 3; i++)
     for (j = 0; j < 3; j++)
       tmp[i] = a[i][0]*b[0] + a[i][1]*b[1] + a[i][2]*b[2];
   
   for (i = 0; i < 3; i++)
   	 fin[i] = tmp[i];
}

void Translate(int tx, int ty,float b[3])
{
   Matrix3x3 m;
   matrixSetIdentity(m);
   m[0][2] = tx;
   m[1][2] = ty;
   matrixPreMultiply(m, b);
}

void Scale(float sx , float sy,float b[3])
{
   Matrix3x3 m;
   matrixSetIdentity(m);
   m[0][0] = sx;
   m[0][2] = (1 - sx)*refpt[0];
   m[1][1] = sy;
   m[1][2] = (1 - sy)*refpt[1];
   matrixPreMultiply(m , b);
}

void Rotate(float a,float b[3])
{
   Matrix3x3 m;
   matrixSetIdentity(m);
   a = a*22/1260;
   m[0][0] = cos(a);
   m[0][1] = -sin(a) ;
   m[0][2] = refpt[0]*(1 - cos(a)) + refpt[1]*sin(a);
   m[1][0] = sin(a);
   m[1][1] = cos(a);
   m[1][2] = refpt[1]*(1 - cos(a)) - refpt[0]*sin(a);
   matrixPreMultiply(m , b);
}

void Reflect(int xy,float b[3])
{
   Matrix3x3 m;
   matrixSetIdentity(m);
   if(xy == 1){
   	m[0][0] = -1;
   	m[1][1]=-1;
   }
   else if(xy == 2){
   	m[1][1]=-1;
   }
   else if(xy==3){
   	m[0][0] = -1;
   }
   else if(xy==4){
   }
   matrixPreMultiply(m , b);
}

void Shear(int choiceShear,int shearvalue,float b[3])
{
   Matrix3x3 m;
   matrixSetIdentity(m);
   if(choiceShear==1){
   m[0][1]=shearvalue;
   }
   else if(choiceShear==2){
   m[1][0]=shearvalue;
   }
  else if(choiceShear==3){
   m[0][1]=shearvalue;
   m[1][0]=shearvalue;
   }
   /*if(xy == 1)
     m[0][1] = shearValue;
   if(xy == 2)
     m[1][0] = shearValue;*/
   matrixPreMultiply(m , b);
}


void cCircle(float x0,float y0,float r0,int k)    // draws the coloured circle
{	
  float xCenter=x0,yCenter=y0,r=r0;
  float x=0,y=r;
  int i;
  float p = 3/2 - r;				
  glColor3f(1,1,1);
  
  glBegin(GL_POLYGON);	
/*  glColor3f(0.8,0.5*(((int)x0)%11000),0.0);*/
  glColor3f(1,0,0);
  if(k==3) {
  	 glColor3f(0.2,0.1,1);
  }
  while(x<=y)
  {
    glVertex2i(xCenter+x,yCenter+y);
    glVertex2i(xCenter+y,yCenter+x);
    glVertex2i(xCenter+y,yCenter-x);
    glVertex2i(xCenter+x,yCenter-y); 
    glVertex2i(xCenter-x,yCenter-y);
    glVertex2i(xCenter-y,yCenter-x); 
    glVertex2i(xCenter-y,yCenter+x);
    glVertex2i(xCenter-x,yCenter+y);

    if (p<0)
    {
    	p += (2*x)+3;
    }
    else 
    {
		p += (2*(x-y))+5;
		y -= 1;
    }
    x++;
  }
  glEnd();
  //glFlush();
  
}




void display1(void){
	glClear(GL_COLOR_BUFFER_BIT);

/*	glLineWidth(10);*/
	
	glBegin(GL_POLYGON);			//Goalpost
		glColor3f(0,0.5,0);
		glVertex2f(0,0);
		glVertex2f(500,0);
		glVertex2f(500,500);
		glVertex2f(000,500);
	glEnd();
	
	glColor3f(1,1,1);
	glBegin(GL_LINES);			//Goalpost
		
		glVertex2f(500,390);
		glVertex2f(300,390);
		
		glVertex2f(500,90);
		glVertex2f(300,90);
		
		glVertex2f(300,390);
		glVertex2f(300,90);
		
	glEnd();
	
	
	glBegin(GL_LINES);			//man 1
		glColor3f(1,0,0);
		glVertex2d(X1,Y1);
		glVertex2d(X1,Y1+50);
		
		glVertex2f(X1,Y1+30);		//hand
		glVertex2f(X1+20,Y1+40);
		
		glVertex2f(X1,Y1+30);
		glVertex2f(X1-20,Y1+40);
		
		glVertex2f(X1,Y1);		//legs
		glVertex2f(X1+20,Y1-20);
		
		glVertex2f(X1,Y1);
		glVertex2f(X1-20,Y1-20);
		
		
	glEnd();
	cCircle(X1,Y1+50,10,0);

/*	glLineWidth(10);*/
		
	glBegin(GL_LINES);			//man 2
		glColor3f(1,0,0);
		glVertex2f(X2,Y2);
		glVertex2f(X2,Y2+50);
		
		glVertex2f(X2,Y2+30);		//hand
		glVertex2f(X2+20,Y2+40);
		
		glVertex2f(X2,Y2+30);
		glVertex2f(X2-20,Y2+40);
		
		glVertex2f(X2,Y2);		//legs
		glVertex2f(X2+20,Y2-20);
		
		glVertex2f(X2,Y2);
		glVertex2f(X2-20,Y2-20);
		
	glEnd();
	cCircle(X2,Y2+50,10,0);
/*	flg=1;*/
	if(!flg) {		// flg = 0 Player -1
		bx1 = X1+20;
		by1 = Y1-5;
	}
	else if(flg==1) {
		bx1 = X2+20;
		by1 = Y2-5;
		
	}
	else if(flg==2) {	//flg=2 , ball at goalpost
		bx1=470;
		by1 = 250;
	}
	glColor3f(0,0,1);									
	glBegin(GL_LINES);			//Goalpost
		glColor3f(0,0,1);
		glVertex2f(500,300);
		glVertex2f(400,300);
		glVertex2f(400,200);
		glVertex2f(500,200);
	glEnd();
	glBegin(GL_LINES);			//Goalpost
		glColor3f(0,0,1);
		
		glVertex2f(400,300);
		glVertex2f(400,200);
		
	glEnd();
	
	
	cCircle(bx1,by1,15,3);		// ball
	
	
	
	
	glutSwapBuffers();
	glFlush();


}

void slp() {
/*	usleep(2000);*/
	glutPostRedisplay();
	
}
void kick() {
	
	if(flg==0) {	// player one
	
		bx1 = X1+20;
		float i;
		float factor = (X2-X1)/(Y2-Y1);
		
		for(;bx1<=X2+20;) {
			bx1+=factor;
			by1+=1;
			slp();
/*			glutPostRedisplay();*/
/*			usleep(2000);*/
		}
		flg=1;
	}
	else if(flg==1) {	// player two
	
		bx1 = X2+20;
		float i;
		float factor = (X1-X2)/(Y2-Y1);
		
		for(;bx1<=X1+20;) {
			bx1+=factor;
			by1-=1;
			slp();
/*			glutPostRedisplay();*/
/*			usleep(2000);*/
		}
		flg=0;
	}
}



void goal() {
/*	float gx = 470;*/
/*	float gy = 250;*/
/*	bx1 = gx;*/
/*	bx2 = gy;*/
/*	*/
	flg=2;
	slp();
}



void init(){
	X1=100;
	Y1=100;
	
	X2=125;
	Y2=350;
	flg=0;
	

	bx1 = X1+15;
	by1 = Y1-5;
	
	bx2 = X2+15;
	by2 = Y2-5;



}


void keyPressed (unsigned char key, int x, int y) {  
	if(key=='q'){
		if(X1<=300)
			X1+=5;

		glutPostRedisplay();
	}
	else if(key=='w'){
		if(X2<=300)
			X2+=5;
		glutPostRedisplay();
	}
	else if(key=='s'){
		kick();
		// Man 2 Kick
		
/*		glutPostRedisplay();*/
	}
	else if(key=='g'){
		goal();
		// anyone kicks goal
		
	}
	else if(key=='r'){
		init();
		glutPostRedisplay();
		// anyone kicks goal
		
	}


}












int main(int argc,char **argv ) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("Football");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);

	init();


	glutDisplayFunc(display1);
	glutKeyboardFunc(keyPressed);

	glutMainLoop();


}
