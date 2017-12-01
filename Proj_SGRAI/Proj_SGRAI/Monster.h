#pragma once

#ifndef  _MONSTER_H_
#define _MONSTER_H_

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#include "mdlviewer.h"
#include "globalHeader.h"
#ifndef _BOARD_H_
#include "Board.h"
#endif
#define MONSTER_NUM_LIVES 3
#define MONSTER_ANGLE 30


class Monster {
private:

	void desenhaPoligono(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[]);
	void desenhaCubo();
public:
	double speed;
	int lives; // will it be needed??
	bool killed;
	float angle;
	double x, y;
	bool animate;
	float size;
	int dynamiteFound = DEBBUG ? DYNAMITE_NEEDED : 0;
	int startIndexMonster;
	StudioModel model;
	Board* boards;

	Monster(double, double, float, int,Board*);

	~Monster(void);

	void MoveTo();		//move the Character

	void Reinit();				//reinitialize everything

	void initDirection(int); // get direction monster

	void Draw(void);			//draw character
};
#endif
