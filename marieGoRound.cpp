#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "camera.h"

#include<GL/glut.h>

#define BLACK 0, 0, 0
#define WHITE 1, 1, 1
#define pi 3.1416

//make a global variable -- for tracking the anglular position of camera
double cameraAngle;			//in radian
double cameraAngleDelta;

double cameraHeight;	
double cameraRadius;
double cameraRadiusY;

double rectAngle;	//in degree
double ro=10,tag=1,po=37,loG,ro1,tag1,po1;
double pitch,yaw,roll;
int f;

bool canDrawGrid;
Point3 abc,def;
Vector3 vec;
Camera cm;
int flag=0;


void tube(GLfloat radius, GLfloat segment_length) {
    glPolygonMode(GL_BACK, GL_NONE);
    glPolygonMode(GL_FRONT, GL_FILL);

    glPushMatrix(); {
        GLfloat z1 = 0.0;
        GLfloat z2 = segment_length;

        GLfloat y_offset = 0.0;
        GLfloat y_change = 0.00;

        int i = 0;
        int j = 0;
        for (j = 0; j < 20; j++) {
            glPushMatrix(); {
                glBegin(GL_TRIANGLE_STRIP); {
                    for (i = 360; i >= 0; i--) {
                        GLfloat theta = i * pi/180;
                        GLfloat x = radius * cos(theta);
                        GLfloat y = radius * sin(theta) + y_offset;

                        glVertex3f(x, y, z1);
                        glVertex3f(x, y, z2);
                    }
                } glEnd();
            } glPopMatrix();

            // attach the front of the next segment to the back of the previous
            z1 = z2;
            z2 += segment_length;

            // make some other adjustments
            y_offset += y_change;
        }
    } glPopMatrix();
}






void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BLACK, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();


	//instead of CONSTANT information, we will define a circular path.
//	gluLookAt(-30,-30,50,	0,0,0,	0,0,1);

	//gluLookAt(cameraRadius, cameraRadiusY, cameraHeight,		0,0,0,		0,0,1);
	//NOTE: the camera still CONSTANTLY looks at the center
	// cameraAngle is in RADIAN, since you are using inside COS and SIN
	
	if(flag==0)
	{
	abc.set(cameraRadius, cameraRadiusY, cameraHeight);
	def.set(0,0,0);
	vec.set(0,0,1);
	cm.set(abc,def,vec);
	}
	if(flag==4)cm.roll(2);
	if(flag==7)cm.roll(-2);
	
	if(flag==5)cm.pitch(2);
	if(flag==8)cm.pitch(-2);
	
	if(flag==6)cm.yaw(2);
	if(flag==9)cm.yaw(-2);
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

/* turn on default lighting */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
	/****************************
	/ Add your objects from here
	****************************/
	//add objects
	//rotate this rectangle around the Z axis
/*
	glPushMatrix();{	//STORE the state
		glRotatef(rectAngle,	0,0,1);	// in DEGREE
		//a simple rectangles
		glColor3f(0.3, 0.4, 0.8);
		glBegin(GL_QUADS);{
			glVertex3f(0,0,30);
			glVertex3f(10,0,30);
			glVertex3f(10,20,30);
			glVertex3f(0,20,30);
		}glEnd();

		///lets draw another one in the XY plane --- i.e. Z = 0
		glColor3f(0.15, 0.2, 0.4);
		glBegin(GL_QUADS);{
			glVertex3f(0,0,0);
			glVertex3f(10,0,0);
			glVertex3f(10,20,0);
			glVertex3f(0,20,0);
		}glEnd();
	}glPopMatrix();		//the effect of rotation is not there now.
*/
	//some gridlines along the field
	int i;

	//WILL draw grid IF the "canDrawGrid" is true:



