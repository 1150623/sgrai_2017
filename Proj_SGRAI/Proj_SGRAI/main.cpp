#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>
#include "Board.h"
#include "Character.h"
#include "Camera.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

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

	//pipe transport
	if ((int)myCharacter->x == 27 && (int)myCharacter->y == 14 && myCharacter->angle == 0)
	{
		myCharacter->x = 0;
		myCharacter->animate = true;
	}
	else
		if ((int)(myCharacter->x + 0.9) == 0 && (int)myCharacter->y == 14 && myCharacter->angle == 180)
		{
			myCharacter->x = 27;
			myCharacter->animate = true;
		}
	
	if (myCharacter->animate)
		myCharacter->Move();
	if (!(board->IsOpen((int)(myCharacter->x + cos(M_PI / 180 * myCharacter->angle)),
		(int)(myCharacter->y + sin(M_PI / 180 * myCharacter->angle)))) &&
		myCharacter->x - (int)myCharacter->x < 0.1 && myCharacter->y - (int)myCharacter->y < 0.1)
		myCharacter->animate = false;


	//labirinto Init (where to put objects for example)


	//if (true /*Something happens like catching all keys*/)
	//{
	//	init();
	//	//unlock something
	//	//or, for testing:
	//	board->tp_restore(); // (comment when needed) - restore lab
	//}
	
	board->Draw();
	
	if (!gameover)
		myCharacter->Draw(); //go to stating place

	/*	{
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
	start_timer = 140;
	myCharacter->Reinit();

	/**
	//Monsters inicial positions
	int start_x[4] = { 11,12,15,16 };
	float ghost_colors[4][3] = { { 255,0,0 },{ 120,240,120 },{ 255,200,200 },{ 255,125,0 } };

	for (int i = 0; i < num_monsters; i++)
	{
		monsters[i]->Reinit();
	}

	//PUT HERE Monsters starting positions + colors + speed +.....
	
	*/



}



void TimerFunction(int value)
{


	//switch views from 3D to classic
	if (GetAsyncKeyState(0x56) && v_timer == 0)
	{
		view = (view + 1) % 2;
		v_timer = 10;
	}
	if (v_timer > 0)
		v_timer--;


	//character moving + key recognition - ex: press VK_UP to move up


	//start a new game
	if (GetAsyncKeyState(VK_RETURN) && gameover)
	{
		//myCharacter->lives = ???? how many ????;
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
		if (GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT))
		{
			if (board->IsOpen(myCharacter->x +1, myCharacter->y))
				myCharacter->x++;
		}
		else
			//move left
			if (GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT))
			{
				if(board->IsOpen(myCharacter->x -1 , myCharacter->y))
						myCharacter->x--;
			}
		//move up
		if (GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_DOWN))
		{
				if (board->IsOpen(myCharacter->x, myCharacter->y - 1))
					myCharacter->y--;
			
		}
		else
			//move down
			if (GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_UP))
			{
				if (board->IsOpen(myCharacter->x, myCharacter->y + 1))
					myCharacter->y++;
			}

	}


	//quit
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		exit(0);
	}

	glutPostRedisplay();

	glutTimerFunc(15, TimerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1;

	ratio = 1.0f * w / (h);
	glViewport(0, 0, w, h);
	camera = new Camera(ratio);

}

int main() {

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	//windowed mode
	glutInitWindowSize(1080, 820);
	glutCreateWindow("Labirinto 3D");

	//fullscreen mode
	
	//glutGameModeString("800x600:16@60");
	//glutEnterGameMode();

	//make mouse disappear
	glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(15, TimerFunction, 1);

	//draw the level/floor...
	glClearColor(.3, .3, .3, 1.0);

	//set up board
	board = new Board();
	int start_x[4] = { 11,12,15,16 }; //staring position
	//Inicialize character
	myCharacter = new Character(13.5, 23);

	//put monster in starting positions
	/*
	for (int i = 0; i < num_monsters; i++)
	{
		monsters[i] = new Monsters(start_x[i], 14);
	}
	*/

	init();

	//initial view is the "3D" view
	view = 0;
	v_timer = 0;

	glutMainLoop();

	return 0;
}