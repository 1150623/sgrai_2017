#pragma once

#ifndef  _OBJECT_H_
#define _OBJECT_H_

#include "globalHeader.h"
#ifndef _BOARD_H_
#include "Board.h"
#endif
#include "mdlviewer.h"
class Object {

public:

	int type;

	float x, y, size;

	bool got_it;

	StudioModel bandage;
	StudioModel bullet;

	~Object(void);

	Object(int type, float, float, float, Board);

	void Draw(void);			//draw 
};
#endif
