#include "Board.h"
#include <stdio.h>
#include <GL/glut.h>


//Inicializar Dimensões do Board/(Labirinto)
const int Board::BOARD_WALL_SIZE = 1;
const int Board::BOARD_X = 30;
const int Board::BOARD_Y = 40;


//0 -> wall
//1 -> path
// Sujeito a alterações (seria mais eficiente se fosse desenhado por faces, para evitar que paredes tivessem mais faces do que o desejado)
//		Para isso é necessário colocar mais numeros para além de 0 e 1
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


Board::Board(float scale) {
	Board::scale = scale;
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



void Board::desenhaCubo() {


	GLfloat a = 0;
	GLfloat d = 1;

	GLfloat v0[3] = { a,a,a };
	GLfloat v1[3] = { d,a,a };
	GLfloat v2[3] = { d,d,a };
	GLfloat v3[3] = { a,d,a };
	GLfloat v4[3] = { a,a,d };
	GLfloat v5[3] = { d,a,d };
	GLfloat v6[3] = { d,d,d };
	GLfloat v7[3] = { a,d,d };


	GLfloat cores[][3] = { { 0.30,0.75,0.75 },
	{ 1.0,0.0,0.0 },
	{ 1.0,1.0,0.0 },
	{ 0.0,1.0,0.0 },
	{ 1.0,0.0,1.0 },
	{ 0.0,0.0,1.0 },
	{ 1.0,1.0,1.0 } };

	desenhaPoligono(v5, v6, v7, v4, cores[0]);
	desenhaPoligono(v1, v2, v6, v5, cores[0]);
	desenhaPoligono(v2, v3, v7, v6, cores[0]);
	desenhaPoligono(v1, v5, v4, v0, cores[0]);
	desenhaPoligono(v3, v0, v4, v7, cores[0]);

}



void Board::desenhaParedes() {
	
	/*
	GLint tex;
	// some init gl code here

	// the texture (2x2)
	GLbyte textureData[] = { 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 0 };
	GLsizei width = 2;
	GLsizei heigth = 2;


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	//glGenTextures(1, &amp; tex);   // generate a texture handler really reccomanded (mandatory in openGL 3.0)
	glBindTexture(GL_TEXTURE_2D, tex); // tell openGL that we are using the texture 

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, BOARD_WALL_SIZE*scale, BOARD_WALL_SIZE*scale, 0, GL_UNSIGNED_BYTE, (GLvoid*)textureData); // send the texture data
	*/
	//Divided in 2 parts to avoid depth issues

	// 1 Part
	int i, j;
	for (i = 0; i < Board::BOARD_X; i++) {
		for (j = 0; j < Board::BOARD_Y / 2; j++) {
			glColor3f(0, 0, 1);
			glPushMatrix();
			{
				glTranslatef(-(float)BOARD_X / 2.0, -(float)BOARD_Y / 2.0, 0);
				glTranslatef(i*scale, BOARD_Y - j*scale, 0);
				glPushMatrix(); {
					glTranslatef(BOARD_WALL_SIZE*scale, BOARD_WALL_SIZE*scale, 0);
					switch (board_walls[j][i]) {
					case 1:// Means there is a cube/wall there
						glPushMatrix(); {
							glScalef(BOARD_WALL_SIZE*scale, BOARD_WALL_SIZE*scale, BOARD_WALL_SIZE*scale);
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
			glPushMatrix();
			{
				glTranslatef(-(float)BOARD_X / 2.0, -(float)BOARD_Y / 2.0, 0);
				glTranslatef(i*scale, BOARD_Y - j*scale, 0);
				glPushMatrix(); {
					glTranslatef(BOARD_WALL_SIZE*scale, BOARD_WALL_SIZE*scale, 0);
					switch (board_walls[j][i]) {
					case 1:// Means there is a cube/wall there
						glPushMatrix(); {
							glScalef(BOARD_WALL_SIZE*scale, BOARD_WALL_SIZE*scale, BOARD_WALL_SIZE*scale);
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
}


//Desenha Labirinto
void Board::Draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	desenhaParedes();

	glFlush();
}


//returns whether or not the labirinth is open at the given coords
//array is transpose of how actual labirinth appears on screen
bool
Board::IsOpen(int x, int y)
{
	x /= scale;
	y /= scale;

	if (board_walls[y][x] > 0)
	{
		return false;
	}
	return true;
}

