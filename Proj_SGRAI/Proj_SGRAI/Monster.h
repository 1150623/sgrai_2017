#pragma once

#ifndef  _MONSTER_H_
#define _MONSTER_H_

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#include "globalHeader.h"
#ifndef _BOARD_H_
#include "Board.h"
#endif
#define MONSTER_NUM_LIVES 3
#define MONSTER_ANGLE 30
#define MONSTER_SPEED 0.1


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
	int startIndexMonster;

	bool ESTADO_PATRULHA = false;
	bool ESTADO_SHOOT = false;
	bool ESTADO_MELEE = false;
	bool ESTADO_DEAD = false;

	Monster(double, double, float, int,Board);

	~Monster(void);

	void Start(void);		//Patrulha 

	void Reinit();				//reinitialize everything

	void Draw(void);			//draw character
};
#endif
