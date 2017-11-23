#pragma once

#ifndef _NODE_H_
#define _NODE_H_

#include "A star_Algorithm.h"

class Node
{

	private:
		// current position
		int xPos;
		int yPos;
		// total distance already travelled to reach the node
		int level;
		// priority=level+remaining distance estimate
		int priority;  // smaller -> higher priority

	public:


	Node(int, int, int, int);

	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }

	void updatePriority(const int & xDest, const int & yDest);

	// give better priority to going strait instead of diagonally
	void nextLevel(const int & i); // i-> direction

	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const
	{
		static int xd, yd, d;
		xd = xDest - xPos;
		yd = yDest - yPos;

		// Euclidian Distance
		d = static_cast<int>(sqrt(xd*xd + yd*yd));
		return(d);
	}
};

#endif