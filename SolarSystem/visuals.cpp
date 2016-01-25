#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "gl/glut.h"   // - An interface and windows management library
#include "visuals.h"   // Header file for our OpenGL functions

model md;
static float tx = 0.0;
static float rotationX = 0.0, rotationY = 0.0;
static bool animate = false;
static float red = 1.0;
static float green = 0.0;
static float blue = 0.0;
static float angle = 0.0;
// actual vector representing the camera's direction
static float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
static bool stopRotating = true;
static float x = 0.0f, z = 60.0f;
static float transparency = 0.2;
static bool ascendingPhase = true;
using namespace std;

void keimeno(const char *str,float size)
{

	glPushMatrix();
	glScalef(size,size,size);

	for (int i=0;i<strlen(str);i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	glPopMatrix();

}
const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f ,0.0f, 17.0f, 1.0f };
void drawStar() {

//white color
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);

	glVertex3f(-10.0f, -3.0f, 0.0f);
	glVertex3f(-12.0f, -3.0f, 0.0f);
	glVertex3f(-14.0f, -3.0f, 0.0f);



glEnd();


}
void drawSolar() {

	//for light
}
void Render()
{    
	static int yPos[] = { 35,	91,	62,	56	,43,
		35,	65,	80,	12,	99,
		34,	93,	61,	83,	34,
		35,	100,	78,	61,	41,
		78,	61,	39,	4	,69,
		72,	75,	24	,1,	33,
		99,	6,	83,	49,	2,
		53,	41,	36,	34,	25,
		39,	19,	27,	32,	59,
		33,	69,	75,	65,	39,
		38,	80,	64,	69,	63,
		79,	68,	95,	28,	86,
		15,	19,	4	,51,	95,
		67,	30	,67	,30	,49,
		3,	16	,67	,27,	63,
		40	,15	,29	,4,	55,
		61	,68	,77	,61	,8
		,26	,21	,44	,69	,29
		,85	,41	,49	,17	,9,
		18	,76	,25	,53	,71 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);
	glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
	// Draw 1 Solar
			glPushMatrix();
			glRotatef(angle, 0.0f, 1.0f, 0.0f);
			glEnable(GL_LIGHT0);
			glEnable(GL_NORMALIZE);
			glEnable(GL_COLOR_MATERIAL);
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
			glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			// Draw Sun : color yellow
			glColor3f(1.0f, 1.0f, 0.0f);
			glTranslatef(0.0f, 0.75f, 0.0f);
			glutSolidSphere(3.0f, 100, 100);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(3.0f, 1.0f, 0.0f, transparency);
			if (transparency >= 1.0f)
				ascendingPhase = false;
			if(transparency <= 0)
				ascendingPhase = true;
			if (ascendingPhase)
				transparency += 0.02;
			else
				transparency -= 0.02;
			glutSolidSphere(4.0f, 100, 100);
			//Mercury :  Black Gray
			glColor3f(0.9f, 0.9f, 0.9f);
			glTranslatef(-14, 0.60, 0.0f);
			glutSolidSphere(0.75f, 60, 60);
			//Venus : drak yellow
			glColor3f(0.9f, 0.7f, 0.0f);
			glTranslatef(7, 0.0f, 4.0f);
			glutSolidSphere(0.60f, 40, 40);
			//Earth : blue
			glColor3f(0.0f, 0.5f, 1.0f);
			glTranslatef(17, 0.0f, 8.0f);
			glutSolidSphere(1.5f, 40, 40);

			glColor3f(0.6f, 0.5f, 1.0f);
			glTranslatef(5, 0.0f, 6.0f);
			glutSolidSphere(1.5f, 40, 40);

			glEnd();
			if(stopRotating)
				angle += 0.1f;
			glPopMatrix();

	// for Star
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			glPushMatrix();
			glTranslatef(i*10.0, yPos[i*j + j]/6, j * 10.0);
			drawStar();
			glPopMatrix();
		}

	glutSwapBuffers();

}

