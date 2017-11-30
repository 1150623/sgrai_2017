#include "globalHeader.h"
#include "Character.h"
#include "Camera.h"
#include "Monster.h"


#define TECLA_S 0x53
#define TECLA_W 0x57
#define TECLA_A 0x41
#define TECLA_D 0x44

#define TECLA_UP VK_UP
#define TECLA_LEFT VK_LEFT
#define TECLA_RIGHT VK_RIGHT
#define TECLA_DOWN VK_DOWN


//delays in game
int start_timer;

void init(void);

//window info
float ratio;
int h, w;

Board *board;
Character *myCharacter;
Camera *camera;

Monster *monstros[NUM_MONSTROS_RANDOM];

char* textureFloor = TEXTURE_FLOOR_2;
char* textureWall = TEXTURE_WALL_1;

//viewing position (not implemented yet)
int view;
//stops key repeats
int v_timer;

bool gameover = false;	// used to tell if the game has ended  (not implemented yet - no onjective defined)

void DrawAim() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	int textSize;

	std::string s;
	glColor3f(0, 1, 0);

	s = "+";
	glRasterPos2d(w / 2, h / 2);
	textSize = s.length();

	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[0]);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void RenderScene()
{ //Draw Scene
	
  //camera update
	camera->Set_position(myCharacter->x, myCharacter->y, view);

	camera->set_light(myCharacter->x, myCharacter->y, myCharacter->size);

	//labirinto Init (where to put objects for example)


	//if (/*Something happens like catching all keys OR killing certain monsters or something...*/)
	//{
	//restart all
	//	init();
	//	//unlock something
	//	//or, for testing:
	//	board->tp_restore(); // (comment when needed) - restore lab
	//}
	
	board->Draw();

	
	if (!gameover)
		myCharacter->Draw(camera->pitch,camera->yaw,view); //go to stating place

	for (int i = 0; i <NUM_MONSTROS_RANDOM; i++) {
		monstros[i]->Draw();
	}

	/*	
		{ 
			//Example For Monster implementation

			if (!gameover)			//Monsters not implemented
				monster[x]->Draw();

			if (!gameover)			//Monsters not implemented
				monster[x]->Move();

			if(monster->killed)
				...
		}
	*/
	if (view == VIEW_FIRST_PERSON)
		DrawAim();


	glutSwapBuffers();
}

GLuint textName[NUM_TEXTURES];

//SET UP THE GAME
void init(void)
{

	if (TEXTURE_ON) {
				
		//activar texturas 
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glEnable(GL_TEXTURE_2D);
		
		//configurar aspectos gerais de texturas
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // GL_MODULATE - So that light can take effect on textures 
		glDepthFunc(GL_LESS);
		
		//criar objecto textura
		glGenTextures(NUM_TEXTURES, textName);
		board->loadTextures();
		
	}
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	srand((unsigned)time(NULL));
	start_timer = 70;
	myCharacter->Reinit();

}

