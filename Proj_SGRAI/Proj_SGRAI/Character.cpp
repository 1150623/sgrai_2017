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
	AStar::CoordList coords = board.getPath(x, y, xF, yF);
	
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


	glPushMatrix();



	glLineWidth(1);

	float radius = 0.125;
	float aimSize = 0.010;

	float centerX;
	float centerY;
	float centerZ;

	centerX = radius * cos(pitch);
	centerZ = 0.2 + (radius * sin(pitch));
	centerY = 0;

	float beta = RAD(90.0f - GRAUS(pitch));

	float posX11 = centerX + ((aimSize / 8) * -cos(beta));
	float posY11 = centerZ + ((aimSize / 8) * sin(beta));

	float posX1 = centerX + ((aimSize / 4) * -cos(beta));
	float posY1 = centerZ + ((aimSize / 4) * sin(beta));


	float posX21 = centerX + ((aimSize / 8) * cos(beta));
	float posY21 = centerZ + ((aimSize / 8) * -sin(beta));

	float posX2 = centerX + ((aimSize / 4) * cos(beta));
	float posY2 = centerZ + ((aimSize / 4) * -sin(beta));


	// Eixo dos y - mira 1
	glBegin(GL_LINES);
	glColor3f(0.11, 0.56, 1.0);
	glVertex3f(posX1, posY1, 0);
	glVertex3f(posX11, posY11, 0);
	glEnd();

	// Eixo dos y - mira 2
	glBegin(GL_LINES);
	glColor3f(1.0, 0.7, 0.0);
	glVertex3f(posX21, posY21, 0);
	glVertex3f(posX2, posY2, 0);
	glEnd();

	// Eixo dos z - mira 1
	glBegin(GL_LINES);
	glColor3f(1.0, 0.7, 0.0);
	glVertex3f(centerX,  (aimSize / 8),centerZ);
	glVertex3f(centerX, (aimSize / 4), centerZ);
	glEnd();


	// Eixo dos z - mira 2
	glBegin(GL_LINES);
	glColor3f(0.11, 0.56, 1.0);
	glVertex3f(centerX, -(aimSize / 8), centerZ);
	glVertex3f(centerX, -(aimSize / 4), centerZ);;
	glEnd();


	glPopMatrix();


	//draw Weapon
	//glPushMatrix(); {
	//	
	//	//Codigo para a mira Aqui
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
		glDisable(GL_CULL_FACE);


	//}glPopMatrix();

	/*draw spheare*/
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