#pragma once
#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "globalHeader.h"
#include "Board.h"

class Camera {
private:

public:

	float distance, ratio;

	float x, y, z;   // Position
	float centerX, centerY, centerZ; // Direction vector of where we are looking at
	float yaw, pitch; // Various rotation angles

	// Constructor.
	void Reshape(float, int);

	// Destructor.
	~Camera(void);

	Camera(void);

	void Set_position(float, float, int);

	void RotateYaw(float angle);
	void RotatePitch(float angle);

	void set_light(float, float, float);
};



#endif