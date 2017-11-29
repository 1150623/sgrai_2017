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
		glTranslatef(Monster::x, -Monster::y + size * 2, -size);
		glTranslatef(size / 2, size + 0.1, 0);
		glTranslatef((float)Board::BOARD_X / -2.0, (float)Board::BOARD_Y / 2.0, 0.5);
		glutSolidSphere(size / 2, 10, 10);
	}
	glPopMatrix();
}


void Monster::GenerateRandoMonsters(Board boards)
{
	struct Vec2ii
	{
		int x, y;
	};

	//Conta o numero de possiçoes onde e possivel adicionar monstro
	int numeroPosPossivelCriarMonstro = 0;
	int i;
	int j;
	for (i = 0; i < boards.BOARD_X; i++){
		for (j = 0; j < boards.BOARD_Y; j++){
			if (board_walls[i][j] == 0){
				numeroPosPossivelCriarMonstro++;
				}
		}
	}

	//Adiciona as coordenadas onde e possivel adicionar monstros a um vector
	std::vector<Vec2ii> vectorTeste(numeroPosPossivelCriarMonstro, {0,0});
	for (int i = 0; i < boards.BOARD_X; i++)
	{
		for (int j = 0; j < boards.BOARD_Y; j++)
		{
			if (board_walls[i][j] == 0) {
				vectorTeste.insert(vectorTeste.begin(),{i,j});
			}
		}
	}

	//Gera um numero Random que vai selecionar a possicao onde vai nascer os monstros
	srand(time(NULL));
	for (int k = 0; k < NUM_MONSTROS_RANDOM; k++)
	{
		int x = rand()%vectorTeste.size();
		// Valor na matriz para a existencia de monstros
		board_walls[vectorTeste[x].x][vectorTeste[x].y] = 3;
		VecPositionMonsters.push_back(savePositionMonsters());
		VecPositionMonsters[k].x = vectorTeste[x].x;
		VecPositionMonsters[k].y = vectorTeste[x].y;
		vectorTeste.erase(vectorTeste.begin() + x);

	}

		
}