void TimerFunction(int value)
{
	//switch views from 3D to 2D (top view) - button-> 'V'
	if (GetAsyncKeyState(0x56) && v_timer == 0)
	{
		view = (view == VIEW_FIRST_PERSON) ? VIEW_THIRD_PERSON : (view == VIEW_THIRD_PERSON) ? VIEW_MAP : (view == VIEW_MAP) ? VIEW_THIRD_PERSON : view;
		if (view == VIEW_MAP && !DEBBUG) {
			view = VIEW_THIRD_PERSON;
		}

		if (view == VIEW_MAP) camera->Reshape(ratio, 60);
		if (view == VIEW_THIRD_PERSON) camera->Reshape(ratio, 10);
		v_timer = 10;
	}
	if (v_timer > 0)
		v_timer--;

	if (GetAsyncKeyState(0x45) && !GetAsyncKeyState(0x56))
	{
		view = VIEW_FIRST_PERSON;
		camera->Reshape(ratio, 60);
	}

	//start a new game
	if (GetAsyncKeyState(VK_RETURN) && gameover) // GAMEOVER not implemented yet
	{
		myCharacter->lives = 3;
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
		if (GetAsyncKeyState(TECLA_D) && !GetAsyncKeyState(TECLA_A)
			)
		{
			if (board->IsOpen(myCharacter->x + MOVE_RATIO, myCharacter->y))
			{
				if (view == VIEW_FIRST_PERSON) {
					myCharacter->x += -MOVE_RATIO * cos(myCharacter->angle + RAD(90));
					myCharacter->y -= -MOVE_RATIO * sin(myCharacter->angle + RAD(90));
				}
				else {
					myCharacter->x += MOVE_RATIO;
				}
			}
			else {//Open doors wih 3 dynamites (pressing 'Q')
				if (GetAsyncKeyState(0x51) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {
					if (board->IsDoor(myCharacter->x + MOVE_RATIO, myCharacter->y))
					{
						board->OpenDoor(myCharacter->x + MOVE_RATIO, myCharacter->y);
					}
				}
			}
		}
		else
			//move left
			if (GetAsyncKeyState(TECLA_A) && !GetAsyncKeyState(TECLA_D)
				)
			{
				if (board->IsOpen(myCharacter->x - MOVE_RATIO, myCharacter->y))
				{
					if (view == VIEW_FIRST_PERSON) {
						myCharacter->x += MOVE_RATIO * cos(myCharacter->angle + RAD(90));
						myCharacter->y -= MOVE_RATIO * sin(myCharacter->angle + RAD(90));
					}
					else {
						myCharacter->x -= MOVE_RATIO;
					}
				}
				else {//Open doors wih 3 dynamites (pressing 'Q')
					if (GetAsyncKeyState(0x51) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {
						if (board->IsDoor(myCharacter->x - MOVE_RATIO, myCharacter->y))
						{
							board->OpenDoor(myCharacter->x - MOVE_RATIO, myCharacter->y);
						}
					}
				}
			}
		//move up
		if (GetAsyncKeyState(TECLA_W) && !GetAsyncKeyState(TECLA_S)
			)
		{
			if (board->IsOpen(myCharacter->x, myCharacter->y - MOVE_RATIO))
			{
				if (view == VIEW_FIRST_PERSON) {
					myCharacter->x += MOVE_RATIO * cos(myCharacter->angle);
					myCharacter->y -= MOVE_RATIO * sin(myCharacter->angle);
				}
				else {
					myCharacter->y -= MOVE_RATIO;
				}
			}
			else {//Open doors wih 3 dynamites (pressing 'Q')
				if (GetAsyncKeyState(0x51) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {
					if (board->IsDoor(myCharacter->x, myCharacter->y - MOVE_RATIO))
					{
						board->OpenDoor(myCharacter->x, myCharacter->y - MOVE_RATIO);
					}
				}
			}
		}
		else
			//move down
			if (GetAsyncKeyState(TECLA_S) && !GetAsyncKeyState(TECLA_W)
				)
			{
				if (board->IsOpen(myCharacter->x, myCharacter->y + MOVE_RATIO))
				{
					if (view == VIEW_FIRST_PERSON) {
						myCharacter->x += -MOVE_RATIO * cos(myCharacter->angle);
						myCharacter->y -= -MOVE_RATIO * sin(myCharacter->angle);
					}
					else {
						myCharacter->y += MOVE_RATIO;
					}
				}
				else {//Open doors wih 3 dynamites (pressing 'Q')
					if (GetAsyncKeyState(0x51) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {
						if (board->IsDoor(myCharacter->x, myCharacter->y + MOVE_RATIO))
						{
							board->OpenDoor(myCharacter->x, myCharacter->y + MOVE_RATIO);
						}
					}
				}
			}

	}

	//DEBBUG KEYS
	if (DEBBUG) {
		float d = 0;
		if (GetAsyncKeyState(VK_F1) && !GetAsyncKeyState(VK_F2))
		{
			d = camera->distance += 0.5;
			camera->Reshape(camera->ratio, d);
			camera->Set_position(myCharacter->x, myCharacter->y, view);
		}
		if (GetAsyncKeyState(VK_F2) && !GetAsyncKeyState(VK_F1)) {
			d = camera->distance -= 0.5;
			camera->Reshape(camera->ratio, d);
			camera->Set_position(myCharacter->x, myCharacter->y, view);
		}

		if (GetAsyncKeyState(VK_F3) && !GetAsyncKeyState(VK_F4)) { //F3 - Não atribuido
		}
		if (GetAsyncKeyState(VK_F4) && !GetAsyncKeyState(VK_F3)) { //F4 - Não atribuido
		}
		if (GetAsyncKeyState(VK_F5) && !GetAsyncKeyState(VK_F6)) { //F5 - Não atribuido
		}
		if (GetAsyncKeyState(VK_F6) && !GetAsyncKeyState(VK_F5)) { //F6 - Não atribuido
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

	int distance = 0;
	if (view == VIEW_FIRST_PERSON || view == VIEW_MAP) {
		distance = 60;
	}
	else {
		distance = 10;
	}

	camera->Reshape(ratio, distance);
}

void MouseMotion(int x, int y)
{
	// This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
	// This avoids it being called recursively and hanging up the event loop
	static bool just_warped = false;

	if (just_warped) {
		just_warped = false;
		return;
	}


		int dx = x - glutGet(GLUT_WINDOW_WIDTH) / 2;
		int dy = y - glutGet(GLUT_WINDOW_HEIGHT) / 2;

		if (dx) {
			camera->RotateYaw(VELOCIDADE_ROTACAO*dx);
		}

		if (dy) {
			camera->RotatePitch(VELOCIDADE_ROTACAO*dy);
		}

		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		just_warped = true;
		myCharacter->angle = camera->yaw;
	
}

int main(int argc, char **argv) {

	info();
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	if (!FULLSCREEN) {
		//windowed mode
		glutInitWindowSize(1080, 820);
		if (glutCreateWindow("Labirinto 3D") == GL_FALSE)
			exit(1);
	}
	else {
		//fullscreen mode
		glutGameModeString("800x600:16@60");
		glutEnterGameMode();
	}

	camera = new Camera();

	//make mouse disappear
	glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	

	//draw the level/floor...
	glClearColor(.3, .3, .3, 1.0);
	
	
	//set up board
	board = new Board();
	
	//Inicialize character
	myCharacter = new Character(CHARACTER_STARTLOCATION_X, CHARACTER_STARTLOCATION_Y, CHARACTER_SIZE, *board);
	myCharacter->MoveTo(20, 20);
	// gerar labirinto aleatorio
	board->GenerateRandoMonstersPositions();
	
	for (int  i = 0; i < board->VecPositionMonsters.size(); i++)
	{
		printf("%d\n", board->VecPositionMonsters[i].x);

	}


	for (int i = 0; i <NUM_MONSTROS_RANDOM; i++){
		monstros[i] = new Monster(board->VecPositionMonsters[i].x, board->VecPositionMonsters[i].y,i, CHARACTER_SIZE, *board);
	}




	init();

	//initial view is the "3D" view
	view = VIEW_FIRST_PERSON;
	v_timer = 0;
	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glutTimerFunc(15, TimerFunction, 1);
	glutMainLoop();

	return 0;\
}