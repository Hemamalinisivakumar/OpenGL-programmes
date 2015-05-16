#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>

/**
*Program Description:
*Basic Scenery with Mountain, River, Hut, Sun and Man
*Man walks from river to hut during daytime 
*At ninght stays at hut
*In the morning he walks and continues the cycle
*
**/

//typecast 3x3 matrix
typedef float Matrix3x3 [3][3];

float ref[3];
float theta;
float fin[3];
float CirRef[3];
float CirCen[3];
int k,inc,moon;
float Grass_line[4][2];
float end[3];
float thetaCir;
void calPts();
float translate_man;
int fwd;
void matrixPreMultiply(Matrix3x3 a , float b[3]);
void init();
float Apts[3][3],Bpts[3][3],Cpts[3][3];//bird pts
float hut[5][3],river[4][3],mountain[8][3]; // hut river and mountain
void matrixSetIdentity(Matrix3x3 m) {
/*Matrix3x3 theMatrix*/
// Initialises the matrix as Unit Matrix

   int i, j;
   for (i=0; i<3; i++)
   for (j=0; j<3; j++)
   m[i][j] = (i == j);
}


//rotate b about refpt
void Rotate(float a,float b[3],float refpt[3]){
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



//translate b with tx and ty appropriately
void Translate(int tx, int ty,float b[3])
{
   Matrix3x3 m;
   matrixSetIdentity(m);
   m[0][2] = tx;
   m[1][2] = ty;
   matrixPreMultiply(m, b);
}
//redisplay screen
void redisp(){
/*	sleep();*/
	if(moon==0)
		usleep(2*100000);
	else {	//moon=1
		usleep(2*10000);
/*		sleep(3);*/
	}
	glutPostRedisplay();

}

//draw sun at x0,y0 of rad r0
void Sun(float x0,float y0,float r0,int k)    // draws the sun
{	
  float xCenter=x0,yCenter=y0,r=r0;
  float x=0,y=r;
  int i;
  float p = 3/2 - r;				
  glColor3f(1,1,1);
  
  glBegin(GL_POLYGON);
  glColor3f(0.8,0.5,0.0);
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
  
}

void Circle(float ax,float ay,float ar,int k)			// used for drawing head of body
{
	

  	const PI = 3.141592;
    const float X = ax;
    const float Y = ay;
    const float Radius = ar;
    int col;

	glColor3f (1,0, 0);


    glBegin (GL_POLYGON);
    float angle;
    for(angle=0;angle<=PI*2;angle+=0.01) //  Circumference of circle = 2PI * r
        glVertex2f (X + sin(angle) * Radius, Y + cos(angle) * Radius);
    
    glEnd ();	

}
void moon_show(){
	

  	const PI = 3.141592;
    float X = 250;
    float Y = 850;
    float Radius = 40;
    int col;

	//Change colour
    glColor3f (1,1,1); 


    glBegin (GL_POLYGON);
    float angle;
    for(angle=0;angle<=PI*2;angle+=0.01) //  Circumference of circle = 2PI * r
        glVertex2f (X + sin(angle) * Radius, Y + cos(angle) * Radius);
    
    glEnd ();	

    X = 260;
    Y = 870;
    Radius = 40;

	//look like ex
    glColor3f (0,0,0); 


    glBegin (GL_POLYGON);
   // float angle;
    for(angle=0;angle<=PI*2;angle+=0.01) //  Circumference of circle = 2PI * r
        glVertex2f (X + sin(angle) * Radius, Y + cos(angle) * Radius);
    
    glEnd ();	
	moon=1;
	if(!(CirCen[0]>1100 || CirCen[0]< -100))		//if its for daytime reinitialize scene
   	 init();

}

void display1(void){
	glClear(GL_COLOR_BUFFER_BIT);
	
	//if night bg colour black else blue
	glBegin(GL_POLYGON);
		if(moon==1)
			glColor3f(0,0,0);
		else
			glColor3f(0,0,1);
			
		glVertex2f(0,1000);
		glVertex2f(1000,1000);
		glVertex2f(1000,0);
		glVertex2f(0,0);

	glEnd();

	//draw grass 
	glBegin(GL_POLYGON);
		glColor3f(0,1,0);
		glVertex2f(Grass_line[0][0],Grass_line[0][1]);
		glVertex2f(Grass_line[1][0],Grass_line[1][1]);
		glVertex2f(Grass_line[2][0],Grass_line[2][1]);
		glVertex2f(Grass_line[3][0],Grass_line[3][1]);

	glEnd();
	
	//  draw hut
	glBegin(GL_POLYGON);
		glColor3f(0.78,0.06,0.87);
		glVertex2f(730,200);
		glVertex2f(730,530);
		glVertex2f(790,500);
		glVertex2f(790,170);

	glEnd();
	
	glBegin(GL_POLYGON);
		glColor3f(0.60,0.55,0.60);
		glVertex2f(730,530);
		glVertex2f(755,570);
		glVertex2f(790,500);
	glEnd();
	
	
	glBegin(GL_POLYGON);
		glColor3f(1,0.5,0.5);
		glVertex2f(755,570);
		glVertex2f(1000,570);
		glVertex2f(1000,500);
		glVertex2f(790,500);
	glEnd();
	
	glBegin(GL_POLYGON);
		glColor3f(0.5,0.5,0.5);
		glVertex2f(790,500);
		glVertex2f(1000,500);
		glVertex2f(1000,170);
		glVertex2f(790,170);
	glEnd();
	
	
	// river
	glBegin(GL_POLYGON);		 
		glColor3f(0,0.3,0.7);
		glVertex2f(river[0][0],river[0][1]);
		glVertex2f(river[1][0],river[1][1]);
		glVertex2f(river[2][0],river[2][1]);
		glVertex2f(river[3][0],river[3][1]);
	glEnd();
	
	// draw mountain
	glBegin(GL_POLYGON);		
		glColor3f(0.8,0.3,0.7);
		glVertex2f(mountain[0][0],mountain[0][1]);
		glVertex2f(mountain[1][0],mountain[1][1]);
		glVertex2f(mountain[2][0],mountain[2][1]);
		glVertex2f(mountain[3][0],mountain[3][1]);
		glVertex2f(mountain[4][0],mountain[4][1]);
		glVertex2f(mountain[5][0],mountain[5][1]);
		glVertex2f(mountain[6][0],mountain[6][1]);
		glVertex2f(mountain[7][0],mountain[7][1]);
	glEnd();
	
	
	
	
	
	// Draw man at day
	if(!moon) {			

		glBegin(GL_LINES);
			glColor3f(0,0,0);
			glVertex2f(ref[0],ref[1]);
			glVertex2f(end[0],end[1]);
		glEnd();
		
		//man head
		Circle(ref[0],ref[1],15,k);			
	}
	
	//Draw Sun 
	Sun(CirCen[0],CirCen[1],50,0);		

	//if night
	if(moon==1){
		moon_show();
	}	
	
	//draw bird1
	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex2f(Apts[0][0],Apts[0][1]);
		glVertex2f(Apts[1][0],Apts[1][1]);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex2f(Apts[0][0],Apts[0][1]);
		glVertex2f(Apts[2][0],Apts[2][1]);
	glEnd();
	

	//draw bird2
	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex2f(Bpts[0][0],Bpts[0][1]);
		glVertex2f(Bpts[1][0],Bpts[1][1]);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex2f(Bpts[0][0],Bpts[0][1]);
		glVertex2f(Bpts[2][0],Bpts[2][1]);
	glEnd();



	//draw bird3
	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex2f(Cpts[0][0],Cpts[0][1]);
		glVertex2f(Cpts[1][0],Cpts[1][1]);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex2f(Cpts[0][0],Cpts[0][1]);
		glVertex2f(Cpts[2][0],Cpts[2][1]);
	glEnd();
	
	
	
	glutSwapBuffers();
	calPts();
	
}


void calPts(){
	
	// For Man
	if(fwd==1){	//if man is moving fwd(backward for coordinates)
		if(k&1) {	//if odd iteration	
			Rotate(-theta,ref,end);	//rotate man head with respect to legs by minus theta
			ref[0]=fin[0];ref[1]=fin[1];ref[2]=fin[2];	//get rotated head 
	
		}
	
		else {	//else even iteration
			Rotate(theta,ref,end);	//rotate man head with respect to legs by plus theta
			ref[0]=fin[0];ref[1]=fin[1];ref[2]=fin[2];	//get rotated head 
		}
		end[0]+=(-translate_man);	//move man leg fordward(backward in coordinate system)
		ref[0]+=(-translate_man);	//move man head fordward(backward in coordinate system)
		if(ref[0]<=350)	//if man reached river
			fwd=0;	//unset flag ---> move backward
	}
	else{	//if man is backward fwd(forward for coordinates)
		if(k&1) {	//if odd iteration
			Rotate(-theta,ref,end);	//rotate man head with respect to legs by minus theta
			ref[0]=fin[0];ref[1]=fin[1];ref[2]=fin[2];	//get rotated head
	
		}
		else {	//else even iteration
			Rotate(theta,ref,end);	//rotate man head with respect to legs by plus theta
			ref[0]=fin[0];ref[1]=fin[1];ref[2]=fin[2];	//get rotated head
		}
		end[0]+=(translate_man); //move man leg backward(forward in coordinate system)
		ref[0]+=(translate_man); //move man head backward(forward in coordinate system)
		if(ref[0]>=800)	//if man reached hut
			fwd=1;	//change direction---> move forward

		
	}
	k++;	//increment counter


	/*calculating rotation of sun*/

	Rotate(-thetaCir,CirCen,CirRef);	// Rotate Sun centre about Circle reference
	CirCen[0]=fin[0];CirCen[1]=fin[1];CirCen[2]=fin[2];	//get sun center after rotation


	//if sun centre out of scene	
	if((CirCen[0]>1100 || CirCen[0]< -100)) {	
		
		moon=1;	//set night
		redisp(); //neccessary for displayiing moon
		return;
	}
	
	/*bird move 1*/
	if(k&1){	//if odd iteration
		//Bird1
		Rotate(-50,Apts[1],Apts[0]);	//rotate a left wing by -50
		Apts[1][0]=fin[0];Apts[1][1]=fin[1];Apts[1][2]=fin[2];	//get rotated coordinates 	
		Rotate(50,Apts[2],Apts[0]);	//rotate a right wing by +50
		Apts[2][0]=fin[0];Apts[2][1]=fin[1];Apts[2][2]=fin[2];	//get rotated coordinates
		
		//Bird 2
		Rotate(-50,Bpts[1],Bpts[0]);//rotate a left wing by -50
		Bpts[1][0]=fin[0];Bpts[1][1]=fin[1];Bpts[1][2]=fin[2];	//get rotated coordinates
		Rotate(50,Bpts[2],Bpts[0]);//rotate a right wing by +50
		Bpts[2][0]=fin[0];Bpts[2][1]=fin[1];Bpts[2][2]=fin[2];	//get rotated coordinates

		//Bird 3
		Rotate(-50,Cpts[1],Cpts[0]);//rotate a left wing by -50
		Cpts[1][0]=fin[0];Cpts[1][1]=fin[1];Cpts[1][2]=fin[2];	//get rotated coordinates
		Rotate(50,Cpts[2],Cpts[0]);//rotate a right wing by +50
		Cpts[2][0]=fin[0];Cpts[2][1]=fin[1];Cpts[2][2]=fin[2];	//get rotated coordinates


	}
	else{	// even iteration
		//Bird 1
		Rotate(50,Apts[1],Apts[0]);//rotate a left wing by +50
		Apts[1][0]=fin[0];Apts[1][1]=fin[1];Apts[1][2]=fin[2];	//get rotated coordinates
		Rotate(-50,Apts[2],Apts[0]);//rotate a right wing by -50
		Apts[2][0]=fin[0];Apts[2][1]=fin[1];Apts[2][2]=fin[2];	//get rotated coordinates
		
		//Bird 2
		Rotate(50,Bpts[1],Bpts[0]);//rotate a left wing by +50
		Bpts[1][0]=fin[0];Bpts[1][1]=fin[1];Bpts[1][2]=fin[2];	//get rotated coordinates
		Rotate(-50,Bpts[2],Bpts[0]);//rotate a right wing by -50
		Bpts[2][0]=fin[0];Bpts[2][1]=fin[1];Bpts[2][2]=fin[2];	//get rotated coordinates

		//Bird 3
		Rotate(50,Cpts[1],Cpts[0]);//rotate a left wing by 50
		Cpts[1][0]=fin[0];Cpts[1][1]=fin[1];Cpts[1][2]=fin[2];	//get rotated coordinates
		Rotate(-50,Cpts[2],Cpts[0]);//rotate a right wing by -50
		Cpts[2][0]=fin[0];Cpts[2][1]=fin[1];Cpts[2][2]=fin[2];	//get rotated coordinates


	}
	//Bird1 translation
	Apts[0][0]-=5;//
	Apts[0][1]+=5;

	Apts[1][0]-=5;
	Apts[1][1]+=5;

	Apts[2][0]-=5;
	Apts[2][1]+=5;

	//Bird2 translation
	Bpts[0][0]-=5;
	Bpts[0][1]+=5;

	Bpts[1][0]-=5;
	Bpts[1][1]+=5;

	Bpts[2][0]-=5;
	Bpts[2][1]+=5;

	//Bird3 translation
	Cpts[0][0]-=5;
	Cpts[0][1]+=5;

	Cpts[1][0]-=5;
	Cpts[1][1]+=5;

	Cpts[2][0]-=5;
	Cpts[2][1]+=5;
	// sleep and redisplay appropriately	
	redisp();
  
}
void init(){
	if(moon==1)
		//initial value of k
		k=0;
	
	//trans man and fwd=1 moves toward left
	translate_man=14;
	fwd=1;
	
	/*Initial points for Man
	 ref = Upper end
	 end = Lower end*/
	ref[0]=750;
	ref[1]=300;
	ref[2]=1;
	end[0]=750;
	end[1]=200;
	end[2]=1;
	
	//moon=0 initially
	moon=0;
	
	//Initial points for Sun
	// Radius for Rotation of Sun = Ref[1] - Cen[1]
	CirRef[0]=250;
	CirRef[1]=-1500;
	CirRef[2]=1;
	CirCen[0]=-100;
	CirCen[1]=900;
	CirCen[2]=1;
	theta=15;
	thetaCir=0.5;
	
	// INitial points of birds
	//Bird 1
	// 0 - Centre
	// 1 - Left wing
	// 2 - Right wing
	Apts[0][0]=700;
	Apts[0][1]=720;
	Apts[0][2]=1;
	
	Apts[1][0]=680;
	Apts[1][1]=750;
	Apts[1][2]=1;
	
	Apts[2][0]=720;
	Apts[2][1]=750;
	Apts[2][2]=1;
	//Bird 2
	Bpts[0][0]=700;
	Bpts[0][1]=770;
	Bpts[0][2]=1;
	
	Bpts[1][0]=680;
	Bpts[1][1]=800;
	Bpts[1][2]=1;
	
	Bpts[2][0]=720;
	Bpts[2][1]=800;
	Bpts[2][2]=1;

	//BIrd 3	
	Cpts[0][0]=750;
	Cpts[0][1]=740;
	Cpts[0][2]=1;
	
	Cpts[1][0]=730;
	Cpts[1][1]=770;
	Cpts[1][2]=1;
	
	Cpts[2][0]=770;
	Cpts[2][1]=770;
	Cpts[2][2]=1;
	
	//Line for drawing grass
	//left-top pt.
	Grass_line[0][0]=0;
	Grass_line[0][1]=400;
	
	//right-top pt.
	Grass_line[1][0]=1000;
	Grass_line[1][1]=400;
	
	//bottom-right pt.
	Grass_line[2][0]=1000;
	Grass_line[2][1]=0;
	
	//bottom-left pt.
	Grass_line[3][0]=0;
	Grass_line[3][1]=0;
	
	
	//hut
	hut[0][0]=800;
	hut[0][1]=200;
	
	hut[1][0]=950;
	hut[1][1]=200;
	
	hut[2][0]=950;
	hut[2][1]=390;
	
	hut[3][0]=875;
	hut[3][1]=500;
	
	hut[4][0]=800;
	hut[4][1]=390;
	
	//river
	
	river[0][0]=200;
	river[0][1]=0;
	
	river[1][0]=300;
	river[1][1]=400;
	
	river[2][0]=400;
	river[2][1]=400;
	
	river[3][0]=300;
	river[3][1]=0;
	
	//mountain
	mountain[0][0]=0;
	mountain[0][1]=400;
	
	mountain[1][0]=200;
	mountain[1][1]=600;
	
	mountain[2][0]=300;
	mountain[2][1]=400;
	
	mountain[3][0]=400;
	mountain[3][1]=800;
	
	mountain[4][0]=500;
	mountain[4][1]=400;
	
	mountain[5][0]=600;
	mountain[5][1]=600;
	
	mountain[6][0]=700;
	mountain[6][1]=400;
	
	mountain[7][0]=0;
	mountain[7][1]=400;

	
	

}
int main(int argc ,char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("MyPendulum");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,1000,0,1000);

	//initialize the coordinates of various components
	init();

	//diplay
	glutDisplayFunc(display1);

	glutMainLoop();
	
	
}
