#include "Board.h"
#include <stdio.h>
#include <GL/glut.h>


//Inicializar Dimensões do Board/(Labirinto)
const int Board::BOARD_WALL_SIZE = 1;
const int Board::BOARD_X = 30;
const int Board::BOARD_Y = 40;


//0 -> wall
//1 -> path
//3 -> key
int board_walls[Board::BOARD_Y][Board::BOARD_X] =
{ 
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
};


Board::Board() {
	//( tp_restore)
}

void Board::tp_restore(){}


// Destructor
Board::~Board(void) {}


void desenhaPoligono(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat cor[])
{
	glBegin(GL_QUADS);
	glColor3fv(cor);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(a[0], a[1], a[2]);
	glVertex3f(b[0], b[1], b[2]);
	glVertex3f(c[0], c[1], c[2]);
	glVertex3f(d[0], d[1], d[2]);
	glEnd();
}



void Board::desenhaCubo(){


	GLfloat a = 0;
	GLfloat d = 1;

	GLfloat vertice0[3] = { a,a,a };
	GLfloat vertice1[3] = { d,a,a };
	GLfloat vertice2[3] = { d,d,a };
	GLfloat vertice3[3] = { a,d,a };
	GLfloat vertice4[3] = { a,a,d };
	GLfloat vertice5[3] = { d,a,d };
	GLfloat vertice6[3] = { d,d,d };
	GLfloat vertice7[3] = { a,d,d };


	GLfloat cores[][3] = { { 0.75,0.75,0.75},
	{ 1.0,0.0,0.0 },
	{ 1.0,1.0,0.0 },
	{ 0.0,1.0,0.0 },
	{ 1.0,0.0,1.0 },
	{ 0.0,0.0,1.0 },
	{ 1.0,1.0,1.0 } };

	desenhaPoligono(vertice0, vertice3, vertice2, vertice1, cores[0]);
	desenhaPoligono(vertice1, vertice5, vertice6, vertice2, cores[0]);
	desenhaPoligono(vertice4, vertice5, vertice6, vertice7, cores[0]);
	desenhaPoligono(vertice3, vertice7, vertice4, vertice0, cores[0]);
	desenhaPoligono(vertice7, vertice6, vertice2, vertice3, cores[0]);
	desenhaPoligono(vertice4, vertice5, vertice1, vertice0, cores[0]);

}


void Board::desenhaParedes() {

	//Divided in 2 parts to avoid depth issues

	// 1 Part
	int i, j;
	for (i = 0; i < Board::BOARD_X; i++) {
		for (j = 0; j < Board::BOARD_Y / 2; j++) {
			glColor3f(0.5, 1, 1);
			glPushMatrix();
			{
				glTranslatef(-(float)BOARD_X / 2.0, -(float)BOARD_Y / 2.0, 0);
				glTranslatef(j, BOARD_Y - i, 0);
				glPushMatrix(); {
					glTranslatef(BOARD_WALL_SIZE, BOARD_WALL_SIZE, 0);
					switch (board_walls[i][j]) {
					case 1:// Means there is a cube/wall there
						glPushMatrix(); {
							Board::desenhaCubo();
						}glPopMatrix();
						break;
					case 0:
						break;
					}
				}glPopMatrix();
			}glPopMatrix();
		}
	}

	// 2 Part
	for (int i = 0; i < BOARD_X; i++)
	{
		for (int j = BOARD_Y - 1; j >= BOARD_Y/2; j--)
		{
			glColor3f(0.5, 1, 1);
			int call_this = 0;
			glPushMatrix();
			{
				glTranslatef(-(float)BOARD_X / 2.0, -(float)BOARD_Y / 2.00, 0);
				glTranslatef(j, BOARD_Y - i, 0);
				glPushMatrix();
				{
					glTranslatef(BOARD_WALL_SIZE, BOARD_WALL_SIZE, 0);
					switch (board_walls[i][j])
					{
						case 1:
							glPushMatrix(); {
								Board::desenhaCubo();
							}glPopMatrix();
							glutPostRedisplay();
							break;
						case 0:
							break;
					}

				}
				glPopMatrix();
			}
			glPopMatrix();
		}
	}
}


//Desenha Labirinto
void Board::Draw(void) {
	glColor3f(0.2, 0.2, 0.9);
	desenhaParedes();
	glutPostRedisplay();

}


//returns whether or not the labirinth is open at the given coords
//array is transpose of how actual labirinth appears on screen
bool
Board::IsOpen(int x, int y)
{
	if (board_walls[y][x] > 0)
	{
		return false;
	}
	return true;
}
