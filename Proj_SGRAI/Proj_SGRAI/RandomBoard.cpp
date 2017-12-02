#include "RandomBoard.h"


/*


Generates Random Maze using DFS


*/
void Initialize(Cell Level[][LAB_SIZE]);
void GenerateMaze(Cell Level[][LAB_SIZE], int &posX, int &posY, int &goalX, int &goalY);

void createRandomLab(int board_walls[LAB_SIZE][LAB_SIZE]) {

	if (LAB_SIZE % 2 == 0) {
		printf("[LAB_SIZE] must be an odd number!! (ex: 31)\n");
		exit(-1);
	}

	Cell Level[LAB_SIZE][LAB_SIZE];
	int posX = 0;
	int posY = 0;
	int goalX = 0;
	int goalY = 0;
	bool game_over = false;


	Initialize(Level);
	GenerateMaze(Level, posX, posY, goalX, goalY);
	//SaveMaze(Level);

	

	for (int i = 0; i < LAB_SIZE; i++) {
		for (int j = 0; j < LAB_SIZE; j++){
			board_walls[i][j] = Level[i][j].display;
		}
	}
}

// INITIALIZE MAZE
void Initialize(Cell Level[][LAB_SIZE]) {
	for (int i = 0; i < LAB_SIZE; i++) {
		for (int j = 0; j < LAB_SIZE; j++) {
			Level[i][j].display = 1;
			Level[i][j].visited = false;
			Level[i][j].top_wall = true;
			Level[i][j].bot_wall = true;
			Level[i][j].left_wall = true;
			Level[i][j].right_wall = true;
		}
	}
	for (int i = 1; i < LAB_SIZE - 1; i++) {
		for (int j = 1; j < LAB_SIZE - 1; j++) {
			// Border Cells have fewer accessible walls
			Level[1][j].top_wall = false;
			Level[LAB_SIZE - 2][j].bot_wall = false;
			Level[i][1].left_wall = false;
			Level[i][LAB_SIZE - 2].right_wall = false;
		}
	}
}

// GENERATE MAZE
void GenerateMaze(Cell Level[][LAB_SIZE], int &posX, int &posY, int &goalX, int &goalY) {
	srand((unsigned)time(NULL));													//Pick random start cell
	int random = 0;
	int randomX = ((2 * rand()) + 1) % (LAB_SIZE - 1);								//Generate random number between 1 and SIZE
	int randomY = ((2 * rand()) + 1) % (LAB_SIZE - 1);								//Generate random number between 1 and SIZE
	posX = randomX;																	// Save player's initial X position
	posY = randomY;																	// Save player's initial Y position
	int visitedCells = 1;
	int totalCells = ((LAB_SIZE - 1) / 2)*((LAB_SIZE - 1) / 2);
	std::stack<int> back_trackX, back_trackY; 										// Stack is used to trace the reverse path

	Level[randomY][randomX].display = START_POSITION_NUMBER;											// Set S as the start cell
	Level[randomY][randomX].visited = true; 										// Set start cell as visited;

	while (visitedCells < totalCells)
	{
		if (((Level[randomY - 2][randomX].visited == false) && (Level[randomY][randomX].top_wall == true && Level[randomY - 2][randomX].bot_wall == true)) ||
			((Level[randomY + 2][randomX].visited == false) && (Level[randomY][randomX].bot_wall == true && Level[randomY + 2][randomX].top_wall == true)) ||
			((Level[randomY][randomX - 2].visited == false) && (Level[randomY][randomX].left_wall == true && Level[randomY][randomX - 2].right_wall == true)) ||
			((Level[randomY][randomX + 2].visited == false) && (Level[randomY][randomX].right_wall == true && Level[randomY][randomX + 2].left_wall == true)))
		{
			random = (rand() % 4) + 1;												// Pick a random wall 1-4 to knock down

																					// GO UP
			if ((random == 1) && (randomY > 1)) {
				if (Level[randomY - 2][randomX].visited == false) {					// If not visited
					Level[randomY - 1][randomX].display = 0;						// Delete display
					Level[randomY - 1][randomX].visited = true;						// Mark cell as visited
					Level[randomY][randomX].top_wall = false;						// Knock down wall

					back_trackX.push(randomX);										// Push X for back track
					back_trackY.push(randomY);										// Push Y for back track

					randomY -= 2;													// Move to next cell
					Level[randomY][randomX].visited = true;							// Mark cell moved to as visited
					Level[randomY][randomX].display = 0;							// Update path
					Level[randomY][randomX].bot_wall = false;						// Knock down wall
					visitedCells++;													// Increase visitedCells counter
				}
				else
					continue;
			}

			// GO DOWN
			else if ((random == 2) && (randomY < LAB_SIZE - 2)) {
				if (Level[randomY + 2][randomX].visited == false) {						// If not visited
					Level[randomY + 1][randomX].display = 0;							// Delete display
					Level[randomY + 1][randomX].visited = true;							// Mark cell as visited
					Level[randomY][randomX].bot_wall = false;							// Knock down wall

					back_trackX.push(randomX);											// Push X for back track
					back_trackY.push(randomY);											// Push Y for back track

					randomY += 2;														// Move to next cell
					Level[randomY][randomX].visited = true;								// Mark cell moved to as visited
					Level[randomY][randomX].display = 0;								// Update path
					Level[randomY][randomX].top_wall = false;							// Knock down wall
					visitedCells++;														// Increase visitedCells counter
				}
				else
					continue;
			}

			// GO LEFT
			else if ((random == 3) && (randomX > 1)) {
				if (Level[randomY][randomX - 2].visited == false) {						// If not visited
					Level[randomY][randomX - 1].display = 0;							// Delete display
					Level[randomY][randomX - 1].visited = true;							// Mark cell as visited
					Level[randomY][randomX].left_wall = false;							// Knock down wall

					back_trackX.push(randomX);											// Push X for back track
					back_trackY.push(randomY);											// Push Y for back track

					randomX -= 2;														// Move to next cell
					Level[randomY][randomX].visited = true;								// Mark cell moved to as visited
					Level[randomY][randomX].display = 0;								// Update path
					Level[randomY][randomX].right_wall = false;							// Knock down wall
					visitedCells++;														// Increase visitedCells counter
				}
				else
					continue;
			}

			// GO RIGHT
			else if ((random == 4) && (randomX < LAB_SIZE - 2)) {
				if (Level[randomY][randomX + 2].visited == false) {						// If not visited
					Level[randomY][randomX + 1].display = 0;							// Delete display
					Level[randomY][randomX + 1].visited = true;							// Mark cell as visited
					Level[randomY][randomX].right_wall = false;							// Knock down wall

					back_trackX.push(randomX);											// Push X for back track
					back_trackY.push(randomY);											// Push Y for back track

					randomX += 2;														// Move to next cell
					Level[randomY][randomX].visited = true;								// Mark cell moved to as visited
					Level[randomY][randomX].display = 0;								// Update path
					Level[randomY][randomX].left_wall = false;							// Knock down wall
					visitedCells++;														// Increase visitedCells counter
				}
				else
					continue;
			}
		}
		else {
			randomX = back_trackX.top();
			back_trackX.pop();

			randomY = back_trackY.top();
			back_trackY.pop();
		}
	}

	goalX = randomX;
	goalY = randomY;
	Level[goalY][goalX].display = END_POSITION_NUMBER;
}


