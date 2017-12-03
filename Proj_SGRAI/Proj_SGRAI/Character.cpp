#include "Character.h"

// Destructor
Character::~Character(void) {}
Board board;
//Constructor (inicializa)
Character::Character(double tx, double ty, float size, Board b)
{
	mdlviewer_init("weapon.mdl", weapon);
	mdlviewer_init("terceiraPessoa.mdl", model);
	board = b;
	Character::size = size;
	lives = NUM_LIVES;
	retrys = NUM_RETRYS;
	x = tx + 1;
	startX = x;
	y = ty - 0.5;
	startY = y;
	angle = CHAR_ANGLE;
	speed = CHAR_SPEED;
	animate = false;
}


void
Character::InitModelPrimeiraPessoa() {
	mdlviewer_init("weapon.mdl", weapon);
}


void
Character::InitModelTerceicaPessoa() {
	mdlviewer_init("terceiraPessoa.mdl", model);
}


//put Character at starting position and angle
void
Character::Reinit(void)
{
	x = startX;
	y = startY;
	angle = CHAR_ANGLE;
	retrys--;
	lives = NUM_LIVES;
	animate = false;
}


void
Character::Draw(float pitch, float yaw, int view)
{
	//draw Weapon
	if (view == VIEW_FIRST_PERSON) {

			glPushMatrix(); {
				glTranslatef(Character::x, Character::y, 0.45);

				glRotatef(GRAUS(yaw), 0, 0, 1);
				glRotatef(GRAUS(pitch), 0, 1, 0);

				glScalef(SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01);
				mdlviewer_display(weapon);
				mdlviewer_nextsequence;
			}glPopMatrix();
	}
	else {

		//draw soldier
		glColor3f(1.0, 0.25, 0.25);
		glPushMatrix();
		{
			glTranslatef(Character::x, Character::y, 0.55);
			glRotatef(GRAUS(yaw), 0, 0, 1);
			glScalef(SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01);
			mdlviewer_display(model);
			model.AdvanceFrame(0.01);
			
		}
		glPopMatrix();

	}
}