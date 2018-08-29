/*

========================================================================
Project -- Computer Graphics 
Department of Computer Science and Engineering @ University of Ioannina

Team: 
Maria Pappa
Lia Dinopulu
========================================================================

*/

/* Inlucde libraries */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

/* Include definitions */
#define BLACK 0
#define WHITE 1
#define RED 2
#define GREEN 3
#define BLUE 4
#define YELLOW 5
#define ORANGE 6
#define PURPLE 7
#define GREY 8
#define BROWN 9
#define GOLD 10
#define PINK 11
#define NAVY 12
#define TURQOISE 13
#define BORDEAUX 14
#define CORAL 15
#define GREENYELLOW 16

int movement=0;
int flag=0;
int flag1=0;
int in_action=0;
#define draw 10
void display();
int state=0,size,size2=-1;
int fl=0;
int pol=0;
int xtemp;
int ytemp;
int menu=1;
int move=1;
int lineColor=BLACK,backgroundColor=WHITE;;
void shapes();
void vertex(int x,int y);
void polygon();
void display();
void mouse(int x, int y);
void mouseclick(int x, int y);
void fill_color();
void line_color();
void init();
void buttonmove(GLint button, GLint action, GLint xMouse, GLint yMouse);
void drawLineSegment(int x1,int y1, int x2,int y2);
//size-->shapes
//size2-->koryfes
int **X=NULL,**Y=NULL,*numSize=NULL,*color,*color2;;
int ptCtr = 0;
int A,B;
int numOfRule=-1;
void addcolor(int color1,float totalcolor[3]);


int isLeft(int x, int y, int i, int j)
{
	return ((X[i][j+1]-X[i][j])*(y-Y[i][j]) - (x-X[i][j])*(Y[i][j+1]-Y[i][j]) ) ;
}

//x,y to shmeio
//p to polygwno
int wn_PnPoly(int x, int y, int p)
{
	int wn=0,i,j;
	//x=-5+x*10/600.0;
	//y=5-y*0.02;
	//y=y*10/600.0;
	for(i=0;i<numSize[p]-1;i++)
	{
		if(Y[p][i]<=y)
		{
			if(Y[p][i+1] > y)
			{
				if(isLeft(x,y,p,i) > 0)
				{
					wn++;
				}
			}
		}
		else
		{	
			if(Y[p][i+1] <=y)
			{
				if(isLeft(x,y,p,i) <0)
				{
					wn--;
				}
			}
		}	
	}
	return(wn);
}

void setcolorFill(int *in)
{
	int i, p;
	float totalcolor[3];
	int counter=0;
	totalcolor[0]=0;
	totalcolor[1]=0;
	totalcolor[2]=0;

	for(i=0;i<=size;i++)
	{
		if(in[i]==1)
		{
			counter++;
			addcolor(color2[i],totalcolor);			
		}
	}
	if(counter!=0)
	{
		totalcolor[0]/=counter;
		totalcolor[1]/=counter;
		totalcolor[2]/=counter;		
		glColor3f(totalcolor[0],totalcolor[1],totalcolor[2]);
	}
	else
	{
		glColor3f(1,1,1);
	}
}

void setcolor(int color1);

void fill(int rule)
{

	int i,j,wn,p;
	int in[size];
	//int *in=
	if(rule!=-1)
		if(X!=NULL)
		{		
			for(i=0;i<600;i++)
			{
				for(j=0;j<500;j++)
				{
					for(p=0;p<=size;p++)
					{
						wn=wn_PnPoly(i,j,p);
                        wn=-wn;
					if(numOfRule==1)
					{
						if(wn!=0)
							in[p]=1;
						else
							in[p]=0;
					}
					else if(numOfRule==2)
					{
						if(wn!=0)
							in[p]=1;
						else
							in[p]=0;
					}
					else if(numOfRule==3)
					{
						if(int(ceil((wn/2.0)))%2==1)
							in[p]=1;
						else
							in[p]=0;
					}
					else if(numOfRule==4)
					{
						if(wn>0)
							in[p]=1;
						else
							in[p]=0;
					}
				}
				setcolorFill(in);
				glBegin(GL_POINTS);
				glVertex2f (-5+i*double(10.0/600.0), 5-j*double(10.0/500.0));
				glEnd();
			}
		}
	}
}

