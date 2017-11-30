#pragma once
#ifndef _BOARDMATRIXCALCULATIONS_H_
#define _BOARDMATRIXCALCULATIONS_H_

#include "globalHeader.h"
class BoardMatrixCalculations {

private:
	


public:


	int** create_randomBoard();
	int** create_genRandomLab();

	void alter_placeElementsInBoard(int**);
	void alter_placeEnemiesInBoard(int**);

	int** move_enemy_simple(int**);
	int** move_enemy_boss(int**);

};

#endif