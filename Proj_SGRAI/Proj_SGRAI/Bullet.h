#pragma once

#ifndef _Bullet_H_
#define _Bullet_H_

#include "globalHeader.h"


#define BULLET_SPEED 0.1

class Bullet {
private:

	double speed;


public:

	bool shoot;
	float  yaw,pitch;
	float x, y,z;
	float size;
	int x_dest;
	int y_dest;

	Bullet();

	~Bullet(void);

	void setInitial(float, float, float,float );
	void Draw();			//draw bullet
	void Move();
};
#endif