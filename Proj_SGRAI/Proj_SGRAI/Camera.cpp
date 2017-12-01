#include "Camera.h"



// Destructor
Camera::~Camera(void) {}

Camera::Camera() {
	yaw = 0.0;
	pitch = 0.0;
}

void
Camera::Reshape(float ratio, int distance)
{
	Camera::ratio = ratio;
	Camera::distance = distance;

	//Cull back faces
	//glEnable(GL_CULL_FACE);

	// Turn on normal vector normalization. 
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the clipping volume
	gluPerspective(60, ratio, 0.1, 100);

	// Clear the screen.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void
Camera::Set_position(float x_at, float y_at, int view)
{
	// Clear the screen.
	glLoadIdentity();

	x = x_at;
	y = y_at;
	z = 0.5;

	centerX = cos(yaw) * cos(pitch);
	centerY = sin(yaw) * cos(pitch);
	centerZ = sin(-pitch);


	if (view == VIEW_MAP) {

		gluLookAt(-1.5f, 0.0f, distance,					// eye
			-1.5f, 0.0f, 0.0f,							// center
			1.0f, 0.0f, 0.0f);					// up

	}
	else if (view == VIEW_THIRD_PERSON) {

		gluLookAt(x - 3, y , z + 5,						// eye
					x, y, z,									// center
				0.0f, 0.0f, 1.0f);																			// up (x, y, x)
	}
	else if (view == VIEW_FIRST_PERSON) {
		gluLookAt(x, y, z,
			x + centerX, y + centerY, z + centerZ,
			0.0, 0.0, 1.0);
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

void Camera::set_light(float x_c, float y_c, float z_c) {

	glPushMatrix(); {
		// Set lighting intensity and color
		glTranslatef(x_c, y_c , 0);
		//glTranslatef(z_c / 2, z_c + 0.1, 0);
		//glTranslatef((float)Board::BOARD_X / -2.0, (float)Board::BOARD_Y / 2.0, 0.715);
		GLfloat ambientLight[] = { 0.1, 0.1, 0.1, 1.0 };
		GLfloat diffuseLight[] = { 1, 1, 1, 1.0 };
		GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

		// Light source position
		GLfloat lightPosition[] = { 0,0,5, 1 };
		GLfloat vector0[] = { 0, 0, -1 };

		// Enable lighting
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);

		//// Set lighting intensity and color
		//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		//glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

		//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, CUTOFF);// set cutoff angle
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, vector0);
		/*
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, -0.5);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.00000005);*/
	}glPopMatrix();
}


