#include "Monster.h"
#include <stdio.h>
#include <GL/glut.h>
#include <Math.h>

// Destructor
Monster::~Monster(void) {}

//Constructor (inicializa)
Monster::Monster(double tx, double ty, float size, int IndexMonster,Board* b)
{
	mdlviewer_init("elite.mdl", model);
	model.SetSequence(4);
	killed = false;
	Monster::boards = b;
	Monster::size = size;
	lives = MONSTER_LIFE;
	x = tx + 0.5;
	y = ty+ 0.5;
	speed = MONSTER_SPEED;
	animate = false;
	startIndexMonster = IndexMonster;
	initDirection(IndexMonster); //verifica na matrix a direção que tem de seguir
	patrol = true;
	melee = false;
	shooting = false;
}

void Monster::Draw(void)
{
	
	//draw current Character

	glPushMatrix(); {
		glTranslatef(Monster::x, Monster::y, size + 0.095);
		glRotatef(angle, 0, 0, 1);
		glPushMatrix();
		{
			glColor3f(1.0, 0.25, 0.25);
			glScalef(SCALE_PLAYER + 0.005, SCALE_PLAYER + 0.005, SCALE_PLAYER + 0.005);
			mdlviewer_display(model);
			//glutSolidSphere(size / 2, 10, 10);
		}glPopMatrix();

		glTranslatef(0, 0, size + 0.2);

		glPushMatrix();
		{
			glColor3f(0.0, 1.0, 0.0);
			glScaled(0.05, 0.3, 0.05);
			desenhaCubo();
			//glutSolidSphere(size / 2, 10, 10);
		}glPopMatrix();
	}glPopMatrix();
}


void Monster::initDirection(int startIndexMonster) {
	int x = boards->VecPositionMonsters[startIndexMonster].linha;
	int y = boards->VecPositionMonsters[startIndexMonster].coluna;
	//maisX
	int cima = boards->getBoardValue(x + 1, y);
	int baixo = boards->getBoardValue(x - 1, y);
	int esquerda = boards->getBoardValue(x, y + 1);
	int direita = boards->getBoardValue(x, y - 1);


	if (esquerda == (startIndexMonster + BASE_INDEX_MONSTERS)) {
		angle= 0;
	}
	else if (direita == (startIndexMonster + BASE_INDEX_MONSTERS)) {
		angle = 180;
	}
	else if (cima == (startIndexMonster + BASE_INDEX_MONSTERS)) {
		angle = 90;
	}
	else if (baixo == (startIndexMonster + BASE_INDEX_MONSTERS)) {
		angle = 270;
	}
	else {
		angle = -1;
	}
}

int Monster::alert(float c_y, float c_x) {
	float dist = sqrt(pow(c_x - x, 2) + pow(c_y - y, 2));
	printf("Monster [%d] -> dist = %.3f\n", startIndexMonster,dist);
	if (dist < MONSTER_SHOOT_DIST) {
		if (dist < MONSTER_MELEE_DIST) {
			//MELEE
			melee = true;
			shooting = false;
			patrol = false;
			return 1;
		}
		else {
			//SHOOT
			melee = false;
			shooting = true;
			patrol = false;
			return 2;
		}
	}
	else {
		melee = false;
		shooting = false;
		patrol = true;
		return 0;
	}

}

void Monster::updateShootingAngle(float c_x, float c_y) {

	if (shooting) {
		if (angle == 0) {
			if (c_x > x && (c_y+0.5 >= y && c_y -0.5 <=y)) {
				shootingAngle = 0;
			}
			else {
				shootingAngle = 180;
			}
		}
		else if (angle == 180) {
			if (c_x < x && (c_y + 0.5 >= y && c_y - 0.5 <= y)) {
				shootingAngle = 180;
			}
			else {
				shootingAngle = 0;
			}
		}
		else if (angle == 90) {
			if (c_y > y && (c_x + 0.5 >= x && c_x - 0.5 <= x)) {
				shootingAngle = 90;
			}
			else {
				shootingAngle = 270;
			}
		}
		else if (angle == 270) {
			if (c_y < y && (c_x + 0.5 >= x && c_x - 0.5 <= x)) {
				shootingAngle = 270;
			}
			else {
				shootingAngle = 90;
			}
		}
	}
}

void Monster::shoot(float c_x, float c_y) {
	
	if (shooting) {
		updateShootingAngle(c_x, c_y);
		bullet = new Bullet();
		bullet->setInitial(x, y, shootingAngle, 0);
	}
}

void Monster::MoveTo() {
	if (patrol) {

		if (angle == 180) {
			//baixo
			if (!boards->IsOpen2(x - speed, y, (startIndexMonster + BASE_INDEX_MONSTERS))) {
				angle -= 180;
			}
			else
				if (boards->IsOpen2(x - speed, y, (startIndexMonster + BASE_INDEX_MONSTERS)))
					x -= speed;
		}
		else if (angle == 90) {
			//esquerda
			if (!boards->IsOpen2(x, y + speed, (startIndexMonster + BASE_INDEX_MONSTERS))) {
				angle += 180;
			}
			else
				if (boards->IsOpen2(x, y + speed, (startIndexMonster + BASE_INDEX_MONSTERS)))
					y += speed;
		}
		else if (angle == 0) {
			//CIMA
			if (!boards->IsOpen2(x + speed, y, (startIndexMonster + BASE_INDEX_MONSTERS))) {
				angle += 180;
			}
			else
				if (boards->IsOpen2(x + speed, y, (startIndexMonster + BASE_INDEX_MONSTERS)))
					x += speed;

		}
		else if (angle == 270) {
			//direita
			if (!boards->IsOpen2(x, y - speed, (startIndexMonster + BASE_INDEX_MONSTERS))) {
				angle -= 180;
			}
			else
				if (boards->IsOpen2(x, y - speed, (startIndexMonster + BASE_INDEX_MONSTERS))) {
					y -= speed;
				}
		}
		else {


		}
	}
}



void Monster::desenhaPoligono(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[])
{

	glBegin(GL_POLYGON);
	glNormal3fv(normal);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
}

void Monster::desenhaCubo()
{
	GLfloat vertices[][3] = { { -0.3,-0.3,-0.3 },
	{ 0.3,-0.3,-0.3 },
	{ 0.3,0.3,-0.3 },
	{ -0.3,0.3,-0.3 },
	{ -0.3,-0.3,0.3 },
	{ 0.3,-0.3,0.3 },
	{ 0.3,0.3,0.3 },
	{ -0.3,0.3,0.3 } };

	GLfloat normais[][3] = { { 0,0,-1 },
	{ 0,1,0 },
	{ -1,0,0 },
	{ 1,0,0 },
	{ 0,0,1 },
	{ 0,-1,0 }
	};


	desenhaPoligono(vertices[1], vertices[0], vertices[3], vertices[2], normais[0]);
	desenhaPoligono(vertices[2], vertices[3], vertices[7], vertices[6], normais[1]);
	desenhaPoligono(vertices[3], vertices[0], vertices[4], vertices[7], normais[2]);
	desenhaPoligono(vertices[6], vertices[5], vertices[1], vertices[2], normais[3]);
	desenhaPoligono(vertices[4], vertices[5], vertices[6], vertices[7], normais[4]);
	desenhaPoligono(vertices[5], vertices[4], vertices[0], vertices[1], normais[5]);

	//glBindTexture(GL_TEXTURE_2D, 0);
}
