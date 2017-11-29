#include "Board.h"

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

using namespace AStar;
Generator generator;

Board::Board() {
	
	initAStarGenerator();
	

}

void Board::initAStarGenerator() {

	generator.setWorldSize({ BOARD_X, BOARD_Y });
	generator.setHeuristic(AStar::Heuristic::manhattan);
	generator.setDiagonalMovement(false);

}


void Board::tp_restore(){}

typedef struct {
	int sizeX, sizeY;
	char *data;
} PPMImage;

extern "C" PPMImage *LoadPPM(char * path) {
	PPMImage* result = new PPMImage;
	result->sizeX = 128;
	result->sizeY = 128;
	result->data = SAIL_load_image(path, &result->sizeX, &result->sizeY);

	return result;
};

void Board::loadTextures(void) {
 
	if (TEXTURE_ON) {

		
		//LOAD WALL TEXTURE
		// START
		{
			PPMImage *imagemPPM;
			imagemPPM = LoadPPM(textureWall);
			glBindTexture(GL_TEXTURE_2D, textName[0]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagemPPM->sizeX, imagemPPM->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemPPM->data);
			free(imagemPPM); // the GPU already has the image

			//glBindTexture(GL_TEXTURE_2D, textName[0]);


			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		// END
		
		//LOAD FLOOR TEXTURE
		// START
		{
			PPMImage *imagemPPM2;
			imagemPPM2 = LoadPPM(textureFloor);
			glBindTexture(GL_TEXTURE_2D, textName[1]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagemPPM2->sizeX, imagemPPM2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemPPM2->data);
			free(imagemPPM2); // the GPU already has the image

			//glBindTexture(GL_TEXTURE_2D, textName[1]);


			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		// END
	}
}

void Board::DRAW_WALLS_NORTH(void) {
	if (!TEXTURE_ON) {
		glColor3f(0.2, 0.3, 0.4);
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	glNormal3f(-1.0f, 0.0f, 0.0f);
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
	if (!TEXTURE_ON) {
		glColor3f(0.2, 0.3, 0.4);
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	glNormal3f(1.0f, 0.0f, 0.0f);
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
	if (!TEXTURE_ON) {
		glColor3f(0.2, 0.3, 0.4);
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	glNormal3f(0.0f, -1.0f, 0.0f);
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
	if (!TEXTURE_ON) {
		glColor3f(0.2, 0.3, 0.4);
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	glNormal3f(0.0f, 1.0f, 0.0f);
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
	if (!TEXTURE_ON) {
		glColor3f(0.2, 0.3, 0.4);
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	
	glNormal3f(0.0f, 0.0f, 1.0);
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

	if (!TEXTURE_ON) {
		glColor3f(0.2, 0.1, 0.1);
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);
	}
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
Board::~Board(void) {}



void Board::drawWalls(void) {
	
	for (int i = 0; i < BOARD_X; i++)
	{
		for (int j = 0; j < BOARD_Y ; j++)
		{
			int aux = WALLS_BOTTOM;
			glPushMatrix(); 
			{

				glTranslatef(-(float)BOARD_X / 2.0f, -(float)BOARD_Y / 2.0f, 0);
				glTranslatef(j, BOARD_Y - i, 0);
				
				glPushMatrix(); 
				{

					if (board_walls[i][j] == 1)
					{
						aux += WALLS_TOP;
						aux -= WALLS_BOTTOM;
						if (i - 1 >= 0) if (board_walls[i - 1][j] == 0 || board_walls[i - 1][j] >= BASE_INDEX_MONSTERS || board_walls[i - 1][j] == 5) { aux += WALLS_SOUTH; }
						if (i + 1 < BOARD_X) if (board_walls[i + 1][j] == 0 || board_walls[i + 1][j] >= BASE_INDEX_MONSTERS || board_walls[i + 1][j] == 5) { aux += WALLS_NORTH; }
						if (j + 1 < BOARD_Y) if (board_walls[i][j + 1] == 0 || board_walls[i][j + 1] >= BASE_INDEX_MONSTERS || board_walls[i][j + 1] == 5) { aux += WALLS_WEST; }
						if (j - 1 >= 0) if (board_walls[i][j - 1] == 0 || board_walls[i][j - 1] >= BASE_INDEX_MONSTERS || board_walls[i][j - 1] == 5) { aux += WALLS_EAST; }

						if (!(aux & WALLS_SOUTH) && i == 0) if (board_walls[i][j] == 1) { aux += WALLS_SOUTH; }
						if (!(aux & WALLS_NORTH) && i == BOARD_X - 1) if (board_walls[i][j] == 1) { aux += WALLS_NORTH; }
						if (!(aux & WALLS_WEST) && j == BOARD_Y - 1) if (board_walls[i][j] == 1) { aux += WALLS_WEST; }
						if (!(aux & WALLS_EAST) && j == 0) if (board_walls[i][j] == 1) { aux += WALLS_EAST; }
						if (TEXTURE_ON) glBindTexture(GL_TEXTURE_2D, textName[0]);
					}
					else {
						if (TEXTURE_ON) glBindTexture(GL_TEXTURE_2D, textName[1]);
					}

					if (board_walls[i][j] == 5) {
						aux += Board::DRAW_DOOR;
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
							glBindTexture(GL_TEXTURE_2D, 0);
							Board::MYcube();
						}
					}
					glEnd();

					glBindTexture(GL_TEXTURE_2D, 0);

				}
				glPopMatrix();

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

struct Coord
{
	int x, y;
};

//returns whether or not the labirinth is open at the given coords
//array is transpose of how actual labirinth appears on screen
bool
Board::IsOpen(float x, float y)
{	
	Coord charcacter = {x, y};

	Coord parede;
	for (int i = x-10; i > x+10 ; i++) {
		if (i >= 0 && i < BOARD_Y)
		for (int j = y-10; j < y+10; j++) {
			if(j >= 0 && j < BOARD_X)
			if (board_walls[j][i] == 1) {
				//parede = Board::getCoordOfWall(j,i);
				//parede = { j,i };

			}
		}
	}

	//if (DEBBUG)printf("[%d][%d]", y, x);
	if (board_walls[(int)y][(int)x] > 0)
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

AStar::CoordList Board::getPath(int x, int y, int xF, int yF) {
	return generator.findPath({ x, y }, { xF, yF });
}


void Board::makeWall(int x, int y) {

	board_walls[y][x] = 1;

}

// Gera monstros aleatorios no mapa
void Board::GenerateRandoMonstersPositions(void)
{
	struct Vec2ii
	{
		int x, y;
	};

	//Conta o numero de possiçoes onde e possivel adicionar monstro
	int numeroPosPossivelCriarMonstro = 0;
	int i;
	int j;
	for (i = 0; i <Board::BOARD_X; i++) {
		for (j = 0; j < Board::BOARD_Y; j++) {
			if (board_walls[i][j] == 0) {
				numeroPosPossivelCriarMonstro++;
			}
		}
	}

	//Adiciona as coordenadas onde e possivel adicionar monstros a um vector
	std::vector<Vec2ii> vectorTeste;
	for (int i = 0; i < Board::BOARD_X; i++)
	{
		for (int j = 0; j < Board::BOARD_Y; j++)
		{
			if (board_walls[i][j] == 0) {
				Vec2ii v = { i,j };
				vectorTeste.insert(vectorTeste.begin(), v);
			}
		}
	}

	for (i = 0; i < Board::BOARD_X; i++) {
		for (j = 0; j < Board::BOARD_Y; j++) {
			printf(" %2d ", board_walls[i][j]);
		}
		printf("\n");
	}

	printf("-------------------------------------------------------------------------------------------------------\n");

	//Gera um numero Random que vai selecionar a possicao onde vai nascer os monstros
	srand(time(NULL));
	for (int k = 0; k < NUM_MONSTROS_RANDOM; k++)
	{
		int x = rand() % vectorTeste.size();

		// Valor na matriz para a existencia de monstros
		VecPositionMonsters.push_back(savePositionMonsters());
		VecPositionMonsters[k].x = vectorTeste[x].x;
		VecPositionMonsters[k].y = vectorTeste[x].y;

		int maisX = 0;
		int menosX = 0;
		int maisY = 0;
		int menosY = 0;

		// maisX
		int aumentaX = vectorTeste[x].x;
		while(board_walls[aumentaX][vectorTeste[x].y] ==0){
			maisX++;
			aumentaX++;
		}
		// menosX
		int diminuiX = vectorTeste[x].x;
		while (board_walls[diminuiX][vectorTeste[x].y] == 0) {
			menosX++;
			diminuiX--;
		}

		// maisY
		int aumentaY = vectorTeste[x].y;
		while (board_walls[vectorTeste[x].x][aumentaY] == 0){
			maisY++;
			aumentaY++;
		}
		// menosY
		int diminuiY = vectorTeste[x].y;
		while (board_walls[vectorTeste[x].x][diminuiY] == 0) {
			menosY++;
			diminuiY--;
		}


		//X
		if ((maisX + menosX) >= (maisY + menosY)){
			aumentaX = vectorTeste[x].x+1;
			while (board_walls[aumentaX][vectorTeste[x].y] == 0) {
				board_walls[aumentaX][vectorTeste[x].y] = k + BASE_INDEX_MONSTERS;
				for (int i = 0; i < vectorTeste.size(); i++){
					if (vectorTeste[x].x == vectorTeste[aumentaX].x && vectorTeste[x].y == vectorTeste[i].y) {
						vectorTeste.erase(vectorTeste.begin() + i);
						goto foraMaisX;
					}
				}
			foraMaisX:
				aumentaX++;
			}
			// menosX
			diminuiX = vectorTeste[x].x-1;
			while (board_walls[diminuiX][vectorTeste[x].y] == 0) {
				board_walls[diminuiX][vectorTeste[x].y] = k + BASE_INDEX_MONSTERS;
				for (int i = 0; i < vectorTeste.size(); i++) {
					if (vectorTeste[x].x == vectorTeste[diminuiX].x && vectorTeste[x].y == vectorTeste[i].y) {
						vectorTeste.erase(vectorTeste.begin() + i);
						goto foraMenosX;
					}
				}
			foraMenosX:
				diminuiX--;
			}
		}
		//Y
		else {

			// maisY
			aumentaY = vectorTeste[x].y+1;
			while (board_walls[vectorTeste[x].x][aumentaY] == 0) {
				board_walls[vectorTeste[x].x][aumentaY] = k + BASE_INDEX_MONSTERS;
				for (int i = 0; i < vectorTeste.size(); i++) {
					if (vectorTeste[x].x == vectorTeste[i].x && vectorTeste[x].y == vectorTeste[aumentaY].y) {
						vectorTeste.erase(vectorTeste.begin() + i);
						goto foraMaisY;
					}
				}
			foraMaisY:
				aumentaY++;
			}
			// menosY
			diminuiY = vectorTeste[x].y-1;
			while (board_walls[vectorTeste[x].x][diminuiY] == 0) {
				board_walls[vectorTeste[x].x][diminuiY] = k + BASE_INDEX_MONSTERS;
				for (int i = 0; i < vectorTeste.size(); i++) {
					if (vectorTeste[x].x == vectorTeste[i].x && vectorTeste[x].y == vectorTeste[diminuiY].y) {
						vectorTeste.erase(vectorTeste.begin() + i);
						goto foraMenosY;
					}
				}
			foraMenosY:
				diminuiY--;
			}
		}

		board_walls[vectorTeste[x].x][vectorTeste[x].y] = k + BASE_INDEX_MONSTERS;


		vectorTeste.erase(vectorTeste.begin() + x);

	}

	for (i = 0; i < Board::BOARD_X; i++) {
		for (j = 0; j < Board::BOARD_Y; j++) {
			printf(" %2d ", board_walls[i][j]);
		}
		printf("\n");
	}
}