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
{ { 8,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	1,	1,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	7 },	
{	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6 },	
{	6,	0,	8,	5,	1,	7,	0,	8,	1,	1,	1,	7,	0,	2,	4,	0,	8,	1,	1,	1,	7,	0,	8,	1,	1,	7,	0,	6 },	
{	6,	0,	6,	0,	11,	4,	0,	2,	11,	11,	11,	4,	0,	2,	4,	0,	2,	11,	11,	11,	4,	0,	2,	11,	11,	4,	0,	6 },	
{	6,	0,	9,	0,	3,	6,	 0,	9,	3,	3,	3,	10,	0,	9,	10,	0,	9,	3,	3,	3,	10,	0,	9,	3,	3,	10,	0,	6 },	
{	6,	0,	0,	0,	6,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	6,	0,	0,	0,	0,	0,	0,	6 },	
{	6,	0,	8,	1,	1,	6,	0,	8,	7,	0,	8,	1,	1,	1,	1,	1,	1,	7,	0,	8,	7,	0,	8,	1,	1,	7,	0,	6 },	
{	6,	0,	9,	3,	3,	10,	0,	2,	4,	0,	9,	3,	3,	11,	11,	3,	3,	10,	0,	2,	4,	0,	9,	3,	3,	10,	0,	6 },	
{	6,	0,	0,	0,	0,	0,	0,	2,	4,	0,	0,	0,	0,	2,	4,	0,	0,	0,	0,	2,	4,	0,	0,	0,	0,	0,	0,	6 },	
{	6,	5,	5,	5,	5,	7,	0,	2,	11,	1,	1,	7,	0,	2,	4,	0,	8,	1,	1,	11,	4,	0,	8,	5,	5,	5,	5,	6 },	
{	6,	0,	0,	0,	0,	6,	0,	2,	11,	3,	3,	10,	0,	9,	10,	0,	9,	3,	3,	11,	4,	0,	6,	0,	0,	0,	0,	6 },	
{	6,	0,	6,	0,	0,	6,	0,	2,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	4,	0,	6,	0,	0,	0,	0,	6 },	
{	6,	0,	6,	0,	0,	6,	0,	2,	4,	0,	8,	5,	0,	5,	5,	5,	5,	7,	0,	2,	4,	0,	6,	0,	0,	0,	0,	6 },	
{	6,	0,	9,	5,	5,	10,	0,	9,	10,	5,	6,	6,	0,	0,	0,	0,	0,	6,	0,	9,	10,	0,	9,	5,	5,	5,	5,	6 },	
{	6,	0,	0,	0,	0,	0,	0,	0,	0,	8,	6,	6,	5,	6,	6,	6,	0,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6 },	
{	6,	0,	5,	5,	5,	7,	0,	8,	7,	0,	6,	0,	0,	0,	0,	0,	0,	6,	0,	8,	7,	0,	8,	7,	0,	8,	5,	6 },	
{	6,	0,	6,	0,	0,	6,	0,	2,	4,	0,	9,	5,	5,	0,	5,	5,	5,	10,	0,	2,	4,	0,	6,	0,	0,	6,	0,	6 },	
{	6,	0,	9,	10,	0,	6,	0,	2,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	4,	0,	6,	0,	0,	6,	0,	6 },	
{	6,	0,	0,	0,	0,	6,	0,	2,	4,	0,	8,	1,	1,	1,	1,	1,	1,	7,	0,	2,	4,	0,	6,	0,	0,	6,	0,	6 },	
{	6,	5,	5,	5,	5,	10,	0,	9,	10,	0,	9,	3,	3,	11,	11,	3,	3,	10,	0,	9,	10,	0,	9,	10,	0,	9,	5,	6 },	
{	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6 },	
{	6,	0,	8,	1,	1,	7,	0,	8,	1,	1,	1,	7,	0,	2,	4,	0,	8,	1,	1,	1,	7,	0,	8,	1,	1,	7,	0,	6 },	
{	6,	0,	9,	3,	11,	4,	0,	9,	3,	3,	3,	10,	0,	9,	10,	0,	9,	3,	3,	3,	10,	0,	2,	11,	3,	10,	0,	6 },	
{	6,	0,	0,	0,	2,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	4,	0,	0,	0,	6 },	
{	2,	1,	7,	0,	2,	4,	0,	8,	7,	0,	8,	1,	1,	1,	1,	1,	1,	7,	0,	8,	7,	0,	2,	4,	0,	8,	1,	4 },	
{	2,	3,	10,	0,	9,	10,	0,	2,	4,	0,	9,	3,	3,	11,	11,	3,	3,	10,	0,	2,	4,	0,	9,	10,	0,	9,	3,	4 },	
{	6,	0,	0,	0,	0,	0,	0,	2,	4,	0,	0,	0,	0,	2,	4,	0,	0,	0,	0,	2,	4,	0,	0,	0,	0,	0,	0,	6 },	
{	6,	0,	8,	1,	1,	1,	1,	11,	11,	1,	1,	7,	0,	2,	4,	0,	8,	1,	1,	11,	11,	1,	1,	1,	1,	7,	0,	6 },	
{	6,	0,	9,	3,	3,	3,	3,	3,	3,	3,	3,	10,	0,	9,	10,	0,	9,	3,	3,	3,	3,	3,	3,	3,	3,	10,	0,	6 },	
{	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	6 },	
{	9,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	10 } };

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


