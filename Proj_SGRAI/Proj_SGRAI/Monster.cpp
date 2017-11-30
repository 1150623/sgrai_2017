#include "Monster.h"
#include <stdio.h>
#include <GL/glut.h>
#include <Math.h>

// Destructor
Monster::~Monster(void) {}
Board boards;

//Constructor (inicializa)
Monster::Monster(double tx, double ty, float size, Board b)
{
	boards = b;
	Monster::size = size;
	lives = MONSTER_NUM_LIVES;
	x = tx;
	y = ty;
	angle = MONSTER_ANGLE;
	speed = MONSTER_SPEED;
	animate = false;
}

void Monster::Draw(void)
{
	//draw current Character
	glColor3f(1.0, 0.25, 0.25);
	glPushMatrix();
	{

		glTranslatef(Monster::y, -Monster::x, -size);
		glTranslatef(0.01+ size / 2, 0.5, 0);
		glTranslatef((float)Board::BOARD_X / -2.0, (float)Board::BOARD_Y / 2.0, 0.5);
		glutSolidSphere(size / 2, 10, 10);

	}
	glPopMatrix();
}
