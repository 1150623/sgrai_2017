
#include "Camera.h"
#include "Board.h"
#include <stdio.h>
#include <GL/glut.h>
#include <Math.h>


// Destructor
Camera::~Camera(void) {}

//Constructor
Camera::Camera(float ratio, float distance)
{
	Camera::ratio = ratio;
	Camera::distance = distance;

	//Cull back faces
	glEnable(GL_CULL_FACE);
	
	//double  eye[3];
	float   color[4], dir[4];

	// Enable lighting with one light.
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Turn on normal vector normalization. 
	glEnable(GL_NORMALIZE);

	
	color[0] = 1.0f; 
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	color[0] = 0.0f; 
	color[1] = 0.0f; 
	color[2] = 0.0f; 
	color[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_SPECULAR, color);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the clipping volume
	gluPerspective(Camera::distance, ratio, 0.005, 100);

	// Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Position the light source. -> Directional light
	dir[0] = 0.2; dir[1] = 1.0; dir[2] = 1.0; dir[3] = 0.2;
	glLightfv(GL_LIGHT0, GL_POSITION, dir);
}
void
Camera::Set_position(float x_at, float y_at, int view)
{
	// Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (view == 1) {
		
		gluLookAt(	-1.5f, 0.0f, 40.0f,					// eye
					-1.5f, 0.0f, 0.0f,					// center
					0.0f, 1.0f, 0.0f);					// up

	}
	else if(view == 0) {
		
		gluLookAt(.8f*(float)(	x_at - Board::BOARD_X / 2) - 0.3, -y_at + Board::BOARD_Y / 4 - 10, 20,						// eye
								x_at - Board::BOARD_X / 2, -y_at + Board::BOARD_Y / 2, 1,									// center
								0.0f, 0.0f, 1.0f);																			// up (x, y, x)
	}
	else { 
			//VISTA PRIMEIRA PESSOA
	}
	
}