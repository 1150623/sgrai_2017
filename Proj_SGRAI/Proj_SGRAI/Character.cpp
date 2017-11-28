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
	//x = CHARACTER_STARTLOCATION_X;
	//y = CHARACTER_STARTLOCATION_Y;
	//angle = CHAR_ANGLE;
	//animate = false;
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
	//draw Weapon
	//glPushMatrix();
	//	glTranslatef(Character::x, -Character::y + size * 2, -size);
	//	glTranslatef(size / 2, size + 0.1, 0);
	//	glTranslatef((float)Board::BOARD_X / -1.996, (float)Board::BOARD_Y / 2.0, 0.715);
	//	//glRotatef(GRAUS(angle), 0, 1, 0);
	//	//glRotatef(-90, 1, 0, 0);
	//	glRotatef(GRAUS(angle), 0, 1, 0);
	//	glScalef(SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01);
	//	mdlviewer_display(weapon);
	//glPopMatrix();

	//draw spheare
	glColor3f(1.0, 0.25, 0.25);	
	glPushMatrix();
	{
		glTranslatef(Character::x, -Character::y+size*2, -size);
		glTranslatef(size/2, size +0.1, 0);
		glTranslatef((float)Board::BOARD_X / -2.0, (float)Board::BOARD_Y / 2.0, 0.5);
		//glRotatef(GRAUS(angle), 0, 1, 0);
		glutSolidSphere(size/2, 10, 10);
	}
	glPopMatrix();


}

void
Character::Draw(float pitch,float yaw)
{
	//draw Weapon
	glPushMatrix(); {
		
		//Codigo para a mira Aqui
		glPushMatrix(); {
			glTranslatef(Character::x, -Character::y + size * 2, -size);
			glTranslatef(size / 2, size + 0.1, 0);
			glTranslatef((float)Board::BOARD_X / -1.996, (float)Board::BOARD_Y / 2.0, 0.715);
			//glRotatef(GRAUS(angle), 0, 1, 0);
			//glRotatef(-90, 1, 0, 0);
			glRotatef(GRAUS(pitch), 0, 1, 0);
			glRotatef(GRAUS(yaw), 0, 0, 1);
			glScalef(SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01);
			mdlviewer_display(weapon);
		}glPopMatrix();
	}glPopMatrix();

	//draw spheare
	//glColor3f(1.0, 0.25, 0.25);	
	//glPushMatrix();
	//{
	//	glTranslatef(Character::x, -Character::y+size*2, -size);
	//	glTranslatef(size/2, size +0.1, 0);
	//	glTranslatef((float)Board::BOARD_X / -2.0, (float)Board::BOARD_Y / 2.0, 0.5);
	//	//glRotatef(GRAUS(angle), 0, 1, 0);
	//	glutSolidSphere(size/2, 10, 10);
	//}
	//glPopMatrix();
}