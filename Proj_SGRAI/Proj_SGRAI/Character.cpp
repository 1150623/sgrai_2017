#include "Character.h"
#include "Board.h"
#include <stdio.h>
#include <GL/glut.h>
#include <Math.h>

float boardScale;
// Destructor
Character::~Character(void) {}

//Constructor (inicializa)
Character::Character(double tx, double ty, float scale)
{
	boardScale = scale;
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
	x = 13.5;
	y = 23;
	angle = CHAR_ANGLE;
	animate = false;
}

void
Character::Move()
{
	x += speed*cos(M_PI / 180 * angle);
	y += speed*sin(M_PI / 180 * angle);
}

void
Character::Draw(void)
{
	//draw current Character
	glColor3f(1.0, 0.25, 0.25);	
	glPushMatrix();
	{
		glTranslatef(Character::x, -Character::y, 0);
		glTranslatef(.5, 0.6, 0);
		glTranslatef((float)Board::BOARD_X / -2.0, (float)Board::BOARD_Y / 2.0, 0.5);
		glutSolidSphere(0.5, 10, 10);
	}
	glPopMatrix();

	//draw remaining Character lives above the board
	for (int i = 0; i < lives - 1; i++)
	{
		glColor3f(0.4, 0.15, 0.25);
		glPushMatrix(); {
			glTranslatef((float)Board::BOARD_X*boardScale / -2.0 + i * 2, (float)Board::BOARD_Y* boardScale / 2.0 + 3, 1.0);
			glutSolidSphere(0.5, 10, 10);
		}
		glPopMatrix();
	}
}