void findsquare(int x, int y)
{
	int a = 5;
	int xmove, ymove;
	for(int i=0; i<=size; i++)
	{
		for(int j=0; j<=numSize[i]; j++)
		{				
			xmove=X[i][j];
			ymove=Y[i][j];			
			if((x<=(xmove+a))&&(x>=(xmove-a)))
			{
				if((y<=(ymove+a))&&(y>=(ymove-a)))
				{
					A=i;
					B=j;
					movement=1;
				}
			}
		}
	}
}

void drawsquare(int x1, int y1) 
{
	int a=5;
	glColor3f(1.0, 0.0, 0.0);    			//Change the object colors to green
	glBegin(GL_QUADS);				//Start drawing quads
	glVertex2f (-5+(x1+a)*10/600.0, 5-(y1+a)*0.02);
	glVertex2f (-5+(x1-a)*10/600.0, 5-(y1+a)*0.02);
	glVertex2f (-5+(x1-a)*10/600.0, 5-(y1-a)*0.02);
	glVertex2f (-5+(x1+a)*10/600.0, 5-(y1-a)*0.02);
	glEnd(); 
}

void move1()
{
	int xmove, ymove;

	if((X!=NULL)&&(Y!=NULL))
	{
		for(int i=0; i<=size; i++)
		{
			for(int j=0; j<numSize[i]; j++)
			{
				xmove=X[i][j];
				ymove=Y[i][j];
				drawsquare(xmove, ymove);
			}
		}
	}	
}

void changeLineColor(int color1)
{
	lineColor=color1;
}

void changeBackgroundColor(int color1)
{
	backgroundColor=color1;
}

void addcolor(int color1, float totalcolor[3])
{
	switch(color1){
		case PINK:							
			totalcolor[0]+=1.00;
			totalcolor[1]+=0.11;
			totalcolor[2]+=0.68;
		
			break;
		case BLACK:							
			totalcolor[0]+=0;
			totalcolor[1]+=0;
			totalcolor[2]+=0;

			break;
		case GREEN:
			totalcolor[0]+=0;
			totalcolor[1]+=1;
			totalcolor[2]+=0;

			break;
		case YELLOW:
			totalcolor[0]+=1.00;
			totalcolor[1]+=1;
			totalcolor[2]+=0;

			break;
		case BROWN: 
			totalcolor[0]+=0.647059;
			totalcolor[1]+=0.164706;
			totalcolor[2]+=0.164706;

			break;
		case PURPLE:
			totalcolor[0]+=0.73;
			totalcolor[1]+=0.16;
			totalcolor[2]+=0.96;

			break;
		case ORANGE:
			totalcolor[0]+=0;
			totalcolor[1]+=0.5;
			totalcolor[2]+=0;

			break;
		case BLUE:
			totalcolor[0]+=0;
			totalcolor[1]+=0;
			totalcolor[2]+=1;

			break;
		case RED:
			totalcolor[0]+=1.00;
			totalcolor[1]+=0;
			totalcolor[2]+=0;

			break;
		case GOLD:
			totalcolor[0]+=0.8;
			totalcolor[1]+=0.4980391;
			totalcolor[2]+=0.19607;

			break;
		case NAVY:
			totalcolor[0]+=0.137255;
			totalcolor[1]+=0.137255;
			totalcolor[2]+=0.556863;

			break;
		case TURQOISE:
			totalcolor[0]+=0.439216;
			totalcolor[1]+=0.858824;
			totalcolor[2]+=0.858824;

			break;
		case BORDEAUX:
			totalcolor[0]+=0.858824;
			totalcolor[1]+=0.439216;
			totalcolor[2]+=0.576471;

			break;
		case CORAL:
			totalcolor[0]+=1.00;
			totalcolor[1]+=0.498039;
			totalcolor[2]+=0;

			break;
		case GREENYELLOW:
			totalcolor[0]+=0.576471;
			totalcolor[1]+=0.858824;
			totalcolor[2]+=0.439216;

			break;
		case GREY:
			totalcolor[0]+=0.90;
			totalcolor[1]+=0.90 ;
			totalcolor[2]+=0.90;

			break;
		case WHITE:
			totalcolor[0]+=1;
			totalcolor[1]+=1 ;
			totalcolor[2]+=1;

			break;
	}
}

