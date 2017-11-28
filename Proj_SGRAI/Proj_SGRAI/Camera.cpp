#include "Camera.h"



// Destructor
Camera::~Camera(void) {}

//Constructor
Camera::Camera(float ratio, float distance)
{
	Camera::ratio = ratio;
	Camera::distance = distance;
	yaw = 0.0;
	pitch = 0.0;

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
	gluPerspective(Camera::distance, ratio, 0.1, 50);

	// Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Position the light source. -> Directional light
	dir[0] = 0.1; dir[1] = 0.3; dir[2] = 1.0; dir[3] = 0.2;
	glLightfv(GL_LIGHT0, GL_POSITION, dir);
}
void
Camera::Set_position(float x_at, float y_at, int view)
{
	// Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	x = x_at - Board::BOARD_X / 2-0.40;
	y = -y_at + Board::BOARD_Y / 2+0.87;
	z = 0.5;

	centerX = cos(yaw) * cos(pitch);
	centerY = sin(yaw) * cos(pitch);
	centerZ = sin(-pitch);


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
		gluLookAt(x, y, z, x + centerX, y + centerY, z + centerZ, 0.0, 0.0, 1.0);
	}


	
}

void Camera::RotateYaw(float angle)
{
	yaw -= angle;
}

void Camera::RotatePitch(float angle)
{
	const float limit = 89.0 * M_PI / 180.0;

	pitch += angle;

	if (pitch < -limit)
		pitch = -limit;

	if (pitch > limit)
		pitch = limit;

}

void
Camera::set_light() {
	// Set lighting intensity and color
	GLfloat ambientLight[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat diffuseLight[] = { 1, 1, 1, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emitLight[] = { 0.9, 0.9, 0.9, 0.01 };

	// Light source position
	GLfloat lightPosition[] = { 0, 0, 2, 1 };
	GLfloat lightDirection[] = { 1, 1, 1, 0 };
	GLfloat dirVector0[] = { 0.2, 1.0, 1.0, 0.2 };

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//// Set lighting intensity and color
	/*glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);*/
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	////////////////////////////////////////////



	glLightfv(GL_LIGHT0, GL_SPECULAR, dirVector0);

}


