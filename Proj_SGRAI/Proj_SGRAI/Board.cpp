#include "Board.h"


//Inicializar Dimensões do Board/(Labirinto)
const float Board::BOARD_WALL_SIZE = 1.0;
const int Board::BOARD_X = 8;
const int Board::BOARD_Y = 8;


//0 -> wall
//1 -> path
// Sujeito a alterações (seria mais eficiente se fosse desenhado por faces, para evitar que paredes tivessem mais faces do que o desejado)
//		Para isso é necessário colocar mais numeros para além de 0 e 1
int board_walls[Board::BOARD_X][Board::BOARD_Y] =
{ 
	{ 1,1,1,1,1,1,1,1},
	{ 1,0,0,0,0,0,0,1},
	{ 1,0,1,1,1,1,0,1},
	{ 1,0,1,0,0,1,0,1},
	{ 1,0,1,0,0,1,0,1},
	{ 1,0,1,0,0,1,0,1},
	{ 1,0,0,0,0,0,0,1},
	{ 1,1,1,1,1,1,1,1}
	};


static const int X = BOARD_SCALE_DEFAULT * Board::BOARD_X;
static const int Y = BOARD_SCALE_DEFAULT * Board::BOARD_Y;

int** scaledWalls;

bool firstTime = true;
void Board::scaleWalls() {

	scaledWalls = (int**) calloc(X, sizeof(Y));

	if (scaledWalls == NULL  && DEBBUG) {
		printf("NULL");
	}
	else {
		for (int i = 0; i < X; i++) {
			scaledWalls[i] = (int*)calloc(Y, sizeof(X));
			if (scaledWalls[0] == NULL  && DEBBUG) {
				printf("NULL");
			}
		}


		for (int j = 0; j < Y; j++) {
			for (int i = 0; i < X; i++) {
				scaledWalls[i][j] = 0;
			}
		}



		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
					scaledWalls[i][j] = board_walls[(i/2)][(j/2)];
					if(firstTime && DEBBUG)printf("[%d][%d] = %d\n", i, j, board_walls[i/2-1][j/2-1]);
			
			}
		}
	if (firstTime && DEBBUG) {
		printf("+-------------------+\n");
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				printf(" %d ", scaledWalls[i][j]);
			}
			printf("\n");
		}
	}
		firstTime = false;
	}
}


Board::Board() {
	scaleWalls();
	ang = 0;
	//( tp_restore)
}

void Board::tp_restore(){}


// Destructor
Board::~Board(void) { free(scaledWalls); }


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


	GLfloat a = BOARD_WALL_SIZE/2;
	GLfloat d = -a;

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
	desenhaPoligono(v2, v3, v7, v6, cores[1]);
	desenhaPoligono(v1, v5, v4, v0, cores[1]);
	desenhaPoligono(v3, v0, v4, v7, cores[1]);

}



void Board::desenhaParedes() {
	

	int i, j;
	glColor3f(0, 0, 1);
	glPushMatrix();
	{glRotatef(ang, 0, 0, 1);
		glTranslatef(0, 0, 0);
		
			for (i = 0; i < X; i++) {
				for (j = 0; j < Y ; j++) {
					glPushMatrix();
					{
						glTranslatef(-(float)X / 2.0f, -(float)Y / 2.0f, 0);
						//glTranslatef(j*BOARD_SCALE_DEFAULT, Y - i*BOARD_SCALE_DEFAULT, 0);

						glTranslatef(i*BOARD_SCALE_DEFAULT*BOARD_WALL_SIZE, -j*BOARD_SCALE_DEFAULT*BOARD_WALL_SIZE, 0);
						glPushMatrix(); {
							glTranslatef(BOARD_SCALE_DEFAULT, 0.5*BOARD_SCALE_DEFAULT, 0);

							switch (scaledWalls[j][i]) {
							case 1:// Means there is a cube/wall there

								glPushMatrix(); {
									glScalef(BOARD_WALL_SIZE*BOARD_SCALE_DEFAULT, BOARD_WALL_SIZE*BOARD_SCALE_DEFAULT, BOARD_WALL_SIZE*BOARD_SCALE_DEFAULT);
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

	}glPopMatrix();
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
	if (DEBBUG)printf("[%d][%d]", x, y);
	if (scaledWalls[x][y] > 0)
	{
		return false;
	}
	return true;
}

