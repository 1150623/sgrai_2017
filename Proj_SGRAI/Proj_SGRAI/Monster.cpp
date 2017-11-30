#include "Monster.h"
#include <stdio.h>
#include <GL/glut.h>
#include <Math.h>

// Destructor
Monster::~Monster(void) {}
Board boards;
//Constructor (inicializa)
Monster::Monster(double tx, double ty, float size, int IndexMonster, Board b)
{
	boards = b;
	Monster::size = size;
	lives = MONSTER_NUM_LIVES;
	x = tx;
	y = ty;
	angle = MONSTER_ANGLE;
	speed = MONSTER_SPEED;
	animate = false;
	startIndexMonster = IndexMonster;
	//initDirection(); //verifica na matrix a direção que tem de seguir
}

void Monster::Draw(void)
{
	//draw current Character
	glColor3f(1.0, 0.25, 0.25);
	glPushMatrix();
	{
		glTranslatef(Monster::x, -Monster::y + size * 2, -size);
		glTranslatef(size / 2, size + 0.1, 0);
		glTranslatef((float)Board::BOARD_X / -2.0, (float)Board::BOARD_Y / 2.0, 0.5);
		glutSolidSphere(size / 2, 10, 10);

	}
	glPopMatrix();
}


void Monster::Start(void) {

	//if(isCharacterInZone(zone))
		//Check Distance
			//if Dist > X
				//Estado patrulha
			//else if dist < x*0.5f
				//estado melee
			//else if dist < x
				//estado shoot
	//else patrulha

	//ativateState()
}

//void initDirection() {
//	vector
//
//
//}
