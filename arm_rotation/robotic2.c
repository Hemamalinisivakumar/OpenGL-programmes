#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
float APts[50][3],BPts[50][3],CPts[50][3],pivot[2],fin[3],ref[2];
float theta;
float fin[3];

typedef float Matrix3x3 [3][3];
int k,inc;
void matrixSetIdentity(Matrix3x3 m);
void Rotate(float a,float b[3]);

void redisp();

void display1(void){
	glClear(GL_COLOR_BUFFER_BIT);

	
	
	glBegin(GL_LINES);
		glColor3f(0,APts[k][1]+0.5,APts[k][1]+0.5);
		glVertex2f(pivot[0],pivot[1]);
		glVertex2f(APts[k][0],APts[k][1]);
	glEnd();
	
	glBegin(GL_LINES);
		glColor3f(0,(k*0.1),0);
		glVertex2f(APts[k][0],APts[k][1]);
		glVertex2f(BPts[k][0],BPts[k][1]);
	glEnd();
	
	glBegin(GL_LINES);
		glColor3f(1,1,0);
		glVertex2f(BPts[k][0],BPts[k][1]);
		glVertex2f(CPts[k][0],CPts[k][1]);
	glEnd();
/*	printf("?%d?",k);*/
	k+=inc;
	if(k>49){
		sleep(10);
		k=48;
		inc=-1;
	}
	else if(k<0){
		k=1;
		inc=1;
	}
	glFlush();
	redisp();
}
void calPts(){

	int i;
	float tmp[3];
	for(i=1;i<=49;i++){
		theta=1;
		ref[0]=pivot[0];ref[1]=pivot[1];
		Rotate(theta,APts[i-1]);
		APts[i][0]=fin[0];APts[i][1]=fin[1];APts[i][2]=1;
		
		theta=1;
		Rotate(theta,BPts[i-1]);
		tmp[0]=fin[0];tmp[1]=fin[1];tmp[2]=1;
		ref[0]=APts[i][0];ref[1]=APts[i][1];
		theta=0.5;
		Rotate(theta,tmp);
		BPts[i][0]=fin[0];BPts[i][1]=fin[1]/*+(APts[i][1]-APts[i-1][1])*/;BPts[i][2]=1;
		theta=1;
/*		theta=0.5;*/
		ref[0]=pivot[0];ref[1]=pivot[1];
		Rotate(theta,CPts[i-1]);
		tmp[0]=fin[0];tmp[1]=fin[1]/*+(APts[i][1]-APts[i-1][1])*/;tmp[2]=1;
		ref[0]=APts[i][0];ref[1]=APts[i][1];
		theta=1;
		Rotate(theta,tmp);
		tmp[0]=fin[0];tmp[1]=fin[1]/*+(APts[i][1]-APts[i-1][1])*/;tmp[2]=1;
		ref[0]=BPts[i][0];ref[1]=BPts[i][1];
		Rotate(theta,tmp);
		
		CPts[i][0]=fin[0];CPts[i][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;CPts[i][2]=1;

			
	}
	int m,n;

	for(m=0;m<50;m++){
		printf("Line A : %f :: %f\n",APts[m][0],APts[m][1]);
		printf("Line B : %f :: %f\n",BPts[m][0],BPts[m][1]);
		printf("Line C : %f :: %f\n",CPts[m][0],CPts[m][1]);
		printf("\n");
	}
		
  glutDisplayFunc(display1);
  
  glutMainLoop();




}


int main(int argc ,char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("Robotic");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	k=0;
	inc=1;
	pivot[0]=100;
	pivot[1]=200;
	
	APts[0][0]=190;
	APts[0][1]=200;
	APts[0][2]=1;
	
	BPts[0][0]=260;
	BPts[0][1]=200;
	BPts[0][2]=1;

	CPts[0][0]=330;
	CPts[0][1]=200;
	CPts[0][2]=1;
	
	theta=1;
	calPts();

}



void matrixSetIdentity(Matrix3x3 m){
   int i, j;
   for (i=0; i<3; i++)
   for (j=0; j<3; j++)
   m[i][j] = (i == j);
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
	usleep(50000);
	glutPostRedisplay();

}