void setcolor(int color1)
{
	switch(color1)
	{
		case PINK:							
			glColor3f(1.00, 0.11, 0.68);
			break;
		case BLACK:							
			glColor3f(0.0f, 0.0f, 0.0f);
			break;
		case GREEN:
			glColor3f(0.0, 1.0, 0.0);
			break;
		case YELLOW:
			glColor3f(1.0, 1.0 , 0.0);
			break;
		case BROWN: 
			glColor3f(0.647059, 0.164706 , 0.164706);
			break;
		case PURPLE:
			glColor3f(0.73, 0.16, 0.96);
			break;
		case ORANGE:
			glColor3f(0.0, 0.5, 0.0);
			break;
		case BLUE:
			glColor3f(0.0, 0.0, 1.0);
			break;
		case RED:
			glColor3f(1.0,0.0,0.0);
			break;
		case GOLD:
			glColor3f(0.8,0.498039,0.196078);
			break;
		case NAVY:
			glColor3f(0.137255,0.137255,0.556863);
			break;
		case TURQOISE:
			glColor3f(0.439216,0.858824,0.858824);
			break;
		case BORDEAUX:
			glColor3f(0.858824,0.439216,0.576471);
			break;
		case CORAL:
			glColor3f(1.0,0.498039,0.0);
			break;
		case GREENYELLOW:
			glColor3f(0.576471,0.858824,0.439216);
			break;
		case GREY:
			glColor3f(0.90 ,0.90 ,0.90);
			break;
	}
}

void vertex(int x, int y)
{
	if(y>50)
	{
		if(X==NULL)
		{
			X=(int **)realloc(NULL,sizeof(int *));
			if(X==NULL) 
				exit(0);
			
			Y=(int **)realloc(NULL,sizeof(int *));
			
			numSize=(int *)realloc(NULL,sizeof(int ));
			color=(int *)realloc(NULL,sizeof(int ));
					color2=(int *)realloc(NULL,sizeof(int ));
			if(Y==NULL) 
				exit(0);
			
			X[0]=(int *)realloc(NULL,sizeof(int ));
			Y[0]=(int *)realloc(NULL,sizeof(int ));
			color[0]=lineColor;
			color2[0]=backgroundColor;
	
			if(X[0]==NULL) 
				exit(0);
			if(Y[0]==NULL) 
				exit(0);
	
			X[0][0]=x;
			Y[0][0]=y;
			size=0;
			size2=1;
			numSize[0]=1;
		}
		else if(X!=NULL && size2>-1)
		{
	
			X[size]=(int *)realloc(X[size],(size2+1)*sizeof(int ));
			if(X[size]==NULL)
				exit(0);
	
			Y[size]=(int *)realloc(Y[size],(size2+1)*sizeof(int ));
			if(Y[size]==NULL)
				exit(0);
	
			X[size][size2]=x;
			Y[size][size2]=y;
			size2++;
			numSize[size]=size2;
		}
		else{
	
			X=(int **)realloc(X,(size+2)*sizeof(int *));
			if(X==NULL)
				exit(0);
	
			Y=(int **)realloc(Y,(size+2)*sizeof(int *));
	
			if(Y==NULL)
				exit(0);
			numSize=(int *)realloc(numSize,(size+2)*sizeof(int ));
			color=(int *)realloc(color,(size+2)*sizeof(int ));
					color2=(int *)realloc(color2,(size+2)*sizeof(int ));
			if(Y==NULL)
				exit(0);
			size++;
			size2=0;
			X[size]=(int *)malloc(sizeof(int ));
			Y[size]=(int *)malloc(sizeof(int ));
	
			if(X[size]==NULL) 
				exit(0);
			if(Y[size]==NULL) 
				exit(0);
			X[size][size2]=x;
			Y[size][size2]=y;
	
			size2++;
			numSize[size]=size2;
			color[size]=lineColor;
			color2[size]=backgroundColor;
		}
		display();
	}
}

