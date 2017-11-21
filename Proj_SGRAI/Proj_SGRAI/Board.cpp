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
	//create the different possible cells
	create_list_lib();
	//( tp_restore)
}

void Board::tp_restore(){}


void Board::DRAW_WALLS_NORTH(void) {
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
}

void Board::DRAW_WALLS_SOUTH(void) {
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
}

void Board::DRAW_WALLS_EAST(void) {
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
}

void Board::DRAW_WALLS_WEST(void) {
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
}

void Board::DRAW_WALLS_BOTTOM(void) {
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1, 1, 0.0);
	glVertex3f(0, 1, 0.0);
	glVertex3f(0, 0, 0.0);
	glVertex3f(1, 0, 0.0);
}

void Board::DRAW_WALLS_TOP(void) {
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1, 1, 1.0);
	glVertex3f(0, 1, 1.0);
	glVertex3f(0, 0, 1.0);
	glVertex3f(1, 0, 1.0);
}

// Destructor
Board::~Board(void) { //free(scaledWalls);
}

//	Walls:
//	N - North; S - South; E - East; W -West; T - Top; B - Bottom
//	Binary -> 0x00NSEWTB
int list_Binary[0x00111111];

#define WALLS_NORTH		64
#define WALLS_SOUTH		32
#define WALLS_EAST		16
#define WALLS_WEST		4
#define WALLS_TOP		2
#define WALLS_BOTTOM	1
#define WALLS_EMPTY		0
#define NUM_WALLS 6


void Board::create_list_lib(void)
{
	// Draw poligons instead of cubes


	list[1] = glGenLists(1);
	glNewList(list[1], GL_COMPILE);
	//north facing wall
	glBegin(GL_QUADS);
	DRAW_WALLS_NORTH();
	glEnd();
	glEndList();

	list[2] = glGenLists(1);
	glNewList(list[2], GL_COMPILE);
	glBegin(GL_QUADS);
	//north facing wall
	DRAW_WALLS_NORTH();
	//south facing wall
	DRAW_WALLS_SOUTH();
	glEnd();
	glEndList();


	list[3] = glGenLists(1);
	glNewList(list[3], GL_COMPILE);
	glBegin(GL_QUADS);
	//north facing wall
	DRAW_WALLS_NORTH();

	//east facing wall
	DRAW_WALLS_EAST();
	glEnd();
	glEndList();

	list[4] = glGenLists(1);
	glNewList(list[4], GL_COMPILE);
	glBegin(GL_QUADS);
	//top facing wall
	DRAW_WALLS_TOP();
	glEnd();
	glEndList();
}



void Board::drawWalls(void) {
	glColor3f(0.2, 0.3, 0.4);
	for (int i = 0; i < BOARD_X; i++)
	{
		for (int j = 0; j < BOARD_Y ; j++)
		{
			int aux = WALLS_BOTTOM+WALLS_TOP;
			glPushMatrix();

			glTranslatef(-(float)BOARD_X / 2.0f, -(float)BOARD_Y / 2.0f, 0);
			glTranslatef(j, BOARD_Y - i, 0);
			glPushMatrix();

			if (board_walls[i][j] == 1)
			{
				if (i - 1 >= 0) if (board_walls[i - 1][j] == 0) { aux += WALLS_NORTH; }
				if (i + 1 < BOARD_X) if (board_walls[i + 1][j] == 0) { aux += WALLS_SOUTH; }
				if (j + 1 < BOARD_Y) if (board_walls[i][j + 1] == 0) { aux += WALLS_EAST; }
				if (j - 1 >= 0) if (board_walls[i][j - 1] == 0) { aux += WALLS_WEST; }

				if (i == 0) if (board_walls[i][j] == 1) { aux += WALLS_NORTH; }
				if (i == BOARD_X-1) if (board_walls[i][j] == 1) { aux += WALLS_SOUTH; }
				if (j == BOARD_Y-1) if (board_walls[i][j] == 1) { aux += WALLS_EAST; }
				if (j == 0) if (board_walls[i][j] == 1) { aux += WALLS_WEST; }


				glBegin(GL_QUADS);
				{
					if (aux & WALLS_NORTH) {
						Board::DRAW_WALLS_NORTH();
					}
					if (aux & WALLS_SOUTH) {
						Board::DRAW_WALLS_SOUTH();
					}
					if (aux & WALLS_EAST) {
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
			}
			
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

