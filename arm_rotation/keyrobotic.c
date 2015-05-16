#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
float APts[1][3],BPts[1][3],CPts[1][3],pivot[2],fin[3],ref[2];
float thetaA,thetaC,thetaB;
float fin[3];
typedef float Matrix3x3 [3][3];
int k,inc;
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
void keyPressed (unsigned char key, int x, int y) {  
	if(key=='q'){
		ref[0]=BPts[0][0];ref[1]=BPts[0][1];
		Rotate(thetaC,CPts[0]);
		CPts[0][0]=fin[0];CPts[0][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;CPts[0][2]=1;
		glutPostRedisplay();
	}
	else if(key=='a'){
		ref[0]=BPts[0][0];ref[1]=BPts[0][1];
		Rotate(-thetaC,CPts[0]);
		CPts[0][0]=fin[0];CPts[0][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;CPts[0][2]=1;
		glutPostRedisplay();
	}
	else if(key=='w'){
		ref[0]=APts[0][0];ref[1]=APts[0][1];
		Rotate(thetaB,BPts[0]);
		BPts[0][0]=fin[0];BPts[0][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;BPts[0][2]=1;
		Rotate(thetaB,CPts[0]);
		CPts[0][0]=fin[0];CPts[0][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;CPts[0][2]=1;
		glutPostRedisplay();
	}
	else if(key=='s'){
		ref[0]=APts[0][0];ref[1]=APts[0][1];
		Rotate(-thetaB,BPts[0]);
		BPts[0][0]=fin[0];BPts[0][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;BPts[0][2]=1;
		Rotate(-thetaB,CPts[0]);
		CPts[0][0]=fin[0];CPts[0][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;CPts[0][2]=1;
		glutPostRedisplay();
	}
	else if(key=='e'){
		ref[0]=pivot[0];ref[1]=pivot[1];
		Rotate(thetaA,APts[0]);
		APts[0][0]=fin[0];APts[0][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;APts[0][2]=1;

		Rotate(thetaA,BPts[0]);
		BPts[0][0]=fin[0];BPts[0][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;BPts[0][2]=1;
		Rotate(thetaA,CPts[0]);
		CPts[0][0]=fin[0];CPts[0][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;CPts[0][2]=1;

		glutPostRedisplay();
	}
	else if(key=='d'){
		ref[0]=pivot[0];ref[1]=pivot[1];
		Rotate(-thetaA,APts[0]);
		APts[0][0]=fin[0];APts[0][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;APts[0][2]=1;

		Rotate(-thetaA,BPts[0]);
		BPts[0][0]=fin[0];BPts[0][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;BPts[0][2]=1;
		Rotate(-thetaA,CPts[0]);
		CPts[0][0]=fin[0];CPts[0][1]=fin[1]/*+(BPts[i][1]-BPts[i-1][1])*/;CPts[0][2]=1;

		glutPostRedisplay();
	}


}
void display1(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex2f(pivot[0],pivot[1]);
		glVertex2f(APts[k][0],APts[k][1]);
	glEnd();
	
	glBegin(GL_LINES);
		glColor3f(0,1,0);
		glVertex2f(APts[k][0],APts[k][1]);
		glVertex2f(BPts[k][0],BPts[k][1]);
	glEnd();
	
	glBegin(GL_LINES);
		glColor3f(1,1,1);
		glVertex2f(BPts[k][0],BPts[k][1]);
		glVertex2f(CPts[k][0],CPts[k][1]);
	glEnd();
	glutSwapBuffers();
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
	printf("\n");
	printf("Arm A - RED\n");
	printf("Arm B - GREEN\n");
	printf("Arm C - WHITE\n\n");
	printf("\"e\" to move A up\n");
	printf("\"d\" to move A down\n");
	printf("\"w\" to move B up\n");
	printf("\"s\" to move B down\n");
	printf("\"q\" to move C up\n");
	printf("\"a\" to move C down\n\n");
	
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
	
	thetaA=10;
	thetaB=10;
	thetaC=10;
	glutDisplayFunc(display1);
	glutKeyboardFunc(keyPressed);
	glutMainLoop();

}
