#include "Monster.h"
#include <stdio.h>
#include <GL/glut.h>
#include <Math.h>

// Destructor
Monster::~Monster(void) {}
Board boards;

//Constructor (inicializa)
Monster::Monster(double tx, double ty, float size, int IndexMonster,Board b)
{
	killed = false;
	boards = b;
	Monster::size = size;
	lives = MONSTER_NUM_LIVES;
	x = tx + 0.5;
	y = ty+ 0.5;
	angle = MONSTER_ANGLE;
	speed = MONSTER_SPEED;
	animate = false;
	startIndexMonster = IndexMonster;
	initDirection(startIndexMonster); //verifica na matrix a direção que tem de seguir

}

void Monster::Draw(void)
{
	//draw current Character
	glColor3f(1.0, 0.25, 0.25);
	glPushMatrix();
	{

		glTranslatef(Monster::x, Monster::y, size);
		glutSolidSphere(size / 2, 10, 10);

	}
	glPopMatrix();
}


float Monster::initDirection(int startIndexMonster) {
	int y = boards.VecPositionMonsters[startIndexMonster].linha;
	int x = boards.VecPositionMonsters[startIndexMonster].coluna;
	boards.ImprimeBoarder();

	// imprime a matrix
	int i, j;
	for (i = 0; i < Board::BOARD_X; i++) {
		for (j = 0; j < Board::BOARD_Y; j++) {
			printf(" %2d ", board_walls[i][j]);
		}
		printf("\n");
	}

	//maisX
	if (board_walls[x + 1][y] == (startIndexMonster + BASE_INDEX_MONSTERS)) {
		return 0;
	}
	else if (board_walls[x - 1][y] == (startIndexMonster + BASE_INDEX_MONSTERS)) {
		return M_PI;
	}
	else if (board_walls[x][y + 1] == (startIndexMonster + BASE_INDEX_MONSTERS)) {
		return M_PI * 0.5;
	}
	else if (board_walls[x][y - 1] == (startIndexMonster + BASE_INDEX_MONSTERS)) {
		return (3 * M_PI)*0.5;
	}
	else {
		// o monstro nao tem sitio para ir entao fica parado no mesmo sitio ate que alguem entre no seu quadrante
		return -1;
	}
}
