#include "Board.h"


//Inicializar Dimensões do Board/(Labirinto)
const float Board::BOARD_WALL_SIZE = 1.0;
const int Board::BOARD_X = 31;
const int Board::BOARD_Y = 28;


//0 -> wall
//1 -> path
// Sujeito a alterações (seria mais eficiente se fosse desenhado por faces, para evitar que paredes tivessem mais faces do que o desejado)
//		Para isso é necessário colocar mais numeros para além de 0 e 1
int board_walls[Board::BOARD_X][Board::BOARD_Y] =
{ 
{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	0,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	0,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	0,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	0,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	0,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	0,	1,	0,	0,	1,	0,	1,	1,	1,	1,	0,	0,	0,	0,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	0,	1,	1,	0,	1,	0,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	0,	1,	1,	0,	1,	0,	1,	1,	1,	1,	0,	1,	0,	0,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	0,	0,	1,	0,	1,	0,	1,	1,	1,	1,	0,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	0,	1,	0,	0,	0,	1,	1,	1,	1,	0,	1,	0,	0,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	0,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	0,	1,	0,	1,	0,	0,	1,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	0,	1,	0,	1,	1,	0,	1,	1,	0,	1,	1,	1,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	1,	0,	1,	1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	0,	1,	0,	1,	0,	0,	0,	0,	1,	1,	0,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1,	0,	1,	1,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 } };

static const int X = BOARD_SCALE_DEFAULT * Board::BOARD_X;
static const int Y = BOARD_SCALE_DEFAULT * Board::BOARD_Y;

bool firstTime = false;	


Board::Board() {
	//scaleWalls();
	ang = 0;
	//( tp_restore)
}

void Board::tp_restore(){}


void Board::DRAW_WALLS_NORTH(void) {
	glColor3f(0.2, 0.3, 0.4);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	
	
}

void Board::DRAW_WALLS_SOUTH(void) {
	glColor3f(0.2, 0.3, 0.4);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
}

void Board::DRAW_WALLS_EAST(void) {
	glColor3f(0.2, 0.3, 0.4);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 1.0, 1.0);
	glVertex3f(0.0, 1.0, 0.0);
}

void Board::DRAW_WALLS_WEST(void) {
	glColor3f(0.2, 0.3, 0.4);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 0.0, 1.0);
	glVertex3f(1.0, 0.0, 0.0);
}

void Board::DRAW_WALLS_TOP(void) {
	glColor3f(0.2, 0.3, 0.4);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1,0,1);
	glVertex3f(1,1,1);
	glVertex3f(0,1,1);
	glVertex3f(0,0,1);
}


void Board::DRAW_WALLS_BOTTOM(void) {
	glColor3f(0.2, 0.1, 0.1);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 0);
}

// Destructor
Board::~Board(void) {
}


void Board::drawWalls(void) {
	glColor3f(0.2, 0.3, 0.4);
	for (int i = 0; i < BOARD_X; i++)
	{
		for (int j = 0; j < BOARD_Y ; j++)
		{
			int aux = WALLS_BOTTOM;
			glPushMatrix();

			glTranslatef(-(float)BOARD_X / 2.0f, -(float)BOARD_Y / 2.0f, 0);
			glTranslatef(j, BOARD_Y - i, 0);
			glPushMatrix();

			if (board_walls[i][j] == 1)
			{
				aux += WALLS_TOP;
				aux -= WALLS_BOTTOM;
				if (i - 1 >= 0) if (board_walls[i - 1][j] == 0) { aux += WALLS_SOUTH; }
				if (i + 1 < BOARD_X) if (board_walls[i + 1][j] == 0) { aux += WALLS_NORTH; }
				if (j + 1 < BOARD_Y) if (board_walls[i][j + 1] == 0) { aux += WALLS_WEST; }
				if (j - 1 >= 0) if (board_walls[i][j - 1] == 0) { aux += WALLS_EAST; }

				if (!(aux & WALLS_SOUTH) && i == 0 ) if (board_walls[i][j] == 1) { aux += WALLS_SOUTH; }
				if (!(aux & WALLS_NORTH) && i == BOARD_X-1) if (board_walls[i][j] == 1) { aux += WALLS_NORTH; }
				if (!(aux & WALLS_WEST) && j == BOARD_Y-1) if (board_walls[i][j] == 1) { aux += WALLS_WEST; }
				if (!(aux & WALLS_EAST) && j == 0) if (board_walls[i][j] == 1) { aux += WALLS_EAST; }

			}
				glBegin(GL_QUADS);
				{
					if (aux & WALLS_NORTH) {
						Board::DRAW_WALLS_NORTH();
					}
					if (aux & WALLS_SOUTH) {
						Board::DRAW_WALLS_SOUTH();
					}
					if (aux & WALLS_EAST) {
						//if (DEBBUG) printf("DRAW WEST  at [%d][%d] \n", i, j);
						Board::DRAW_WALLS_EAST();
					}
					if (aux & WALLS_WEST) {
						Board::DRAW_WALLS_WEST();
					}
					if (aux & WALLS_TOP) {
						Board::DRAW_WALLS_TOP();
					}
					if (aux & WALLS_BOTTOM) {
						Board::DRAW_WALLS_BOTTOM();
					}
				}
				glEnd();
			
			
			glPopMatrix();
			
			glPopMatrix();
		}
	}
}


//Desenha Labirinto
void Board::Draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawWalls();

	glFlush();
}


//returns whether or not the labirinth is open at the given coords
//array is transpose of how actual labirinth appears on screen
bool
Board::IsOpen(int x, int y)
{	
	if (DEBBUG)printf("[%d][%d]", y, x);
	if (board_walls[y][x] > 0)
	{
		return false;
	}
	return true;
}