void drawLineSegment (int x1, int y1, int x2, int y2)
{		
	glBegin (GL_LINES);
	glVertex2f (-5+x1*10/600.0, 5-y1*0.02);
	glVertex2f (-5+x2*10/600.0, 5-y2*0.02);
	glEnd ( );
}

/////////////////////////////////////////////// shapes //////////////////////////////////////////////////////////

void shapes()
{
	int i,j;

	if(X!=NULL){
		for(i=0;i<=size;i++)
		{
			setcolor(color[i]);
			for(j=0;j<numSize[i]-1;j++)
			{
				drawLineSegment (X[i][j],Y[i][j],X[i][j+1],Y[i][j+1]);
			}
		}
	}
}

void mouseclick(int x, int y)
{
	if((state==draw))
	{
		if(flag==1)
		{
			vertex(x,y);
			display();
		}
	}

	if(menu==1 && (x>=0) && (x<=150))
	{
		if((y>=116) && (y<=150))
		{
			exit(0);
		}
		else if((y>=81) && (y<=116))
		{
			state=move;
			menu=0;
			numOfRule=-1;
			movement=0;
		}
		else if((y>=51) && (y<=80))
		{
			state=draw;
			shapes();
			menu=0;
			numOfRule=-1;
		}
	}
	if(menu==1 && (x<200) && (x>=150))
	{
		if((y>0)&&(y<=447))
		{
			if((y>=51) && (y<=71))
			{
				state=draw;	
				changeLineColor(PINK);
			}
			else if((y>=72) && (y<=100))
			{
				state=draw;
				changeLineColor(RED);
			}
			if((y>=102) && (y<=125))
			{
				state=draw;
				changeLineColor(BLUE);				
			}
			else if((y>=127) && (y<=150))
			{
				state=draw;
				changeLineColor(YELLOW);
			}
			else if((y>=152) && (y<=175))
			{
				state=draw;
				changeLineColor(GREY);
			}
			else if((y>=176) && (y<=200))
			{
				state=draw;
				changeLineColor(GREEN);		
			}
			else if((y>=201) && (y<=228))
			{
				state=draw;
				changeLineColor(ORANGE);			
			}
			else if((y>=229) && (y<=250))
			{
				state=draw;
				changeLineColor(PURPLE);	
			}
			else if((y>=251) && (y<=280))
			{
				state=draw;
				changeLineColor(GOLD);
			}
			else if((y>=282) && (y<=305))
			{
				state=draw;
				changeLineColor(BLACK);
			}
			else if((y>=305) && (y<=330))
			{
				state=draw;
				changeLineColor(TURQOISE);
			}
			else if((y>=330) && (y<=352))
			{
				state=draw;
				changeLineColor(BORDEAUX);
			}
			else if((y>=352) && (y<=381))
			{
				state=draw;
				changeLineColor(CORAL);
			}
			else if((y>=382) && (y<=405))
			{
				state=draw;
				changeLineColor(BROWN);
			}
			else if((y>=407) && (y<=427))
			{
				state=draw;
				changeLineColor(GREENYELLOW);
			}
			else if((y>=428) && (y<=446))
			{
				state=draw;
				changeLineColor(NAVY);
			}
		}
		menu=0;
		numOfRule=-1;
	}
	if(menu==1 && (x<350) && (x>=200))
	{
		menu=0;
		if((y>0)&&(y<=447))
		{
			if((y>=51) && (y<=71))
			{
				state=draw;	
				changeBackgroundColor(PINK);
			}
			else if((y>=72) && (y<=100))
			{
				state=draw;
				changeBackgroundColor(RED);
			}
			if((y>=102) && (y<=125))
			{
				state=draw;
				changeBackgroundColor(BLUE);				
			}
			else if((y>=127) && (y<=150))
			{
				state=draw;
				changeBackgroundColor(YELLOW);
			}
			else if((y>=152) && (y<=175))
			{
				state=draw;
				changeBackgroundColor(GREY);
			}
			else if((y>=176) && (y<=200))
			{
				state=draw;
				changeBackgroundColor(GREEN);		
			}
			else if((y>=201) && (y<=228))
			{
				state=draw;						
				changeBackgroundColor(ORANGE);					
			}
			else if((y>=229) && (y<=250))
			{
				state=draw;
				changeBackgroundColor(PURPLE);
			}
			else if((y>=251) && (y<=280))
			{
				state=draw;					
				changeBackgroundColor(GOLD);		
			}
			else if((y>=282) && (y<=305))
			{
				state=draw;
				changeBackgroundColor(BLACK);
			}
			else if((y>=305) && (y<=330))
			{
				state=draw;
				changeBackgroundColor(TURQOISE);
			}
			else if((y>=330) && (y<=352))
			{
				state=draw;
				changeBackgroundColor(BORDEAUX);		
			}
			else if((y>=352) && (y<=381))
			{
				state=draw;
				changeBackgroundColor(CORAL);
			}
			else if((y>=382) && (y<=405))
			{
				state=draw;
				changeBackgroundColor(BROWN);		
			}
			else if((y>=407) && (y<=427))
			{
				state=draw;
				changeBackgroundColor(GREENYELLOW);
	
			}
			else if((y>=428) && (y<=446))
			{
				state=draw;
				changeBackgroundColor(NAVY);
			}
		}
		menu=0;
		numOfRule=-1;
	}
	if(menu==1 && (x<500) && (x>=350))
	{
		menu=1;
		if((y>0)&&(y<=150))
		{
			if((y>=51) && (y<=71))
			{	
				numOfRule=1;
			}
			else if((y>=72) && (y<=100))
			{
				numOfRule=2;
			}
			if((y>=102) && (y<=125))
			{
				numOfRule=3;			
			}
			else if((y>=127) && (y<=150))
			{
				numOfRule=4;
			}	
			display();
		}
	}
}
	 
