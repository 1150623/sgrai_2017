#pragma once
#include "globalHeader.h"
#include "Node.h"
using namespace std;
#ifndef _ASTAR_ALGORITHM_H_
#define _ASTAR_ALGORITHM_H_

class Astar_Algorithm
{ 
	private:
		

	public:

		Astar_Algorithm(int**);
		void getBoardMap(int**);

		// A-star algorithm.
		// The route returned is a string of direction digits.
		char* pathFind(const int & xStart, const int & yStart,const int & xFinish, const int & yFinish);

};

#endif