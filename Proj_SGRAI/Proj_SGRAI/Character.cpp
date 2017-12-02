#include "Character.h"

// Destructor
Character::~Character(void) {}
Board board;
//Constructor (inicializa)
Character::Character(double tx, double ty, float size, Board b)
{
	mdlviewer_init("weapon.mdl", weapon);
	//mdlviewer_init("character.mdl", model);
	board = b;
	Character::size = size;
	lives = NUM_LIVES;
	x = tx + 0.5;
	y = ty + 0.5;
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
	//draw Weapon
	if (true/*view == VIEW_FIRST_PERSON*/) {
		//Codigo para a mira Aqui
			glPushMatrix(); {
				glTranslatef(Character::x, Character::y, 0.45);

				glRotatef(GRAUS(yaw), 0, 0, 1);
				glRotatef(GRAUS(pitch), 0, 1, 0);

				glScalef(SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01);
				mdlviewer_display(weapon);
			}glPopMatrix();
	}
	else {
		//draw spheare
		glColor3f(1.0, 0.25, 0.25);
		glPushMatrix();
		{
			glTranslatef(Character::x, Character::y, 0.45);
			glScalef(SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01);
			mdlviewer_display(model);
		}
		glPopMatrix();

	}

}