glRotatef( pitch, 1.0f, 0.0f, 0.0f );
glRotatef( yaw, 0.0f, 1.0f, 0.0f );
glRotatef( roll, 0.0f, 0.0f, 1.0f ); 
glPushMatrix();{

	if(canDrawGrid == true){
		glColor3f(0.3, 0.3, 0.3);	//grey
		glBegin(GL_LINES);{
			for(i=-10;i<=10;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -100, 0);
				glVertex3f(i*10,  100, 0);

				//lines parallel to X-axis
				glVertex3f(-100, i*10, 0);
				glVertex3f( 100, i*10, 0);
			}
		}glEnd();
	}

	// draw the two AXES
	glColor3f(1, 1, 1);	//100% white
	glBegin(GL_LINES);{
		//Y axis
		glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
		glVertex3f(0,  150, 0);

		//X axis
		glVertex3f(-150, 0, 0);
		glVertex3f( 150, 0, 0);
	}glEnd();


  
glTranslatef(0.0,0.0,40);
glPushMatrix();{

glPushMatrix();{
glTranslatef(0.0,0.0,90);
glPushMatrix();{
//lower cone portion                
 glColor3f(.5,0.0,0.0);	//blue                 
 GLUquadricObj *quadratic;
  quadratic = gluNewQuadric();
  glTranslatef(0,0,-130);
  gluCylinder(quadratic,105.0f,15.0f,150.0f,32,32);
}glPopMatrix();
//////////////////////////////



//////////////////takku bel matha///////////////////////////////

glPushMatrix();{
 glColor3f(0.0,0.5,0.0);	//blue
 glTranslatef(0,0,80);
 GLUquadricObj *quadratic1;
 quadratic1 = gluNewQuadric();
 //gluCylinder(quadratic1,30.0f,30.0f,20.0f,32,32);
 //gluDisk(quadratic1,0.0f,30.0f,50,50);
 gluDisk(quadratic1,0.0f,43.0f,50,50);
}glPopMatrix();

glPushMatrix();{
 glColor3f(0.0,0.5,0.0);	//blue
 glTranslatef(0,0,60);
 GLUquadricObj *quadratic1;
 quadratic1 = gluNewQuadric();
 gluCylinder(quadratic1,43.0f,43.0f,20.0f,32,32);
 gluDisk(quadratic1,0.0f,43.0f,50,50);
// gluDisk(quadratic1,0.0f,40.0f,50,50);
}glPopMatrix();

glPushMatrix();{
 glColor3f(0.0,0.5,0.0);	//blue
 glTranslatef(0,0,80);
 GLUquadricObj *quadratic1;
 quadratic1 = gluNewQuadric();
 gluCylinder(quadratic1,25.0f,32.0f,20.0f,32,32);
 //gluDisk(quadratic1,0.0f,40.0f,50,50);
 //gluDisk(quadratic1,0.0f,40.0f,50,50);
}glPopMatrix();


glPushMatrix();{
 glColor3f(0.0,0.5,0.0);	//blue
 glTranslatef(0,0,110);
 GLUquadricObj *quadratic1;
 quadratic1 = gluNewQuadric();
 //gluCylinder(quadratic1,40.0f,40.0f,20.0f,32,32);
 //gluDisk(quadratic1,0.0f,40.0f,50,50);
 //gluDisk(quadratic1,0.0f,40.0f,50,50);
 glutSolidSphere(33.0f,100,100);
}glPopMatrix();

//////////////////////////////////////////////////////////////////////

/////////mathar uporer sing////////////////////////////////////////////
for(int i=0;i<=4;i++)
{
       glRotatef(90.0f*i, 0.0f, 0.0f, 1.0f);
       glPushMatrix();{
            glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
            glTranslatef(117,-20,0);
            // dandi toirir jonno torus crop  
            glPushMatrix();{     
            glTranslatef(2,-101,0);
            double equ1[4];
            
            	equ1[0] = 1;	//1.x
            	equ1[1] = 1;	//0.y
            	equ1[2] = 0;//0.z
            	equ1[3] = -56;//0
            
            	glClipPlane(GL_CLIP_PLANE1,equ1);
            
            	//now we enable the clip plane
                
            	glEnable(GL_CLIP_PLANE1);{
                    
            		glColor3f(0,0.5,0.0);	//blue
                    glPushMatrix();{
                    glutSolidTorus(5.0f, 50.0f, 10, 80);
                    }glPopMatrix();
            
            	}glDisable(GL_CLIP_PLANE1);
            }glPopMatrix();
            
            //torus akakbaka korar majhe ekta cylinder
            glPushMatrix();{
             glColor3f(0.0,0.5,0.0);	//blue
             glTranslatef(-15,-48,0);
             GLUquadricObj *quadratic;
              quadratic = gluNewQuadric();
              glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
              glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
              gluCylinder(quadratic,5.0f,5.0f,35.0f,32,32);
            }glPopMatrix();
            
            
            //dandir nicher bakano ongso
            glPushMatrix();{ 
            double equ2[4];
            
            	equ2[0] = -1;	//1.x
            	equ2[1] = -1;	//0.y
            	equ2[2] = 0;//0.z
            	equ2[3] = -56;//0
            
            	glClipPlane(GL_CLIP_PLANE2,equ2);
            
            	//now we enable the clip plane
            //glTranslatef(0,100,0);
            	glEnable(GL_CLIP_PLANE2);{
             
            		glColor3f(0,0.5,0.0);	//blue
                    glPushMatrix();{
                    glutSolidTorus(5.0f, 50.0f, 10, 80);
                    }glPopMatrix();
            
            	}glDisable(GL_CLIP_PLANE2);	
            }glPopMatrix();
     }glPopMatrix();
}
///////////////////////////////////////////////////////
























//engine portion
glPushMatrix();{
glRotatef(rectAngle,0,0,1);	// in DEGREE

glPushMatrix();{
 glColor3f(0.0,0.3,0.8);	//blue
 glTranslatef(0,0,-40);
 GLUquadricObj *quadratic;
  quadratic = gluNewQuadric();
  gluCylinder(quadratic,35.0f,35.0f,100.0f,32,32);
}glPopMatrix();
////////////////////////////////////////////////




//octopus leg portion
glPushMatrix();{
glColor3f(0.3,0.3,0.3);
for(f=0;f<4;f++)
{
glRotatef(90.0f*f, 0.0f, 0.0f, 1.0f);
glPushMatrix();{


//if(f==0||f==1) {ro=0;tag=0;}
//else if(f==2||f==3) {ro=10;tag=1;} 
/*    	
	if(f==0||f==3)
    {ro=0;}
    if(f==1||f==2)
    {ro=10;} 
*/

if(f==1||f==2)
{glRotatef(ro, 0.0f, 1.0f, 0.0f);}
if(f==0||f==3)
{glRotatef(ro1, 0.0f, 1.0f, 0.0f);}

glTranslatef(-180,0,0);
 glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
 glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
 glRotatef(90.0f, 0.0f, 0.0f, -1.0f);


//torus crop portion  
double equ[4];

	equ[0] = -1;//.x/
	equ[1] = -1;//y
	equ[2] = 0;//0.z
	equ[3] = -40;//0

	glClipPlane(GL_CLIP_PLANE0,equ);

	//now we enable the clip plane

	glEnable(GL_CLIP_PLANE0);{
//		glColor3f(0,0.3,0.8);	//blue
        glPushMatrix();{
        glutSolidTorus(10.0f, 50.0f, 10, 80);
        }glPopMatrix();
	}glDisable(GL_CLIP_PLANE0);
////////////////////////////////////////////////

//octopus leg er nicher ongso
glPushMatrix();{
// glColor3f(0.0,0.3,0.8);	//blue
 glTranslatef(-50,0,0);
 GLUquadricObj *quadratic;
  quadratic = gluNewQuadric();
  glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
  glRotatef(-2.0f, 0.0f, -1.0f, 0.0f);
  gluCylinder(quadratic,10.0f,10.0f,50.0f,32,32);
}glPopMatrix();

//octopus leg er uporer ongso
glPushMatrix();{
// glColor3f(0.0,0.3,0.8);	//blue
 glTranslatef(4,-50.3,0);
 GLUquadricObj *quadratic;
  quadratic = gluNewQuadric();
  glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
  glRotatef(-15.0f, 1.0f, 0.0f, 0.0f);
  gluCylinder(quadratic,10.0f,10.0f,180.0f,32,32);
}glPopMatrix();
}glPopMatrix();
}
}glPopMatrix();

/////////////////////////////////////////////////////////

//garir dandi//////////////////////////////
for(int k=0;k<4;k++)
{
    glRotatef(90.0f*k, 0.0f, 0.0f, 1.0f);
    
    glPushMatrix();{
    glTranslatef(230,0,-80);
    glPushMatrix();{
  //  if(k==1||k==2) po=37;
   // else po=0;
    if(k==1||k==2)
    glTranslatef(0,0,po);
    if(k==3||k==0)
    glTranslatef(0,0,po1);
    
    
    
    
    
///////////////////////////////////////octopus leg er nicher cakti/////////////////    
glPushMatrix();{
glColor3f(0.8,0.0,0.0);                
glRotatef(180.0f,1.0f,0.0f,0.0f);
glTranslatef(0,0,-40);
glPushMatrix();{
 //glColor3f(0.3,0.3,0.3);	//blue
 glTranslatef(0,0,0);
 GLUquadricObj *quadratic1;
 quadratic1 = gluNewQuadric();
 //gluCylinder(quadratic1,30.0f,30.0f,20.0f,32,32);
 //gluDisk(quadratic1,0.0f,30.0f,50,50);
 gluDisk(quadratic1,0.0f,40.0f,50,50);
}glPopMatrix();

glPushMatrix();{
 //glColor3f(0.3,0.3,0.3);	//blue
 
 GLUquadricObj *quadratic1;
 quadratic1 = gluNewQuadric();
 gluCylinder(quadratic1,40.0f,40.0f,10.0f,32,32);
glPushMatrix();{
 glTranslatef(0,0,10);
 gluDisk(quadratic1,0.0f,40.0f,50,50);
}glPopMatrix();
// gluDisk(quadratic1,0.0f,40.0f,50,50);
}glPopMatrix();
}glPopMatrix();
/////////////////////////////////////////////////////////////////////////////
    
    
    
    glScalef(0.7,0.7,0.7);
        
        for(int i=0;i<=4;i++)
        {
            glRotatef(90.0f*i, 0.0f, 0.0f, 1.0f);
            glPushMatrix();{
            glRotatef(loG,0,0,-1);
            glPushMatrix();{
//carrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr                
 /*               glPushMatrix();{ 
                        glTranslatef(0,-100,-50);
                    	glColor3f(0,0.3,0.8);	//blue
                        glPushMatrix();{
                        glutSolidCube(60.0f);
                        }glPopMatrix();	
                }glPopMatrix();
                
   */             
////////////CAAAAAR
 glPushMatrix();{ 
                        glTranslatef(0,-130,-35);
                    	glColor3f(0.2,0.2,0.0);	//yello
glPushMatrix();{
                
                glRotatef(180,0,1,0);
                glRotatef(90,0,0,1);
                glTranslatef(0,0,-60);
     double equ3[4];
            
            	equ3[0] = 0;	//1.x
            	equ3[1] = -3;	//0.y
            	equ3[2] = 1;//0.z
            	equ3[3] = 130;//0
            
            	glClipPlane(GL_CLIP_PLANE1,equ3);
            
            	//now we enable the clip plane
            	
                glEnable(GL_CLIP_PLANE1);{
                    
            		//glColor3f(0.0,0.5,0.0);	//blue
                    
                glPushMatrix();{ 
                    glPushMatrix();{
                    glTranslatef(0,0,51);
                   // glColor3f(0,0.3,0.);
                    glScalef(1.3,2.0,0.3);
                    glutSolidCube(60.0f);
                    }glPopMatrix();	
                    
                    glPushMatrix();{
                    glTranslatef(0,-54,30);
                   // glColor3f(0.3,0.3,0.3);
                    glScalef(0.8,0.2,1.0);
                    glutSolidCube(60.0f);
                    }glPopMatrix();	
                    
                    glPushMatrix();{
                    glRotatef(-17.5,1,0,0);
                    glTranslatef(0,35,38);
                   // glColor3f(0.3,0.3,0.3);
                    glScalef(1.28,0.2,1.0);
                    glutSolidCube(60.0);
                    }glPopMatrix();	
                    
                    
                    glPushMatrix();{
                    glTranslatef(-30,0,30);
                   // glColor3f(0.3,0.3,0.3);
                    glScalef(0.3,2.0,1.0);
                    glutSolidCube(60.0f);
                    }glPopMatrix();	
                
                    glPushMatrix();{
                    glTranslatef(30,-39,30);
                   // glColor3f(0.3,1.0,0.3);
                    glScalef(0.3,0.7,1.0);
                    glutSolidCube(60.0f);
                    }glPopMatrix();	
                
                    glPushMatrix();{
                    glTranslatef(30,39,30);
                   // glColor3f(0.3,1.0,0.3);
                    glScalef(0.3,0.7,1.0);
                    glutSolidCube(60.0f);
                    }glPopMatrix();	
                }glPopMatrix();
                }glDisable(GL_CLIP_PLANE1);
               // glRotatef(180,1,0,0);
               // glTranslatef(0,0,150);
   }glPopMatrix();
}glPopMatrix();
                
/////////////CARRRRRRRRRRRRRRRRRRRRRRRR/////////////            
            
            
             glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
             //glRotatef(00.0f, 1.0f, 0.0f, 0.0f);
              glRotatef(15.0f, 0.0f, 0.0f, -1.0f);
              
              
            // dandi toirir jonno torus crop  
            glPushMatrix();{     
            glTranslatef(2,-101,0);
            double equ1[4];
            
            	equ1[0] = 1;	//1.x
            	equ1[1] = 1;	//0.y
            	equ1[2] = 0;//0.z
            	equ1[3] = -56;//0
            
            	glClipPlane(GL_CLIP_PLANE1,equ1);
            
            	//now we enable the clip plane
                
            	glEnable(GL_CLIP_PLANE1);{
                    
            		glColor3f(0,0.5,0.75);	//akashi
                    glPushMatrix();{
                    glutSolidTorus(5.0f, 50.0f, 10, 80);
                    }glPopMatrix();
            
            	}glDisable(GL_CLIP_PLANE1);
            }glPopMatrix();
            
            //torus akakbaka korar majhe ekta cylinder
            glPushMatrix();{
             glColor3f(0,0.5,0.75);	//blue
             glTranslatef(-15,-48,0);
             GLUquadricObj *quadratic;
              quadratic = gluNewQuadric();
              glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
              glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
              gluCylinder(quadratic,5.0f,5.0f,35.0f,32,32);
            }glPopMatrix();
            
            
            //dandir nicher bakano ongso
            glPushMatrix();{ 
            double equ2[4];
            
            	equ2[0] = -1;	//1.x
            	equ2[1] = -1;	//0.y
            	equ2[2] = 0;//0.z
            	equ2[3] = -56;//0
            
            	glClipPlane(GL_CLIP_PLANE2,equ2);
            
            	//now we enable the clip plane
            //glTranslatef(0,100,0);
            	glEnable(GL_CLIP_PLANE2);{
             
            		glColor3f(0,0.5,0.75);	//blue
                    glPushMatrix();{
                    glutSolidTorus(5.0f, 50.0f, 10, 80);
                    }glPopMatrix();
            
            	}glDisable(GL_CLIP_PLANE2);	
            }glPopMatrix();
///////////////////////////////////////////////////////
            }glPopMatrix();
            }glPopMatrix();
         }
    }glPopMatrix();
    }glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////

}glPopMatrix();
}glPopMatrix();
}glPopMatrix();
}glPopMatrix();

                
	//////// ------ NOTE ---- ORDER matters. compare last two spheres!

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