/*****************************************************************************/
void polygon()
{
	state=draw;
}

void buttonmove (GLint button, GLint action, GLint xMouse, GLint yMouse)
{

	int x1, x2, y1, y2;
	if (button==GLUT_LEFT_BUTTON && action==GLUT_DOWN )
	{
		mouseclick( xMouse, yMouse);	
	}
	if (button==GLUT_RIGHT_BUTTON && action==GLUT_DOWN && state==draw)
	{
		mouseclick( X[size][0], Y[size][0]);
		state=-1;
		size2=-1;
		menu=1;
		lineColor=BLACK;
		backgroundColor=WHITE;
		display();
	}
	if(menu==0 && button==GLUT_LEFT_BUTTON && action==GLUT_DOWN && state!=draw && state==move)
	{
		mouseclick(xMouse, yMouse);
		if(X!=NULL)
			findsquare(xMouse, yMouse);
	}
	else if(button==GLUT_LEFT_BUTTON && action==GLUT_UP && state!=draw && state==move && movement==1)
	{
		mouseclick(xMouse,yMouse);
		X[A][B]=xMouse;
		Y[A][B]=yMouse;
		
		if(B==numSize[A]-1)
		{
			X[A][0]=xMouse;
			Y[A][0]=yMouse;
		}
		state=-1;
		movement=0;
		menu=1;
		A=-1;
		B=-1;
		glutPostRedisplay();
	}
}

