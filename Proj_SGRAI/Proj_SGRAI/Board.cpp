#include "Board.h"


//Inicializar Dimensões do Board/(Labirinto)
const float Board::BOARD_WALL_SIZE = 1.0;


GLbyte image[2][2][2];
GLuint imageWidth = 1, imageHeight = 1;

//0 -> wall
//1 -> path
// Sujeito a alterações (seria mais eficiente se fosse desenhado por faces, para evitar que paredes tivessem mais faces do que o desejado)
//		Para isso é necessário colocar mais numeros para além de 0 e 1
int board_walls[Board::BOARD_X][Board::BOARD_Y] =
{ 
{	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	5,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
{	1,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1 },
{	1,	1,	1,	0,	1,	1,	0,	1,	0,	1,	0,	0,	0,	0,	1,	1,	1,	0,	1,	1,	1,	1,	0,	0,	0,	0,	1,	1 },
{	1,	1,	1,	0,	1,	1,	0,	1,	0,	0,	1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	0,	0,	1,	1,	1,	0,	1,	1 },
{	1,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	1,	0,	0,	0,	0,	0,	1,	1 },
{	1,	1,	1,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	1,	0,	1,	1,	0,	0,	1 },
{	1,	1,	1,	0,	1,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	0,	1,	0,	1,	0,	0,	1,	0,	0,	1,	1,	1,	1 },
{	1,	0,	1,	0,	0,	1,	0,	1,	0,	1,	1,	0,	0,	0,	0,	0,	1,	0,	1,	1,	0,	1,	1,	1,	0,	0,	0,	1 },
{	1,	0,	1,	1,	0,	1,	0,	1,	0,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	0,	0,	0,	0,	0,	1,	0,	1 },
{	1,	0,	1,	1,	0,	1,	0,	1,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1 },
{	1,	0,	0,	1,	0,	1,	0,	1,	0,	1,	1,	0,	1,	0,	1,	1,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1 },
{	1,	1,	0,	1,	0,	0,	0,	1,	0,	1,	1,	0,	1,	0,	0,	1,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	0,	1 },
{	1,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	1 },
{	1,	1,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1 },
{	1,	1,	1,	0,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	1 },
{	1,	0,	1,	1,	0,	1,	0,	1,	0,	0,	1,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	0,	0,	0,	1,	0,	1,	1 },
{	1,	0,	1,	1,	0,	1,	0,	1,	1,	0,	1,	1,	0,	1,	1,	1,	0,	0,	0,	0,	0,	1,	1,	1,	1,	0,	1,	1 },
{	1,	0,	0,	1,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	0,	1,	1,	1,	1,	0,	1,	1 },
{	1,	1,	0,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	0,	0,	0,	1,	1 },
{	1,	0,	0,	0,	0,	0,	1,	1,	0,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	1,	0,	1,	1,	0,	1,	0,	1,	1 },
{	1,	0,	1,	1,	1,	0,	1,	0,	0,	0,	1,	0,	1,	1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	0,	1,	0,	1,	1 },
{	1,	0,	1,	1,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	0,	1,	1,	0,	0,	1,	0,	1,	1,	0,	1,	0,	1,	1 },
{	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	1,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	0,	1,	1 },
{	1,	0,	1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1,	0,	1,	1,	0,	0,	0,	0,	1,	1,	0,	1,	0,	1,	1 },
{	1,	0,	1,	0,	1,	1,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	1,	1,	0,	1,	1,	1,	1,	0,	1,	0,	1,	1 },
{	1,	0,	1,	0,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,	1 },
{	1,	0,	0,	0,	0,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	0,	1,	1,	1,	0,	1,	1 },
{	1,	1,	0,	1,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	1 },
{	1,	1,	0,	1,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	0,	1,	1,	0,	1,	1,	1,	1 },
{	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	1 },
{	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	5,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 } 
};

static const int X = BOARD_SCALE_DEFAULT * Board::BOARD_X;
static const int Y = BOARD_SCALE_DEFAULT * Board::BOARD_Y;

bool firstTime = false;	



typedef float vertex[3];

vertex vertices[] = {
	{ 0, 0, 1},//0 (first 8 verticies for cube)
	{ 0, 1, 1},//1
	{ 1, 1, 1},//2
	{ 1, 0, 1},//3
	{ 0, 0, 0},//4
	{ 0, 1, 0},//5
	{ 1, 1, 0},//6
	{ 1, 0, 0},//7
	{ -3 / 28,	-13 / 28, 	0.5 },//8 (start door) bottom left
	{ 3 / 28,		-13 / 28,        0.5 },//9	bottom right
	{ 3 / 28,	  0,	0.5 },//10   top right
	{ -3 / 28,0,	0.5 } }//11   top left
;


static GLfloat theta[] = { 0.0,0.0,0.0 };


void Board::face(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glNormal3fv(vertices[a]);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void Board::MYcube(void)
{
	glColor3f(1.0, 0.0, 0.0);         //red),
	face(0, 3, 2, 1);
	glColor3f(0.0, 1.0, 0.0);         //green),
	face(4, 5, 6, 7);
	glColor3f(0.0, 0.75388, 1.0);      //blue), 
	face(5, 1, 2, 6);
	glColor3f(1.0, 0.2, 0.7);       //deep pink),
	face(4, 7, 3, 0);
	glColor3f(1.0, 1.0, 0.0);     // yellow), 
	face(2, 3, 7, 6);
	glColor3f(1.0, 0.75, 0.0);     // orange).
	face(5, 4, 0, 1);
	glColor3f(0.0, 0.0, 0.0);         //red),
	face(8, 9, 10, 11);
}







Board::Board() {
	//scaleWalls();
	ang = 0;
	loadTextures();
	//( tp_restore)
}

void Board::tp_restore(){}
	GLuint textName;
void Board::loadTextures(void) {
	if (TEXTURE_ON) {
		// 1 -activar texturas 
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glEnable(GL_TEXTURE_2D);
		// 2 –configurar aspectos gerais de texturas
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		// 3 -criar objecto textura

		glGenTextures(1, &textName);
		// 4 -activar textura 
		glBindTexture(GL_TEXTURE_2D, textName);
		// 5 -configurar textura 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	}
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_DEPTH_TEST);

}

void Board::DRAW_WALLS_NORTH(void) {
	glColor3f(0.2, 0.3, 0.4);
	glNormal3f(0.0f, -1.0f, 0.0f);
	if (TEXTURE_ON)glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	if (TEXTURE_ON)glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0f, 0.0f, 0.0f);
	if (TEXTURE_ON)glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0f, 0.0f, 1.0f);
	if (TEXTURE_ON)glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.0f, 1.0f);
	
	
}

