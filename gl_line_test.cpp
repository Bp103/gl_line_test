/* 
    trigonometry go brrrrr
    Bp103	9-24-2022
    
    Requires an implementation of GLUT.
    FreeGLUT works fine.
*/

#include <stdlib.h>
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define winX glutGet(GLUT_WINDOW_WIDTH)
#define winY glutGet(GLUT_WINDOW_HEIGHT)
#define rad 6.28319
#define PI 3.14159265359

#define aspectx 2
#define aspecty 2
int ox=0,oy=0;
float t;

void check()
{
}

void init(){
	gluOrtho2D(640,0,360,0);
	//gluOrtho2D(360,0,640,0);
	glClearColor(1,1,1,0);
}

int len(char *textInput)
{	
	//get text/buffer length the hard way.
	int output=0;
	for(int i=0;textInput[i]!='\0';i++)output=i+1;
	return output;
}
void printg(int x, int y, char text[100])
{
	//graphical print.
	int textLen=len(text);
	for(int i=0;i<textLen;i++)
	{	
		int textX=x-(i*8);
		if((winX<textX)||(textX>0))
		{
			glRasterPos2i(textX,y);
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
		}else{
			break;
		}
	}
}

void cubo(int poly, int pHight, int sHight, int pOffset, float spin, float spinb, int radi, int radib, float j, float r,float g,float b, bool customOffsets,int xoffset, int yoffset,float tilt, float wspin, bool shape, bool shadow, bool cross)
{
	int xcenter=(winX/aspectx);
  	int ycenter=(winY/aspecty);
  	if(!customOffsets){
    	xoffset=int((cos(((j*spinb)+wspin)*rad)*radib));
    	yoffset=int((sin(((j*spinb)+wspin)*rad)*(radib*tilt)));
  	}
  	glBegin(GL_LINES);
  	for(float i=0;i<(poly+1);i++)
	{
		int x=int((cos(((i/poly)+(j*spin)+wspin)*rad)*radi))+xoffset+xcenter;
    		int y=int((sin(((i/poly)+(j*spin)+wspin)*rad)*(radi*tilt)))+yoffset+ycenter;
    		if(i==0){ox=x; oy=y;}
    		
		if(shadow)
		{
			glColor3f(r/4,g/4,b/4);
    			glVertex2f(ox,oy+sHight+pOffset);
			glVertex2f(x,y+sHight+pOffset);
		}
		if(cross)
		{
			glColor3f(r/4,g/4,b/4);
			int tempx=x;
			int tempy=y;
			x=int((cos((((i+(poly/2))/poly)+(j*spin)+wspin)*rad)*radi))+xcenter+xoffset;
    			y=int((sin((((i+(poly/2))/poly)+(j*spin)+wspin)*rad)*(radi*tilt)))+ycenter+yoffset;
    			glVertex2f(ox,oy+sHight+pOffset);
			glVertex2f(x,y+sHight+pOffset);
			x=int((cos((((i+(poly/4))/poly)+(j*spin)+wspin)*rad)*radi))+xcenter+xoffset;
    			y=int((sin((((i+(poly/4))/poly)+(j*spin)+wspin)*rad)*(radi*tilt)))+ycenter+yoffset;
    			glVertex2f(ox,oy+sHight+pOffset);
			glVertex2f(x,y+sHight+pOffset);
			x=tempx;
    			y=tempy;
		}
    		if(shape)
    		{
    			glColor3f(r,g,b);
    			glVertex2f(x,y+(pHight+sHight));
			glVertex2f(ox,oy+(pHight+sHight));
    			glVertex2f(x,y+pHight);
			glVertex2f(x,y+(pHight+sHight));
    			glVertex2f(x,y+pHight);
			glVertex2f(ox,oy+pHight);
    		}
		
		ox=x;
    		oy=y;					
	} 
	glFlush();
	glEnd();                                
}

float frame1,frame2,fps, ffps, ifps;
int realTime, realTimesec;

void display()
{ 
	//fps based timer setup
	frame2=glutGet(GLUT_ELAPSED_TIME);
	fps=(frame2-frame1); 
	frame1=glutGet(GLUT_ELAPSED_TIME);
 	
 	//fps counter
 	realTime=glutGet(GLUT_ELAPSED_TIME);
 	if(realTimesec<realTime)
 	{
 		ffps=ifps;
 		ifps=0;
 		realTimesec=realTime+1000;
 	}
 	ifps++;
	
	//actually starting display stuff
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	int xcenter=(winX/aspectx);
  	int ycenter=(winY/aspecty);
  	
  	//the main ticker
  	t+=0.00005*fps;
  	
  	//tilting math
  	float rot=(sin(t*11)*.5)+0.51;
  	float rotb=(sin(t*4)*.5);
  	
  	
  	
  	//All the shapes. 
  	cubo(4, 0, 90, 40, 1, 1, 500, 1, 0.625, 0,1,0,true,0,0,rot,rotb,false,true,true);
  	
	int pol=1; float inc = (0.625/8);
	for(float i=0;i<0.625;i+=inc)
	{	
		pol++;
		cubo(pol, 0, 90, 40, 8, 8, 20, 310, i, 1,.5,.5,false,0,0,rot,rotb,true,true,true);
	} 
  	cubo(8, 0, 90, 40, -8, 8, 50, 200, t, 0,0,1,true,0,0,rot,rotb,true,true,false);
  	cubo(4, 0, 90, 40, 8, 8, 80, 200, t, 1,0,1,false,0,0,rot,rotb,true,true,false);
  	cubo(3, int((sin(t*50)*35)+30), 20, 70, -16, -3, 30, 100, t, 0,1,0, true,int((cos(((t* -3))*rad)*100)), int((sin(((t* -3))*rad)*(100*rot)))+40,rot,rotb,true,true,false);
	cubo(4, int((sin(t*100)*35)+30), 20, 70, -32, -11, 40, 100, t, 0.5,0.5,1, true,int((cos(((t* -8))*rad)*140)), int((sin(((t* -12))*rad)*(200*rot)))+40,rot,rotb,true,true,false);
	
	//the fps counter display, drawn last to be on top of everything.
	glColor3f(0,0,0);
	char tbuffer[50];
	int n=sprintf(tbuffer, "FPS:%.0f", ffps);
	printg(int(xcenter+((n/2)*8)),(14*sin(t*125))+28, tbuffer);
	/*
	n=sprintf(tbuffer, "ticker:%.20f", t);
	printg(int(xcenter+((n/2)*8)),(14*sin(t*125))+42, tbuffer);
	*/
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char** argv)
{ 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640,360);
	glutCreateWindow("OpenGL go brrrr");
	
	init();
	
	glutDisplayFunc(display);
	glutMainLoop();
}

