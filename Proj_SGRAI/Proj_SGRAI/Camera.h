#pragma once
#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <gl/glut.h>

class Camera {
private:

public:

	// Constructor.
	Camera(float);

	// Destructor.
	~Camera(void);

	void Set_position(float, float, int);
};


#endif