void action()
{
	in_action=1;
	flag=1;
	glColor3f(0.90 ,0.90 ,0.90);	//Change the object colors to green
	glBegin(GL_QUADS);		//Start drawing quads
	glVertex2f(-5,4);		//first coordinate
	glVertex2f(-5,2);		//second coordinate
	glVertex2f(-2.5,2);		//third coordinate (now blue)
	glVertex2f(-2.5,4);
	glEnd();

	glLineWidth(1); 
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
    	glVertex2f(-5,4);
    	glVertex2f(-5,2);

    	glBegin(GL_LINES);
    	glVertex2f(-5,2);
    	glVertex2f(-2.5,2);

    	glBegin(GL_LINES);
    	glVertex2f(-2.5,4);
    	glVertex2f(-2.5,2);
    	glEnd(); 

	glColor3f(0,0,0);
	glRasterPos2f(-4.5,2.23);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');

	glColor3f(0,0,0);
	glRasterPos2f(-4.5,3.57);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');

	glColor3f(0,0,0);
	glRasterPos2f(-4.5,2.91);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'M');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'v');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);	//Clear the screen
	glColor3f(0.95 ,0.95 ,0.95);    //Change the object colors to green
	if(numOfRule!=-1)
	{
		fill(numOfRule);
	}
	
	glBegin(GL_QUADS);		//Start drawing quads
	glVertex2f(-5,5);		//first coordinate
	glVertex2f(-5,4);		//second coordinate
	glVertex2f(-2.5,4);		//third coordinate 
	glVertex2f(-2.5,5);		//last coordinate
	glEnd();                        //Stop drawing quads
	
    	glLineWidth(1); 
    	glColor3f(0.0, 0.0, 0.0);
   	glBegin(GL_LINES);
    	glVertex2f(-5, 5);
    	glVertex2f(-2.5, 5);

    	glBegin(GL_LINES);
    	glVertex2f(-5, 4);
    	glVertex2f(-2.5, 4);

    	glBegin(GL_LINES);
    	glVertex2f(-5, 5);
    	glVertex2f(-5, 4);

    	glBegin(GL_LINES);
    	glVertex2f(-2.5, 5);
    	glVertex2f(-2.5, 4);
    	glEnd();

    	glColor3f(0,0,0);
	glRasterPos2f(-4.5,4.3);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');

	glColor3f(0.95 ,0.95 ,0.95);    //Change the object colors to green
	glBegin(GL_QUADS);		//Start drawing quads
	glVertex2f(-2.5,5);		//first coordinate
	glVertex2f(0,5);		//second coordinate
	glVertex2f(0,4);		//third coordinate 
	glVertex2f(-2.5,4);		//last coordinate
	glEnd();                        //Stop drawing quads
	
    	glLineWidth(1); 
    	glColor3f(0.0, 0.0, 0.0);
    	glBegin(GL_LINES);
    	glVertex2f(-2.5, 5);
    	glVertex2f(0, 5);

    	glBegin(GL_LINES);
    	glVertex2f(0, 5);
    	glVertex2f(0, 4);

    	glBegin(GL_LINES);
    	glVertex2f(0, 4);
    	glVertex2f(-2.5, 4);

    	glBegin(GL_LINES);
    	glVertex2f(-2.5, 4);
    	glVertex2f(-2.5, 5);
    	glEnd();

    	glColor3f(0,0,0);
	glRasterPos2f(-2.5,4.3);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');	
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');

	glColor3f(0.95 ,0.95 ,0.95);    //Change the object colors to green
	glBegin(GL_QUADS);		//Start drawing quads
	glVertex2f(0,5);		//first coordinate
	glVertex2f(2.5,5);		//second coordinate
	glVertex2f(2.5,4);		//third coordinate (now blue)
	glVertex2f(0,4);		//last coordinate
	glEnd();                        //Stop drawing quads

    	glLineWidth(1); 
    	glColor3f(0.0, 0.0, 0.0);
    	glBegin(GL_LINES);
    	glVertex2f(0, 5);
    	glVertex2f(2.5, 5);

    	glBegin(GL_LINES);
    	glVertex2f(2.5, 5);
    	glVertex2f(2.5, 4);

    	glBegin(GL_LINES);
    	glVertex2f(2.5, 4);
    	glVertex2f(0, 4);

    	glBegin(GL_LINES);
    	glVertex2f(0, 4);
    	glVertex2f(0, 5);
    	glEnd();

    	glColor3f(0,0,0);
	glRasterPos2f(0,4.3);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'F');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');	
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');

	glColor3f(0.95 ,0.95 ,0.95);    //Change the object colors to green
	glBegin(GL_QUADS);		//Start drawing quads
	glVertex2f(2.5,5);		//first coordinate
	glVertex2f(5,5);		//second coordinate
	glVertex2f(5,4);		//third coordinate
	glVertex2f(2.5,4);		//last coordinate
	glEnd();                        //Stop drawing quads
	
    	glLineWidth(1); 
    	glColor3f(0.0, 0.0, 0.0);
    	glBegin(GL_LINES);
    	glVertex2f(2.5, 5);
    	glVertex2f(5, 5);

    	glBegin(GL_LINES);
    	glVertex2f(5, 5);
    	glVertex2f(5, 4);

    	glBegin(GL_LINES);
    	glVertex2f(5, 4);
    	glVertex2f(2.5, 4);

    	glBegin(GL_LINES);
    	glVertex2f(2.5, 4);
    	glVertex2f(2.5, 5);
    	glEnd();
	
    	glColor3f(0,0,0);
	glRasterPos2f(3,4.3);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'U');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');

	shapes();
	move1();
	glFlush();	
}