int a;


void animate(){
	//codes for any changes in Camera
if(a==1)
{
	cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.	// keep the camera steady NOW!!

	//codes for any changes in Models
	
	rectAngle -= 1;
	loG-=3;
		
	
	if(ro1<=10 && tag1==0)
	{
    ro1+=1;
    po1+=3.7;
    if(ro1==10){tag1=1;}
    }   
	else if(ro1>=0 && tag1==1)
	{
         ro1-=1;
         po1-=3.7;
         if(ro1==0){tag1=0;}
    }
    
    
    if(ro>=0 && tag==1)
	{
         ro-=1;
         po-=3.7;
         if(ro==0){tag=0;}
    }
    else if(ro<=10 && tag==0)
	{
    ro+=1;
    po+=3.7;
    if(ro==10){tag=1;}
    }
}
	//else 

/*
    if(tag==0)
	{
    ro+=1;
    po+=3.7;
    if(ro==10){tag=1;}
    }   
	else if(tag==1)
	{
         ro-=1;
         po-=3.7;
         if(ro==0){tag=0;}
    }
*/

	//MISSING SOMETHING? -- YES: add the following
	glutPostRedisplay();	//this will call the display AGAIN
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':	//reverse the rotation of camera
//			cameraAngleDelta = -cameraAngleDelta;
			break;

		case '2':	//increase rotation of camera by 10%
			cameraAngleDelta *= 1.1;
			break;

		case '3':	//decrease rotation
			cameraAngleDelta /= 1.1;
			break;
        
    //    case '4':	//decrease rotation
	//		break;
			
		case '4':
			flag=4;
			//pitch-= 10;
			//cm.pitch(2);
			break;
		case '5':
			flag=5;
			//yaw-= 10;
			//cm.yaw(2);	
			break;
        case '6':
			flag=6;
			//roll-= 10;
			//cm.roll(2);
			break;
        
        			
		case '7':
			flag=7;
			//pitch+= 10;
			//cm.pitch(-2);
			break;
		case '8':
			flag=8;
			//yaw+= 10;
			//cm.yaw(-2);
			break;
        case '9':
			flag=9;
			//roll+= 10;
			//cm.roll(2);
			break;
                        
            	
		case '0':	//toggle grids
			//canDrawGrid = 1 - canDrawGrid;
			flag=0;
			break;

		case 27:	//ESCAPE KEY -- simply exit
			exit(0);
			break;

		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraRadius += 10;
			break;
		case GLUT_KEY_UP:		// up arrow key
		//	if(cameraRadius > 10)
				cameraRadius -= 10;
			break;
		case GLUT_KEY_RIGHT:
			cameraRadiusY += 10;
            break;
		case GLUT_KEY_LEFT:
			cameraRadiusY -= 10;
            break;
		case GLUT_KEY_PAGE_UP:
			cameraHeight += 10;
			break;
		case GLUT_KEY_PAGE_DOWN:
			cameraHeight -= 10;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
             a=1;
			break;
		case GLUT_KEY_END:
             a=0;
			break;

		default:
			break;
	}
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
//				cameraAngleDelta = -cameraAngleDelta;	
			a=1;
            }
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
//				cameraAngleDelta = -cameraAngleDelta;	
			a=0;
            }
            break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}


void init(){
	//codes for initialization
	cameraAngle = 0;	//// init the cameraAngle
	cameraAngleDelta = 0.002;
	rectAngle = 0;
	canDrawGrid = true;
	cameraHeight = 270;
	cameraRadius = 520;
    cameraRadiusY = 200;
	//clear the screen
	glClearColor(WHITE, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);
	
	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(70,	1,	0.1,	10000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)


   

	//ADD keyboard listeners:
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	//ADD mouse listeners:
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
