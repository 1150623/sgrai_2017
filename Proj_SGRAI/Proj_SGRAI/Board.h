#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

#include "globalHeader.h"
class Board {

	private:
		//void desenhaCubo();
		//void desenhaParedes();
		//void scaleWalls();

		GLubyte list[5];  //display lists for each wall

		void create_list_lib(void);
		void drawWalls(void);
	public:

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