void line_color()
{
	glColor3f(0.90 ,0.90 ,0.90);	//Change the object colors to green
	glBegin(GL_QUADS);		//Start drawing quads
	glVertex2f(-2.5,4);		//first coordinate
	glVertex2f(0,4);		//second coordinate
	glVertex2f(0,-4);		//third coordinate 
	glVertex2f(-2.5,-4);
	glEnd();

	glLineWidth(1); 
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
    	glVertex2f(-2.5,4);
    	glVertex2f(-2.5,-4);

    	glBegin(GL_LINES);
    	glVertex2f(0,4);
    	glVertex2f(0,-4);

    	glBegin(GL_LINES);
    	glVertex2f(0,-4);
    	glVertex2f(-2.5,-4);
    	glEnd(); 

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,3.57);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'k');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,3.07);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'd');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,2.57);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	
	glColor3f(0,0,0);
	glRasterPos2f(-2.5,2.07);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'w');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,1.57);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,1.07);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,0.57);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,0.07);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'p');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,-0.47);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'h');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,-1.00);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'k');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,-1.47);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'q');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,-2.00);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'd');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,-2.47);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'h');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,-3.00);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'w');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,-3.47);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'h');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');

	glColor3f(0,0,0);
	glRasterPos2f(-2.5,-3.89);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'm');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');	
	
	glFlush();	
}

