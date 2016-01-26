#include <stdio.h>     // - Just for some ASCII messages
#include <string>
#include <math.h>
#include <iostream>
#include <fstream>
#include "gl/glut.h"   // - An interface and windows management library
#include "visuals.h"   // Header file for our OpenGL functions

model md;

static float rotationX = 0.0, rotationY = 0.0;
static bool animate = false;
static float angle = 0.0;			// Orbits		

static bool stopRotating = false;	// Paused or not
static float transparency = 0.2;	// Sun transparency
static bool ascendingPhase = true;	// Sun transparency increasing or not

using namespace std;

const GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f,  0.8f };
const GLfloat light_diffuse[] = { 0.7f, 0.7f, 0.7f, 0.8f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 0.8f };
const GLfloat light_position[] = { 0.0f ,5.0f, 0.0f, 1.0f };
const GLfloat mat_emission[] = { 0.5, 0.5, 0.0, 0.5 };

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(0.0f, 1.0f, 60.0f,
		0.0f, 1.0f, 59.0f,
		0.0f, 1.0f, 0.0f);
	glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Prepare SunLight
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	// Draw Sun : color yellow
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(3.0f, 100, 100);
	//sun
	glColor4f(3.0f, 1.0f, 0.0f, transparency);
	if (transparency >= 0.8f)
		ascendingPhase = false;
	if (transparency <= 0.2f)
		ascendingPhase = true;
	if (ascendingPhase)
		transparency += 0.01;
	else
		transparency -= 0.01;
	//the light of the sun (another sun with increasing/decreasing transparency)
	glutSolidSphere(4.0f, 100, 100);
	glPopMatrix();


	glPushMatrix();
	glRotatef(angle + 80.0f, 0.0f, 0.0f, 1.0f);
	//Mercury :  Black Gray
	glColor3f(0.2f, 0.5f, 1.0f);
	glScalef(0.003, 0.003, 0.003);
	glTranslatef(-3150.0f, 0.0f, 0.0f);
	DisplayModel(md);
	//glutSolidSphere(0.75f, 60, 60);
	glPopMatrix();

	//Venus : drak yellow
	glPushMatrix();
	glRotatef(angle + 512.0f, 0.0f, 1.0f, 0.0f);
	//Mercury :  Black Gray
	glColor3f(0.4f, 0.2f, 0.1f);
	glScalef(0.00255, 0.00255, 0.00255);
	glTranslatef(+4150.0f, 0, 0.0f);
	DisplayModel(md);
	//glutSolidSphere(0.75f, 60, 60);
	glPopMatrix();


	//Earth : blue
	glPushMatrix();
	glRotatef(angle + 15.0f, 0.0f, 1.0f, 0.0f);
	//Mercury :  Black Gray
	glColor3f(0.2f, 0.5f, 0.4f);
	glScalef(0.0035, 0.0035, 0.0035);
	glTranslatef(-7150.0f, 0, 0.0f);
	DisplayModel(md);
	//glutSolidSphere(0.75f, 60, 60);
	glPopMatrix();


	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	//Mercury :  Black Gray
	glColor3f(0.4f, 0.8f, 1.0f);
	glScalef(0.002, 0.002, 0.002);
	glTranslatef(+10150.0f, 0, 0.0f);
	DisplayModel(md);
	//glutSolidSphere(0.75f, 60, 60);
	glPopMatrix();

	glEnd();
	if (!stopRotating)
		angle += 0.5f;
	glPopMatrix();


	// For Stars
	float x, y, z;
	srand(100);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int j = 0; j < 500; j++) {
		x = rand() % 200 - 100;
		y = rand() % 200 - 100;
		z = rand() % 200 - 100;
		glPushMatrix();
		glTranslatef(x, y, z);
		glutSolidSphere(0.1f, 10, 10);
		glColor4f(1.0f, 1.0f, 1.0f, transparency + 0.3f);
		glutSolidSphere(0.05f, 10, 10);
		glPopMatrix();
	}

	glutSwapBuffers();
}

void Resize(int w, int h)
{
	if (h == 0)
		h = 1;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	float ratio = w * 1.0 / h;
	gluPerspective(60.0f, ratio, 1.0f, 800.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void Idle()
{
	glutPostRedisplay();
}

void Keyboard(int key, int x, int y)
{
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

void Setup()  // TOUCH IT !! 
{
	ReadFile(&md);

	//Parameter handling
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);

	// Enabling Light and more
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ReadFile(model *md)
{
	ifstream obj_file("planet.obj");                   // Open the file for reading planet.obj

	if (obj_file.fail())
		exit(1);

	// Get the count of vertices/faces
	char line[256];
	md->vertices = 0;
	md->faces = 0;
	while (obj_file.getline(line, 256))
		if (line[0] == 'v' && line[1] == ' ')
			md->vertices++;
		else if (line[0] == 'f' && line[1] == ' ')
			md->faces++;

	cout << "Number of vertices: " << md->vertices << endl;
	cout << "Number of faces: " << md->faces << endl;

	md->obj_points = new point[md->vertices];
	md->obj_faces = new face[md->faces];
	obj_file.close();



	obj_file.open("planet.obj");

	for (int i = 0; i < md->vertices; i++) {                       // Get the vertex coordinates
		if (obj_file.get() == 'v' && obj_file.get() == ' ') {
			obj_file.get();
			obj_file >> md->obj_points[i].x;
			obj_file >> md->obj_points[i].y;
			obj_file >> md->obj_points[i].z;
		}
		else
			i--;
		obj_file.ignore(256, '\n');
	}

	for (int i = 0; i < md->faces; i++) { // Get the face structure
		if (obj_file.get() == 'f' && obj_file.get() == ' ') {
			obj_file.get();
			obj_file >> md->obj_faces[i].vtx[0];
			obj_file.ignore(256, ' ');
			obj_file >> md->obj_faces[i].vtx[1];
			obj_file.ignore(256, ' ');
			obj_file >> md->obj_faces[i].vtx[2];
		}
		else
			i--;
		obj_file.ignore(256, '\n');
	}

	obj_file.close();
}

void DisplayModel(model md)
{
	//glScalef(0.005, 0.005, 0.005);
	//glTranslatef(150, 0, -1150);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < md.faces; i++)
	{
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[0] - 1].x, md.obj_points[md.obj_faces[i].vtx[0] - 1].y, md.obj_points[md.obj_faces[i].vtx[0] - 1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[1] - 1].x, md.obj_points[md.obj_faces[i].vtx[1] - 1].y, md.obj_points[md.obj_faces[i].vtx[1] - 1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[2] - 1].x, md.obj_points[md.obj_faces[i].vtx[2] - 1].y, md.obj_points[md.obj_faces[i].vtx[2] - 1].z);
	}

	glEnd();
}