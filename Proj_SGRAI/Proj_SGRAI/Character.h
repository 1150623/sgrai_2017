#pragma once
#pragma once
#ifndef _Character_H_
#define _Character_H_

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#include <gl/glut.h>

#define NUM_LIVES 3
#define CHAR_ANGLE 30
#define CHAR_SPEED 0.1

class Character {
private:

	double speed;

public:

	int lives; // will it be needed??

	double angle;
	double x, y;
	bool animate;

	Character(double, double, float);

	~Character(void);

	void Move();		//move the Character

	void Reinit();		//reinitialize everything
					
	void Draw(void);	//draw character
};
#endif