void Board::DRAW_WALLS_SOUTH(void) {
	glColor3f(0.2, 0.3, 0.4);
	glNormal3f(0.0f, 1.0f, 0.0f);
	if (TEXTURE_ON)glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, 1.0f, 0.0f);
	if (TEXTURE_ON)glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 1.0f, 0.0f);
	if (TEXTURE_ON)glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 1.0f, 1.0f);
	if (TEXTURE_ON)glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
}

void Board::DRAW_WALLS_EAST(void) {
	glColor3f(0.2, 0.3, 0.4);
	glNormal3f(0.0f, 1.0f, 0.0f);
	if (TEXTURE_ON)glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	if (TEXTURE_ON)glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, 1.0);
	if (TEXTURE_ON)glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 1.0, 1.0);
	if (TEXTURE_ON)glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
}

void Board::DRAW_WALLS_WEST(void) {
	glColor3f(0.2, 0.3, 0.4);
	glNormal3f(0.0f, -1.0f, 0.0f);
	if (TEXTURE_ON)glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0, 1.0, 0.0);
	if (TEXTURE_ON)glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	if (TEXTURE_ON)glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 0.0, 1.0);
	if (TEXTURE_ON)glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
}

void Board::DRAW_WALLS_TOP(void) {
	glColor3f(0.2, 0.3, 0.4);
	glNormal3f(0.0f, 0.0f, 1.0f);
	if (TEXTURE_ON)glTexCoord2f(0.0, 0.0);
	glVertex3f(1,0,1);
	if (TEXTURE_ON)glTexCoord2f(0.0, 1.0);
	glVertex3f(1,1,1);
	if (TEXTURE_ON)glTexCoord2f(1.0, 1.0);
	glVertex3f(0,1,1);
	if (TEXTURE_ON)glTexCoord2f(1.0, 0.0);
	glVertex3f(0,0,1);
}


void Board::DRAW_WALLS_BOTTOM(void) {

	glColor3f(0.2, 0.1, 0.1);
	glNormal3f(0.0f, 0.0f, 1.0f);
	if (TEXTURE_ON)glTexCoord2f(0.0, 0.0);
	glVertex3f(1, 0, 0);
	if (TEXTURE_ON)glTexCoord2f(0.0, 1.0);
	glVertex3f(1, 1, 0);
	if (TEXTURE_ON)glTexCoord2f(1.0, 1.0);
	glVertex3f(0, 1, 0);
	if (TEXTURE_ON)glTexCoord2f(1.0, 0.0);
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
				if (i - 1 >= 0) if (board_walls[i - 1][j] == 0 || board_walls[i - 1][j] == 5) { aux += WALLS_SOUTH; }
				if (i + 1 < BOARD_X) if (board_walls[i + 1][j] == 0 || board_walls[i + 1][j] == 5) { aux += WALLS_NORTH; }
				if (j + 1 < BOARD_Y) if (board_walls[i][j + 1] == 0 || board_walls[i][j + 1] == 5) { aux += WALLS_WEST; }
				if (j - 1 >= 0) if (board_walls[i][j - 1] == 0 || board_walls[i][j - 1] == 5) { aux += WALLS_EAST; }

				if (!(aux & WALLS_SOUTH) && i == 0 ) if (board_walls[i][j] == 1) { aux += WALLS_SOUTH; }
				if (!(aux & WALLS_NORTH) && i == BOARD_X-1) if (board_walls[i][j] == 1) { aux += WALLS_NORTH; }
				if (!(aux & WALLS_WEST) && j == BOARD_Y-1) if (board_walls[i][j] == 1) { aux += WALLS_WEST; }
				if (!(aux & WALLS_EAST) && j == 0) if (board_walls[i][j] == 1) { aux += WALLS_EAST; }
				
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, &image[0][0][0]);
				
			}
			else {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, &image[1][1][1]);
			}

			if (board_walls[i][j] == 5) {
				aux += Board::DRAW_DOOR;
			}


			// activar textura 
			if(TEXTURE_ON)glBindTexture(GL_TEXTURE_2D, textName);
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
					if (aux & DRAW_DOOR) {
						Board::MYcube();
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
	//if (DEBBUG)printf("[%d][%d]", y, x);
	if (board_walls[y][x] > 0)
	{
		return false;
	}
	return true;
}


bool
Board::IsDoor(int x, int y)
{
	return board_walls[y][x] == 5;
}

void
Board::OpenDoor(int x, int y)
{
	board_walls[y][x] = 0;
}

