#include "Character.h"
#include <stdio.h>
#include <GL/glut.h>
#include <Math.h>

// Destructor
Character::~Character(void) {}
Board board;
//Constructor (inicializa)
Character::Character(double tx, double ty, float size, Board b)
{
	board = b;
	Character::size = size;
	lives = NUM_LIVES;
	x = tx;
	y = ty;
	angle = CHAR_ANGLE;
	speed = CHAR_SPEED;
	animate = false;
}

//put Character at starting position and angle
void
Character::Reinit(void)
{
	x = CHARACTER_STARTLOCATION_X;
	y = CHARACTER_STARTLOCATION_Y;
	angle = CHAR_ANGLE;
	animate = false;
}

void
Character::MoveTo(int xF, int yF)
{
	char* a = board.getPath(x, y, xF, yF);
	if (a == NULL) {
		printf("NOTHING\n");
	}
	printf("---------------------------------\n%s\n---------------------------------------\n", a);
}

void
Character::Draw(void)
{

	//draw current Character
	glColor3f(1.0, 0.25, 0.25);	
	glPushMatrix();
	{
		glTranslatef(Character::x, -Character::y, 0);
		glTranslatef(size/2, size +0.1, 0);
		glTranslatef((float)Board::BOARD_X*BOARD_SCALE_DEFAULT / -2.0, (float)Board::BOARD_Y*BOARD_SCALE_DEFAULT / 2.0, 0.5);
		glutSolidSphere(size/2, 10, 10);
	}
	glPopMatrix();
}