// Destructor
Board::~Board(void) { //free(scaledWalls);
}

void Board::create_list_lib(void)
{
	// Draw poligons instead of cubes
	list[1] = glGenLists(1);
	glNewList(list[1], GL_COMPILE);
	//north facing wall
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glEnd();
	glEndList();

	list[2] = glGenLists(1);
	glNewList(list[2], GL_COMPILE);
	glBegin(GL_QUADS);
	//north facing wall
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);

	//south facing wall
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glEndList();

	list[3] = glGenLists(1);
	glNewList(list[3], GL_COMPILE);
	glBegin(GL_QUADS);
	//north facing wall
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);

	//east facing wall
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
	glEndList();

	list[4] = glGenLists(1);
	glNewList(list[4], GL_COMPILE);
	glBegin(GL_QUADS);
	//top facing wall
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1, 1, 1.0);
	glVertex3f(0, 1, 1.0);
	glVertex3f(0, 0, 1.0);
	glVertex3f(1, 0, 1.0);
	glEnd();
	glEndList();
}


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

void Board::drawWalls(void) {
	glColor3f(0.2, 0.3, 0.4);
	for (int i = 0; i < BOARD_X; i++)
	{
		for (int j = 0; j < BOARD_Y ; j++)
		{
			int call_this = 0;
			glPushMatrix();

			glTranslatef(-(float)BOARD_X / 2.0f, -(float)BOARD_Y / 2.0f, 0);
			glTranslatef(j, BOARD_Y - i, 0);
			glPushMatrix();
			glTranslatef(0.5, 0.5, 0);
			switch (board_walls[i][j])
			{
			case 4:
				glRotatef(90.0, 0, 0, 1);
			case 3:
				glRotatef(90.0, 0, 0, 1);
			case 2:
				glRotatef(90.0, 0, 0, 1);
			case 1:
				call_this = 1;
				break;
			case 6:
				glRotatef(90.0, 0, 0, 1);
			case 5:
				call_this = 2;
				break;
			case 10:
				glRotatef(90.0, 0, 0, 1);
			case 9:
				glRotatef(90.0, 0, 0, 1);
			case 8:
				glRotatef(90.0, 0, 0, 1);
			case 7:
				call_this = 3;
				break;
			}
			glScalef(1, 1, 0.5);
			glTranslatef(-0.5, -0.5, 0);
			glCallList(list[call_this]);
			glPopMatrix();
			//now put on the top of the cell
			if (call_this != 0 || board_walls[i][j] == 11)
			{
				glTranslatef(0, 0, -0.5);
				glCallList(list[4]);
			}
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

