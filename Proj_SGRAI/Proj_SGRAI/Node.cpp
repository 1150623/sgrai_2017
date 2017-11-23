#include "Board.h"

static const int dir = 8; // number of possible directions to go at any position

Node::Node(int xp, int yp, int d, int p)
{
	xPos = xp; yPos = yp; level = d; priority = p;
}

void Node::updatePriority(const int & xDest, const int & yDest)
{
	priority = level + estimate(xDest, yDest) * 10; //A*
}

// give better priority to going strait instead of diagonally
void Node::nextLevel(const int & i) // i: direction
{
	level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
}
