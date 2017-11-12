#include "globalHeader.h"
#include "Board.h"
#include "Character.h"
#include "Camera.h"


//delays in game
int start_timer;

void init(void);

//window info
float ratio;
int h, w;

Board *board;
Character *myCharacter;
Camera *camera;

//viewing position (not implemented yet)
int view;
//stops key repeats
int v_timer;

bool gameover = false;	// used to tell if the game has ended  (not implemented yet - no onjective defined)

void RenderScene()
{ //Draw Scene
	
  //camera update
	camera->Set_position(myCharacter->x, myCharacter->y, view);

	//labirinto Init (where to put objects for example)


	//if (true /*Something happens like catching all keys OR killing certain monsters or something...*/)
	//{
	//	init();
	//	//unlock something
	//	//or, for testing:
	//	board->tp_restore(); // (comment when needed) - restore lab
	//}
	
	board->Draw();
	
	if (!gameover)
		myCharacter->Draw(); //go to stating place

	/*	{ //Example For Monster implementation

			if (!gameover)			//Monsters not implemented
				monster->Draw();

			if (!gameover)			//Monsters not implemented
				monster[x]->Move();

			if(monster->killed)
				...
		}
	*/


	glutSwapBuffers();
}


//SET UP THE GAME
void init(void)
{
	srand((unsigned)time(NULL));
	start_timer = 70;
	myCharacter->Reinit();


	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_DEPTH_TEST);

}

void TimerFunction(int value)
{


	//switch views from 3D to 2D (top view) - button-> 'V'
	if (GetAsyncKeyState(0x56) && v_timer == 0)
	{
		view = (view + 1) % 2;
		v_timer = 10;
	}
	if (v_timer > 0)
		v_timer--;


	
	//start a new game
	if (GetAsyncKeyState(VK_RETURN) && gameover) // GAMEOVER not implemented yet
	{
		myCharacter->lives = 5;
		init();
		//labirinto->tp_restore();
		gameover = false;
	}


	//short pause when starting game
	if (start_timer > 0)
		start_timer--;

	//make sure game is in play
	
	if (!gameover && start_timer == 0)
	{
		// Get keyboard input
		//move right
		if (GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT)
			)
		{
			if (board->IsOpen(round(myCharacter->x + MOVE_RATIO), round(myCharacter->y)))
			{
				myCharacter->x += MOVE_RATIO;
				myCharacter->angle = 0;
			}
		}
		else
			//move left
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT)
				)
			{
				if (board->IsOpen(round(myCharacter->x - MOVE_RATIO), round(myCharacter->y)))
				{
					myCharacter->x -= MOVE_RATIO;
					myCharacter->angle = 180;
				}
			}
		//move up
		if (GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_DOWN)
			)
		{
			if (board->IsOpen(round(myCharacter->x), round(myCharacter->y - MOVE_RATIO)))
			{
				myCharacter->y -= MOVE_RATIO;
				myCharacter->angle = 270;
			}
		}
		else
			//move down
			if (GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_UP)
				)
			{
				if (board->IsOpen(round(myCharacter->x), round(myCharacter->y + MOVE_RATIO)))
				{
					myCharacter->y += MOVE_RATIO;
					myCharacter->angle = 90;
				}
			}

	}

	//DEBBUG KEYS
	if (DEBBUG) {
		float d = 0;
		if (GetAsyncKeyState(VK_F1) && !GetAsyncKeyState(VK_F2))
		{
			d = camera->distance += 0.5;
			camera = new Camera(camera->ratio,d);
			camera->Set_position(myCharacter->x, myCharacter->y, view);
		}
		if(GetAsyncKeyState(VK_F2) && !GetAsyncKeyState(VK_F1)) {
			d = camera->distance-=0.5;
			camera = new Camera(camera->ratio, d);
			camera->Set_position(myCharacter->x, myCharacter->y, view);
		}

		if (GetAsyncKeyState(VK_F3) && !GetAsyncKeyState(VK_F4)) {
			board->ang++;
		}
		if (GetAsyncKeyState(VK_F4) && !GetAsyncKeyState(VK_F3)) {
			board->ang--;

		}
	}



	//quit
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		board->~Board();
		exit(0);
	}

	glutPostRedisplay();
	glutTimerFunc(1, TimerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1;

	ratio = 1.0 * w / (h);
	glViewport(0, 0, w, h);
	int distance = 70;
	camera = new Camera(ratio, distance);

}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	//windowed mode
	glutInitWindowSize(1080, 820);
	if (glutCreateWindow("Labirinto 3D") == GL_FALSE)
		exit(1);

	//fullscreen mode
	//glutGameModeString("800x600:16@60");
	//glutEnterGameMode();

	//make mouse disappear
	glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	

	//draw the level/floor...
	glClearColor(.3, .3, .3, 1.0);

	//set up board
	board = new Board();
	
									  
	//Inicialize character
	myCharacter = new Character(CHARACTER_STARTLOCATION_X, CHARACTER_STARTLOCATION_Y, CHARACTER_SIZE);


	init();

	//initial view is the "3D" view
	view = 0;
	v_timer = 0;

	glutTimerFunc(15, TimerFunction, 1);
	glutMainLoop();

	return 0;
}