//-----------------------------------------------------------

void Resize(int w, int h)
{
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
  //// define the visible area of the window ( in pixels )
  //if (h==0) h=1;
  //glViewport(0,0,w,h); 

  //// Setup viewing volume

  //glMatrixMode(GL_PROJECTION); 
  //glLoadIdentity();
 
  //gluPerspective(60.0, (float)w/(float)h, 1.0, 500.0);
}

void Idle()
{


	glutPostRedisplay();
}

void Keyboard(int key,int x,int y)
{
	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		rotationY -= 1.0f;
		break;
	case GLUT_KEY_RIGHT:
		rotationY += 1.0f;
		break;
	case GLUT_KEY_UP:
		rotationX -= 1.0f;
		break;
	case GLUT_KEY_DOWN:
		rotationX += 1.0f;
		break;
	case GLUT_KEY_F1:
			stopRotating = !stopRotating;
			break;
	}

	glutPostRedisplay();

}

void Mouse(int button,int state,int x,int y)
{
	 if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	 {
		 animate = !animate;
         glutPostRedisplay();
	 }
}


void Setup()  // TOUCH IT !! 
{ 
	ReadFile(&md);

	//Parameter handling
	glShadeModel (GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);
    
	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] = { 0.0, 30.0, 50.0, 0.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	   
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	//01
	glFrontFace(GL_CCW);
 

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

void MenuSelect(int choice)
{
	switch (choice) {
		case RED : 
			red = 1.0; 
			green = 0.0; 
			blue = 0.0; break;
		case GREEN : 
			red = 0.0; 
			green = 1.0; 
			blue = 0.0; break;
		case BLUE : 
			red = 0.0; 
			green = 0.0; 
			blue = 1.0; break;
		case WHITE : 
			red = 1.0; 
			green = 1.0; 
			blue = 1.0; break;
	}

}

void ReadFile(model *md)
{

	ifstream obj_file("planet.obj");                   // Open the file for reading OBJINFO.TXT
   
	if (obj_file.fail()) 
		exit(1);

	obj_file >> md->vertices;                               // Get the number of vertices
	obj_file >> md->verticeNormals;
	obj_file >> md->faces;									// Get the number of faces

	for (int i = 0; i < md->vertices; i++){                        // Get the vertex coordinates
		obj_file.ignore(3);
		obj_file >> md->obj_points[i].x;
		obj_file >> md->obj_points[i].y;
		obj_file >> md->obj_points[i].z;
	
   }
	for (int i = 0; i < md->verticeNormals; i++) {                        // Get the vertex coordinates
		obj_file.ignore(3);
		obj_file >> md->obj_vertice_normals[i].x;
		obj_file >> md->obj_vertice_normals[i].y;
		obj_file >> md->obj_vertice_normals[i].z;

	}

   for (int i = 0; i < md->faces; i++){                        // Get the face structure
	   obj_file.ignore(256, ' ');
		obj_file >> md->obj_faces[i].vtx[0];
		obj_file.ignore(256, ' ');
		obj_file >> md->obj_faces[i].vtx[1];
		obj_file.ignore(256, ' ');
		obj_file >> md->obj_faces[i].vtx[2];
		obj_file.ignore(256,'\n');
   }

   obj_file.close();
}

void DisplayModel(model md)
{

	glPushMatrix();
	//glScalef(0.005, 0.005, 0.005);
	glTranslatef(0, 0, -1157);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < md.faces; i++)
	{
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[0]-1].x,md.obj_points[md.obj_faces[i].vtx[0]-1].y,md.obj_points[md.obj_faces[i].vtx[0]-1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[1]-1].x,md.obj_points[md.obj_faces[i].vtx[1]-1].y,md.obj_points[md.obj_faces[i].vtx[1]-1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[2]-1].x,md.obj_points[md.obj_faces[i].vtx[2]-1].y,md.obj_points[md.obj_faces[i].vtx[2]-1].z);
	}

	glEnd();
	angle += 0.1f;
	glPopMatrix();

}