#include "Character.h"

// Destructor
Character::~Character(void) {}
Board board;
//Constructor (inicializa)
Character::Character(double tx, double ty, float size, Board b)
{
	mdlviewer_init("weapon.mdl", weapon);
	board = b;
	Character::size = size;
	lives = NUM_LIVES;
	x = 1.5;
	y = 1.5;
	angle = CHAR_ANGLE;
	speed = CHAR_SPEED;
	animate = false;
}

//put Character at starting position and angle
void
Character::Reinit(void)
{
	//x = CHARACTER_STARTLOCATION_X;
	//y = CHARACTER_STARTLOCATION_Y;
	//angle = CHAR_ANGLE;
	//animate = false;
}

void
Character::MoveTo(int xF, int yF)
{
	AStar::CoordList coords = board.getPath(x, y, xF, yF);
	
}

void
Character::Draw(float pitch, float yaw, int view)
{

	//printf("x = %f, y = %f  %d  \n", x, y, board_walls[(int)y][(int)x]);
	//draw Weapon
	if (true/*view == VIEW_FIRST_PERSON*/) {
		//Codigo para a mira Aqui
			glPushMatrix(); {
				glTranslatef(Character::x, Character::y, 0.45);
				/*glTranslatef(size / 2, size + 0.1, 0);*/
				//glTranslatef((float)Board::BOARD_X / -2, (float)Board::BOARD_Y / 2.0, 0.715);
				//glRotatef(GRAUS(angle), 0, 1, 0);
				//glRotatef(-90, 1, 0, 0);
				glRotatef(GRAUS(yaw), 0, 0, 1);
				glRotatef(GRAUS(pitch), 0, 1, 0);
				glScalef(SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01);
				mdlviewer_display(weapon);
			
				/*
				glColor3f(1.0, 1.0,0.0);
				glutSolidSphere(size, 10, 10);*/
			}glPopMatrix();
	}
	else {
		//draw spheare
		glColor3f(1.0, 0.25, 0.25);
		glPushMatrix();
		{
			glTranslatef(Character::x, -Character::y, -size);
			glTranslatef(0.01+ size / 2, 0.5, 0);

			glTranslatef((float)Board::BOARD_X / -2.0, (float)Board::BOARD_Y / 2.0, 0.5);
			glutSolidSphere(size / 2, 10, 10);
		}
		glPopMatrix();


		/*	glTranslatef(Monster::y, -Monster::x, -size);
			glTranslatef(0.01 + size / 2, 0.5, 0);
			glTranslatef((float)Board::BOARD_X / -2.0, (float)Board::BOARD_Y / 2.0, 0.5);
			glutSolidSphere(size / 2, 10, 10);
*/
		
	}

}