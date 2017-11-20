#pragma once
#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "globalHeader.h"

class Camera {
private:

public:

	float distance, ratio;

	// Constructor.
	Camera(float, float);

	// Destructor.
	~Camera(void);

	void Set_position(float, float, int);
};


#endif