void fill_color()
{

	glColor3f(0.90 ,0.90 ,0.90);	//Change the object colors to green
	glBegin(GL_QUADS);		//Start drawing quads
	glVertex2f(0,4);		//first coordinate
	glVertex2f(2.5,4);		//second coordinate
	glVertex2f(2.5,-4);		//third coordinate
	glVertex2f(0,-4);
	glEnd();

	glLineWidth(1); 
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
    	glVertex2f(0,4);
    	glVertex2f(2.5,4);

    	glBegin(GL_LINES);
    	glVertex2f(2.5,4);
    	glVertex2f(2.5,-4);

    	glBegin(GL_LINES);
    	glVertex2f(2.5,-4);
    	glVertex2f(0,-4);
    	glEnd(); 

	glColor3f(0,0,0);
	glRasterPos2f(0,3.57);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'k');

	glColor3f(0,0,0);
	glRasterPos2f(0,3.07);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'd');

	glColor3f(0,0,0);
	glRasterPos2f(0,2.57);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	
	glColor3f(0,0,0);
	glRasterPos2f(0,2.07);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'w');

	glColor3f(0,0,0);
	glRasterPos2f(0,1.57);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');

	glColor3f(0,0,0);
	glRasterPos2f(0,1.07);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');

	glColor3f(0,0,0);
	glRasterPos2f(0,0.57);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');

	glColor3f(0,0,0);
	glRasterPos2f(0,0.07);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'p');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');

	glColor3f(0,0,0);
	glRasterPos2f(0,-0.47);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'h');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');


	glColor3f(0,0,0);
	glRasterPos2f(0,-1.00);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'k');

	glColor3f(0,0,0);
	glRasterPos2f(0,-1.47);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'q');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');

	glColor3f(0,0,0);
	glRasterPos2f(0,-2.00);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'd');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');

	glColor3f(0,0,0);
	glRasterPos2f(0,-2.47);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'h');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');

	glColor3f(0,0,0);
	glRasterPos2f(0,-3.00);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'w');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');

	glColor3f(0,0,0);
	glRasterPos2f(0,-3.47);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'h');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');

	glColor3f(0,0,0);
	glRasterPos2f(0,-3.89);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'm');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	
	glFlush();	
}

void rules(){

	glColor3f(0.90 ,0.90 ,0.90);				//Change the object colors to green
	glBegin(GL_QUADS);					//Start drawing quads
	glVertex2f(-2.5,4);					//first coordinate
	glVertex2f(0,4);					//second coordinate
	glVertex2f(0,-4);					//third coordinate
	glVertex2f(-2.5,-4);
	glEnd();

	glLineWidth(1); 
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
    	glVertex2f(-2.5,4);
    	glVertex2f(-2.5,-4);

    	glBegin(GL_LINES);
    	glVertex2f(0,4);
    	glVertex2f(0,-4);

    	glBegin(GL_LINES);
    	glVertex2f(0,-4);
    	glVertex2f(2.5,-4);
    	glEnd(); 

	glColor3f(0,0,0);
	glRasterPos2f(2.5,3.57);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
	glColor3f(0,0,0);
	glRasterPos2f(2.5,3.07);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');

	glColor3f(0,0,0);
	glRasterPos2f(2.5,2.57);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '3');
	
	glColor3f(0,0,0);
	glRasterPos2f(2.5,2.07);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '4');

	glFlush();	
}
	

void mouse( int x, int y) 
{	
	if(menu == 1)
	{
		if((x<150) && (x>0))
	  	{
			if((y<50) && (y>0))
		  	{	
				action();
			}
		}
		else if((x<300) && (x>150)) 
    		{
    			if((y<50) && (y>0))
		  	{
				line_color();
			}
		}
		else if((x<450) && (x>300))
	  	{
			if ((y>0) && (y<50))
		  	{
				fill_color();
        		}
        	}
      		else if((x<600) && (x>450))
	  	{
			if ((y>0) && (y<50))
		  	{
				rules();
			}
        	}	
	}
}


void init()
{
	glClearColor(1,1,1,1);					//Define our background color
	gluOrtho2D(-5,5,-5,5);					//(NEW) Define our viewing area
	
}

int main(int argc, char ** argv)
{
	printf("Welcome to the polygon game, enjoy! \n");
	
	glutInit(&argc, argv);					//Initialize GLUT
	glutInitWindowSize(600,500);				//define the window size
	glutInitWindowPosition(10,50);				//Position the window
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);		//Define the drawing mode
	glutCreateWindow("Shapes");				//Create our window	
	init();							//initialize our variables
	glutDisplayFunc(display);				//tell Glut what our display function is
	glutMotionFunc(mouseclick);
	glutMouseFunc(buttonmove);
	glutPassiveMotionFunc(mouse);
	glutMainLoop();
}
