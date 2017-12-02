#pragma once
#ifndef _BOARDMATRIXCALCULATIONS_H_
#define _BOARDMATRIXCALCULATIONS_H_

#include "globalHeader.h"
#include "stdafx.h"


// CELL STRUCTURE
	static struct Cell
	{
		bool visited;
		bool top_wall;
		bool bot_wall;
		bool left_wall;
		bool right_wall;
		int display;
	};

	void createRandomLab(int board_walls[LAB_SIZE][LAB_SIZE]);

#endif