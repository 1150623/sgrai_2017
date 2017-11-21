#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

#include "globalHeader.h"
class Board {

	
	private:

		void drawWalls(void);

		void DRAW_WALLS_SOUTH(void);
		void DRAW_WALLS_NORTH(void);
		void DRAW_WALLS_WEST(void);
		void DRAW_WALLS_EAST(void);
		void DRAW_WALLS_BOTTOM(void);
		void DRAW_WALLS_TOP(void);

		byte WALLS_NORTH = 64;	// 01000000
		byte WALLS_SOUTH = 32;	// 00100000
		byte WALLS_EAST = 16;	// 00010000
		byte WALLS_WEST = 4;	// 00001000
		byte WALLS_TOP = 2;		// 00000100
		byte WALLS_BOTTOM = 1;	// 00000010
		byte WALLS_EMPTY = 0;	// 00000001

	public:
		#define NUM_WALLS		6

		static const float BOARD_WALL_SIZE;
		static const int BOARD_X;
		static const int BOARD_Y;

		float ang;

		//Construtor
		Board();

		//Destructor
		~Board();

		//this function returns whether or not a location is open or is a wall
		bool IsOpen(int, int);

		//Restores objects to lab (not implemented yet -> for example, restores keys to open a door (when board is reloaded for example))
		void tp_restore(void);

		//Desenha Labirinto
		void Draw(void);

};

#endif


