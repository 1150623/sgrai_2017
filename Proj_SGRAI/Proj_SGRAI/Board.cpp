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
	{ 1, 0, 0}//7
};


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

void Board::MYcube(bool start)
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
	
}


using namespace AStar;
Generator generator;

Board::Board() {

	createRandomLab(board_walls);
	for (int i = 0; i < LAB_SIZE; i++) {
		for (int j = 0; j < LAB_SIZE; j++) {
			if (board_walls[i][j] == START_POSITION_NUMBER) {
				startPositionX = j;
				startPositionY = i;
			}
			if (board_walls[i][j] == END_POSITION_NUMBER) {
				endPositionX = j;
				endPositionY = i;
			}
		}
	}
	if (DEBBUG) {
		printf("\n       \t+---------------------------------------------------------------------------------------------------------------------------+");
		for (int i = 0; i < LAB_SIZE; i++) {
			printf("\n %d -> \t|", i);
			for (int j = 0; j < LAB_SIZE; j++) {
				if (board_walls[i][j] == START_POSITION_NUMBER || board_walls[i][j] == END_POSITION_NUMBER) {
					printf("#%d#|", board_walls[i][j]);
				}else
				printf(" %d |", board_walls[i][j]);
			}
			printf("\n       \t+---------------------------------------------------------------------------------------------------------------------------+");
		}
	}
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
	
	for (int i = 0; i < BOARD_Y; i++)
	{
		for (int j = 0; j < BOARD_X ; j++)
		{
			int aux = WALLS_BOTTOM;
			glPushMatrix(); 
			{

				glTranslatef(j, i, 0);
				
				glPushMatrix(); 
				{
					if ( board_walls[i][j] == END_POSITION_NUMBER) {
						aux -= WALLS_BOTTOM;
					}

					if (board_walls[i][j] == 1)
					{
						aux += WALLS_TOP;
						aux -= WALLS_BOTTOM;
						if (i - 1 >= 0) if (board_walls[i + 1][j] == 0 || board_walls[i + 1][j] >= BASE_INDEX_MONSTERS || board_walls[i + 1][j] == START_POSITION_NUMBER) { aux += WALLS_SOUTH; }
						if (i + 1 < BOARD_Y) if (board_walls[i - 1][j] == 0 || board_walls[i - 1][j] >= BASE_INDEX_MONSTERS || board_walls[i - 1][j] == START_POSITION_NUMBER) { aux += WALLS_NORTH; }
						if (j + 1 < BOARD_X) if (board_walls[i][j + 1] == 0 || board_walls[i][j + 1] >= BASE_INDEX_MONSTERS || board_walls[i][j + 1] == START_POSITION_NUMBER ) { aux += WALLS_WEST; }
						if (j - 1 >= 0) if (board_walls[i][j - 1] == 0 || board_walls[i][j - 1] >= BASE_INDEX_MONSTERS || board_walls[i][j - 1] == START_POSITION_NUMBER) { aux += WALLS_EAST; }

						if (!(aux & WALLS_SOUTH) && i == 0) if (board_walls[i][j] == 1) { aux += WALLS_SOUTH; }
						if (!(aux & WALLS_NORTH) && i == BOARD_Y - 1) if (board_walls[i][j] == 1) { aux += WALLS_NORTH; }
						if (!(aux & WALLS_WEST) && j == BOARD_X - 1) if (board_walls[i][j] == 1) { aux += WALLS_WEST; }
						if (!(aux & WALLS_EAST) && j == 0) if (board_walls[i][j] == 1) { aux += WALLS_EAST; }
						if (TEXTURE_ON) glBindTexture(GL_TEXTURE_2D, textName[0]);
					}
					else {
						if (TEXTURE_ON) glBindTexture(GL_TEXTURE_2D, textName[1]);
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
							if (board_walls[i][j] == START_POSITION_NUMBER)
								Board::MYcube(true);

							if (board_walls[i][j] == END_POSITION_NUMBER)
								Board::MYcube(false);
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
	drawWalls();
}


//returns whether or not the labirinth is open at the given coords
//array is transpose of how actual labirinth appears on screen
bool
Board::IsOpen(float x, float y)
{	
	return board_walls[(int)y][(int)x] != 1 /*&& board_walls[(int)y][(int)x] != START_POSITION_NUMBER*/;
}

bool Board::IsOpen2(float x, float y, int indexMonster)
{
	if (board_walls[(int)y][(int)x] == indexMonster){
		return true;
	}
	else {
		return false;
	}

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

int
Board::getBoardValue(int x, int y) {
	return board_walls[x][y];
}

AStar::CoordList Board::getPath(int x, int y, int xF, int yF) {
	return generator.findPath({ x, y }, { xF, yF });
}


void Board::makeWall(int x, int y) {

	board_walls[y][x] = 1;

}

struct Vec2ii
{
	int linha, coluna;
};

// Gera monstros aleatorios no mapa
void Board::GenerateRandoMonstersPositions(void)
{
	

	//Conta o numero de possiçoes onde e possivel adicionar monstro
	int numeroPosPossivelCriarMonstro = 0;
	for (int i = 0; i <Board::BOARD_X; i++) {
		for (int j = 0; j < Board::BOARD_Y; j++) {
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

	ImprimeBoarder();

	//Gera um numero Random que vai selecionar a possicao onde vai nascer os monstros
	srand(time(NULL));
	for (int k = 0; k < NUM_MONSTROS_RANDOM; k++)
	{
		int SelectedPosition = rand() % vectorTeste.size();

		// Valor na matriz para a existencia de monstros
		VecPositionMonsters.push_back(savePositionMonsters());
		VecPositionMonsters[k].linha = vectorTeste[SelectedPosition].linha;
		VecPositionMonsters[k].coluna = vectorTeste[SelectedPosition].coluna;

		int maisLinha = 0;
		int menosLinha = 0;
		int maisColuna = 0;
		int menosColuna = 0;

		// maisColunas
		int aumentaLinha = vectorTeste[SelectedPosition].linha;
		while (board_walls[aumentaLinha][vectorTeste[SelectedPosition].coluna] == 0) {
			maisLinha++;
			aumentaLinha++;
		}
		// menosColunas
		int diminiuLinha = vectorTeste[SelectedPosition].linha;
		while (board_walls[diminiuLinha][vectorTeste[SelectedPosition].coluna] == 0) {
			menosLinha++;
			diminiuLinha--;
		}

		// maisLinhas
		int aumentaColuna = vectorTeste[SelectedPosition].coluna;
		while (board_walls[vectorTeste[SelectedPosition].linha][aumentaColuna] == 0) {
			maisColuna++;
			aumentaColuna++;
		}
		// menosLinhas
		int diminuiColuna = vectorTeste[SelectedPosition].coluna;
		while (board_walls[vectorTeste[SelectedPosition].linha][diminuiColuna] == 0) {
			menosColuna++;
			diminuiColuna--;
		}


		//colunas
		if ((maisColuna + menosColuna) >= (maisLinha + menosLinha)) {
			//maisColunas
			aumentaColuna = vectorTeste[SelectedPosition].coluna + 1;

			while (board_walls[vectorTeste[SelectedPosition].linha][aumentaColuna] == 0) {
				board_walls[vectorTeste[SelectedPosition].linha][aumentaColuna] = k + BASE_INDEX_MONSTERS;
				//Remove Valor do vector para nao deixar repetir a posição
				for (int i = 0; i < vectorTeste.size(); i++) {
					if ((aumentaColuna == vectorTeste[i].coluna) && (vectorTeste[SelectedPosition].linha == vectorTeste[i].linha)) {
						if (SelectedPosition > i) {
							SelectedPosition--;
						}
						vectorTeste.erase(vectorTeste.begin() + i);
						goto foraMaisX;
					}
				}
			foraMaisX:
				aumentaColuna++;
			}


			// menosColunas
			diminuiColuna = vectorTeste[SelectedPosition].coluna - 1;

			while (board_walls[vectorTeste[SelectedPosition].linha][diminuiColuna] == 0) {
				board_walls[vectorTeste[SelectedPosition].linha][diminuiColuna] = k + BASE_INDEX_MONSTERS;
				for (int i = 0; i < vectorTeste.size(); i++) {
					if ((diminuiColuna == vectorTeste[i].coluna) && (vectorTeste[SelectedPosition].linha == vectorTeste[i].linha)) {
						if (SelectedPosition > i) {
							SelectedPosition--;
						}
						vectorTeste.erase(vectorTeste.begin() + i);
						goto foraMenosX;
					}
				}
			foraMenosX:
				diminuiColuna--;
			}

		}
		//Linhas
		else {

			// maisLinhas
			aumentaLinha = vectorTeste[SelectedPosition].linha + 1;
			while (board_walls[aumentaLinha][vectorTeste[SelectedPosition].coluna] == 0) {
				board_walls[aumentaLinha][vectorTeste[SelectedPosition].coluna] = k + BASE_INDEX_MONSTERS;
				for (int i = 0; i < vectorTeste.size(); i++) {
					if ((vectorTeste[SelectedPosition].coluna == vectorTeste[i].coluna) && (aumentaLinha == vectorTeste[i].linha)) {
						if (SelectedPosition > i) {
							SelectedPosition--;
						}
						vectorTeste.erase(vectorTeste.begin() + i);
						goto foraMaisY;
					}
				}
			foraMaisY:
				aumentaLinha++;
			}
			// menosLinhas
			diminiuLinha = vectorTeste[SelectedPosition].linha - 1;
			while (board_walls[diminiuLinha][vectorTeste[SelectedPosition].coluna] == 0) {
				board_walls[diminiuLinha][vectorTeste[SelectedPosition].coluna] = k + BASE_INDEX_MONSTERS;
				for (int i = 0; i < vectorTeste.size(); i++) {
					if ((vectorTeste[SelectedPosition].coluna == vectorTeste[i].coluna) && (diminiuLinha == vectorTeste[i].linha)) {
						if (SelectedPosition > i) {
							SelectedPosition--;
						}
						vectorTeste.erase(vectorTeste.begin() + i);
						goto foraMenosY;
					}
				}
			foraMenosY:
				diminiuLinha--;
			}
		}

		board_walls[vectorTeste[SelectedPosition].linha][vectorTeste[SelectedPosition].coluna] = k + BASE_INDEX_MONSTERS;
		vectorTeste.erase(vectorTeste.begin() + SelectedPosition);
		ImprimeBoarder();
	}

	ImprimeBoarder();
}

//gera posições aleatorias no mapa
void Board::generateRandomObjectsPosition(int num) {


	//Adiciona as coordenadas onde é possivel adicionar objetos a um vector
	std::vector<Vec2ii> vector;
	for (int i = 0; i < Board::BOARD_X; i++)
	{
		for (int j = 0; j < Board::BOARD_Y; j++)
		{
			if (board_walls[i][j] == 0) {
				Vec2ii v = { i,j };
				vector.insert(vector.begin(), v);
			}
		}
	}
	int dificulty = 0;

	if (num==3) {
		dificulty = 3;
	}
	else if (num == 5) {
		dificulty = -3;
	}
	//Gera um numero Random que vai selecionar a posicao onde vao nascer objetos
	srand(time(NULL));
	int nr_objets = NUM_DYNAMITES + NUM_BANDAGES + NUM_BULLETS;
	for (int k = 0; k < nr_objets+dificulty ; k++) {
		int x = rand() % vector.size();

		// Valor na matriz para a existencia de objetos
		VecPositionObjects.push_back(savePositionObjects());
		VecPositionObjects[k].y = vector[x].linha;
		VecPositionObjects[k].x = vector[x].coluna;

		if (k<NUM_DYNAMITES) {
			VecPositionObjects[k].type = DYNAMITE;
			board_walls[vector[x].linha][vector[x].coluna] = k + 100;
			vector.erase(vector.begin() + x);
		}
		else if (k<NUM_BANDAGES + NUM_DYNAMITES+dificulty) {
			int b = NUM_BANDAGES + NUM_DYNAMITES + dificulty;
			VecPositionObjects[k].type = BANDAGES;
			board_walls[vector[x].linha][vector[x].coluna] = k + 100;
			vector.erase(vector.begin() + x);

		}
		else if (k <= NUM_DYNAMITES + NUM_BANDAGES + NUM_BULLETS+ dificulty) {
			VecPositionObjects[k].type = BULLETS;
			board_walls[vector[x].linha][vector[x].coluna] = k + 100;
			vector.erase(vector.begin() + x);

		}

	}
	if (DEBBUG) {
		printf("COM OBJETOS: \n");
		for (int i = 0; i < Board::BOARD_X; i++) {
			for (int j = 0; j < Board::BOARD_Y; j++) {
				printf(" %2d ", board_walls[i][j]);
			}
			printf("\n");
		}
	}
}

void Board::ImprimeBoarder(void) {
	if (DEBBUG) {
		printf("-------------------------------------------------------------------------------------------------------\n");
		// imprime a matrix
		printf("    ");
		for (int i = 0; i < Board::BOARD_X; i++)
		{
			printf(" %2d ", i);
		}
		printf("\n");
		for (int i = 0; i < Board::BOARD_X; i++)
		{
			printf("_____");
		}
		printf("\n");
		for (int i = Board::BOARD_X - 1; i >= 0; i--) {
			printf(" %2d | ", Board::BOARD_X - i);
			for (int j = Board::BOARD_Y - 1; j >= 0; j--) {
				printf(" %2d ", board_walls[j][i]);
			}
			printf("\n");
		}
		printf("-------------------------------------------------------------------------------------------------------\n");
	}
}

