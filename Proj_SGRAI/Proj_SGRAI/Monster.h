#pragma once

#ifndef _Monster_H_
#define _Monster_H_

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#include "globalHeader.h"
#include "Board.h"
#define MONSTER_NUM_LIVES 3
#define MONSTER_ANGLE 30
#define MONSTER_SPEED 0.1

static struct savePositionMonsters
{
	int x, y;
};

static std::vector<savePositionMonsters> VecPositionMonsters;

class Monster {
private:

	double speed;

public:

	int lives; // will it be needed??

	double angle;
	double x, y;
	bool animate;
	float size;
	int dynamiteFound = DEBBUG ? DYNAMITE_NEEDED : 0;

	Monster(double, double, float, Board);

	~Monster(void);

	void MoveTo(int, int);		//move the Character

	void Reinit();				//reinitialize everything

	void GenerateRandoMonsters(Board); // generate randm monster 

	void Draw(void);			//draw character
};
#endif
