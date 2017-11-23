#include "Board.h"
#include <cstdlib> 
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

int map[Board::BOARD_X][Board::BOARD_Y];
int closed_nodes_map[Board::BOARD_X][Board::BOARD_Y]; // map of closed (tried-out) nodes
int open_nodes_map[Board::BOARD_X][Board::BOARD_Y]; // map of open (not-yet-tried) nodes
int dir_map[Board::BOARD_X][Board::BOARD_Y]; // map of directions


static const int dir = 8; // number of possible directions to go at any position
// if dir==4
//static int dx[dir]={1,  0,  -1,   0};
//static int dy[dir]={0,  1,   0,  -1};
// if dir==8

//			    R     R_UP    UP    L_UP     L   L_DOWN    DOWN   R_DOWN 
int dx[dir] = { 1,     1,     0,    -1,	    -1,	   -1,       0,     1 };
int dy[dir] = { 0,     1,     1,     1,      0,    -1,      -1,	   -1 };

bool first = true;
Astar_Algorithm::Astar_Algorithm(int** board) {
	

	for (int i = 0; i < Board::BOARD_X; i++) {
		for (int j = 0; j < Board::BOARD_Y; j++) {
			map[i][j] = board[i][j];
		}
	}
	if (first) {
		first = false;
		for (int i = 0; i < Board::BOARD_X; i++) {
			for (int j = 0; j < Board::BOARD_Y; j++) {
				printf("%d", board[i][j]);
			}
			printf("\n");
		}
	}
}

// Determine priority (in the priority queue)
bool operator<(const Node & a, const Node & b)
{
	return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
char* Astar_Algorithm::pathFind(const int & xStart, const int & yStart,
	const int & xFinish, const int & yFinish)
{
	static std::priority_queue<Node> pq[2]; // list of open (not-yet-tried) nodes
	static int pqi; // pq index
	static Node* x0;
	static Node* y0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	// reset the node maps
	for (y = 0; y<Board::BOARD_Y; y++)
	{
		for (x = 0; x<Board::BOARD_X; x++)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	// create the start node and push into list of open nodes
	x0 = new Node(xStart, yStart, 0, 0);
	x0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*x0);
	open_nodes_map[x][y] = x0->getPriority(); // mark it on the open nodes map
	delete x0;
											  // A* search
	while (!pq[pqi].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodes
		x0 = new Node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = x0->getxPos(); y = x0->getyPos();

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[x][y] = 0;
		// mark it on the closed nodes map
		closed_nodes_map[x][y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			char* path = "";
			while (!(x == xStart && y == yStart))
			{
				j = dir_map[x][y];
				c = '0' + (j + dir / 2) % dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			// garbage collection
			delete x0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>Board::BOARD_X - 1 || ydy<0 || ydy>Board::BOARD_Y - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				// generate a child node
				y0 = new Node(xdx, ydy, x0->getLevel(),
					x0->getPriority());
				y0->nextLevel(i);
				y0->updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = y0->getPriority();
					pq[pqi].push(*y0);
					// mark its parent node direction
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
					delete y0;
				}
				else if (open_nodes_map[xdx][ydy]>y0->getPriority())
				{
					// update the priority info
					open_nodes_map[xdx][ydy] = y0->getPriority();
					// update the parent direction info
					dir_map[xdx][ydy] = (i + dir / 2) % dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node

								   // empty the larger size pq to the smaller one
					if (pq[pqi].size()>pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*y0); // add the better node instead
				}
				else delete y0; // garbage collection
			}
		}
		delete x0; // garbage collection
	}
	return ""; // no route found
}
