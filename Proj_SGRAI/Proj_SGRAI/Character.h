#pragma once

#ifndef _Character_H_
#define _Character_H_

#include "globalHeader.h"
#include "Board.h"
#include "mdlviewer.h"


#define CHAR_ANGLE 30
#define CHAR_SPEED 0.1

class Character {
private:

	double speed;

public:

	struct {
		int x, y;
	} direction;

	int lives;
	int retrys;

	int startX;
	int startY;

	double angle;
	double x, y;
	bool animate;
	float size;
	int dynamiteFound = DEBBUG ? DYNAMITE_NEEDED : 0;
	StudioModel weapon;
	StudioModel model;

	Character(double, double, float, Board);

	~Character(void);

	void InitModelTerceicaPessoa();

	void InitModelPrimeiraPessoa();
	int seq;
	int seqAtual;

	void Reload(bool);
	void Moving(bool);
	void Shooting(bool);
	void Reinit();				//reinitialize everything

	void Draw(float, float,int);			//draw character
};
#endif
