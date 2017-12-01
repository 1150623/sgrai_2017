#include "globalHeader.h"
#include "Character.h"
#include "Camera.h"
#include "Monster.h"
#include "Bullet.h"

#define TECLA_E 0x45
#define TECLA_S 0x53
#define TECLA_W 0x57
#define TECLA_A 0x41
#define TECLA_D 0x44
#define TECLA_V 0x56
#define TECLA_Q 0x51

#define TECLA_UP VK_UP
#define TECLA_LEFT VK_LEFT
#define TECLA_RIGHT VK_RIGHT
#define TECLA_DOWN VK_DOWN




///////////////////////////
#define FIX 0.5
///////////////////////////

//delays in game
int start_timer;
int health = 50;

void init(void);

//window info
float ratio;
int h, w;

Board *board;
Character *myCharacter;
Camera *camera;
Bullet *bullet;

Monster *monstros[NUM_MONSTROS_RANDOM];

char* textureFloor = TEXTURE_FLOOR_4;
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



	std::string s;
	glColor3f(0, 1, 0);

	s = "O";
	glRasterPos2d(w / 2, h / 2);

	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[0]);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void strokeCenterString(char *str, double x, double y, double z, double s)
 {
	int i, n;
	n = strlen(str);
	glPushMatrix();
	glTranslated(x - glutStrokeLength(GLUT_STROKE_ROMAN, (const unsigned char*)str)*0.5*s, y - 119.05*0.5*s, z);
	glScaled(s, s, s);
	for (i = 0; i<n; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, (int)str[i]);
	glPopMatrix();
	
		}

void drawCompass()
 {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(1, -0.15, 1, -0.15);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
			// Blending (transparencias)
		glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	
		
		glRotatef(GRAUS(-myCharacter->angle), 0, 0, 1);
	
			//desenha bussola 2D
			//Norte
		glBegin(GL_POLYGON);
	glColor3f(1.0, 0.7, 0.0);
	glVertex2f(0, 0.09);
	glVertex2f(0.03, 0.004);
	glVertex2f(0, 0.015);
	glVertex2f(-0.03, 0.004);
	glEnd();
	
		glColor3f(1.0, 1, 1.0);
	strokeCenterString("N", 0, 0.04, 0, 0.0002); // string, x ,y ,z ,scale
	
														//Sul
		glBegin(GL_POLYGON);
	glColor3f(0.1, 0.2, 0.8);
	glVertex2f(0, -0.09);
	glVertex2f(0.03, -0.004);
	glVertex2f(0, -0.015);
	glVertex2f(-0.03, -0.004);
	glEnd();
	
		glColor3f(1, 1, 1);
	strokeCenterString("S", 0, -0.04, 0, 0.0002); // string, x ,y ,z ,scale
	
		
		
		
			//											 // ropõe estado
		glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
		//glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_DEPTH_TEST);
	
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
		}

void drawHealthBar()
 {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-0.01, 1, 1, -0.01);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
			// Blending (transparencias)
		glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	
		glBegin(GL_POLYGON);
	glColor3f(0.3, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(100 * 0.004, 0);
	glVertex2f(100 * 0.004, 0.05);
	glVertex2f(0, 0.05);
	glEnd();
	
		glBegin(GL_POLYGON);
	glColor3f(1.0, 0, 0.0);
	glVertex2f(0, 0);
	glVertex2f(health*0.004, 0);
	glVertex2f(health*0.004, 0.05);
	glVertex2f(0, 0.05);
	glEnd();
	
		std::string s;
	glColor3f(0, 1, 0);
	
		s = "Health";
	glRasterPos2d(w / 2 + 0.01, (h / 2) + 0.03);
	int textSize = s.length();
	for (int i = 0; i < textSize; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
		
	}
		/*glColor3f(1.0, 1, 1.0);
			strokeCenterString("Health", 0.04, 0.03, 0, 0.0002);*/ // string, x ,y ,z ,scale
		
			//											 // ropõe estado
		glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
		//glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_DEPTH_TEST);
	
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
		}

void RenderScene()
{ //Draw Scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		myCharacter->Draw(camera->pitch, camera->yaw, view); //go to stating place

	for (int i = 0; i < NUM_MONSTROS_RANDOM; i++) {
		monstros[i]->Draw();
	}

	if (bullet->shoot) {
		bullet->Draw();
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

	drawHealthBar();
	drawCompass();


	glutSwapBuffers();
	glFlush();
}

float normalizeAngle(float angle) {
	int voltas = angle / (2 * M_PI);
	return (angle - (voltas*M_PI));
}


void bulletConfig() {
	int boardIndex = board->getBoardValue((int)myCharacter->y, (int)myCharacter->x);
	for (int k = 0; k < 31; k++) {
		for (int j = 0; j < 28; j++) {
			printf(" %2d ", board->getBoardValue(k, j));
		}
		printf("\n");
	}
	printf("X: %d\n", (int)myCharacter->x);
	printf("Y: %d\n", (int)myCharacter->y);
	printf("boardIndex: %d\n", boardIndex);
	printf("Base: %d\n", BASE_INDEX_MONSTERS);
	int i = (boardIndex - BASE_INDEX_MONSTERS);
	printf("i: %d\n", i);
	if (boardIndex >= BASE_INDEX_MONSTERS && !monstros[i]->killed) {

		//bulletDraw
		if (normalizeAngle(myCharacter->angle) - (normalizeAngle(monstros[i]->angle)) <= RAD(15) ||
			normalizeAngle(myCharacter->angle) - (normalizeAngle(monstros[i]->angle)) >= RAD(-15) ||
			normalizeAngle(myCharacter->angle) - ((normalizeAngle(monstros[i]->angle)) - M_PI) <= RAD(15) ||
			normalizeAngle(myCharacter->angle) - ((normalizeAngle(monstros[i]->angle) - M_PI) >= RAD(-15))) {
			printf("shoot: true\n ");
			bullet->x_dest = monstros[i]->x;
			bullet->y_dest = monstros[i]->y;
			printf("Monster x: %d\n", monstros[i]->x);
			printf("Monster y: %d\n", monstros[i]->y);
			bullet->shoot = true;
		}
	}
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
	start_timer = 100;
	myCharacter->Reinit();
	bullet = new Bullet();

}
bool first = true;
void TimerFunction(int value)
{
	//switch views from 3D to 2D (top view) - 
	// button-> 'V'
	if (GetAsyncKeyState(TECLA_V) && v_timer == 0)
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

	if (GetAsyncKeyState(TECLA_E) && !GetAsyncKeyState(TECLA_V))
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
		if (GetAsyncKeyState(TECLA_D) && !GetAsyncKeyState(TECLA_A))
		{
			if (view == VIEW_FIRST_PERSON) {
				if (board->IsOpen(myCharacter->x + MOVE_RATIO * cos(myCharacter->angle - RAD(90)), myCharacter->y + MOVE_RATIO * sin(myCharacter->angle - RAD(90))))
				{
					myCharacter->x += MOVE_RATIO * cos(myCharacter->angle - RAD(90));
					myCharacter->y += MOVE_RATIO * sin(myCharacter->angle - RAD(90));
				}
			}
			else {
				if (board->IsOpen(myCharacter->x + MOVE_RATIO, myCharacter->y))
				{
					myCharacter->x += MOVE_RATIO;
				}
			}
			//Open doors wih 3 dynamites (pressing 'Q')
			if (GetAsyncKeyState(TECLA_Q) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {
				if (board->IsDoor(myCharacter->x + MOVE_RATIO, myCharacter->y))
				{
					board->OpenDoor(myCharacter->x + MOVE_RATIO, myCharacter->y);
				}
			}
		}

		//move left
		if (GetAsyncKeyState(TECLA_A) && !GetAsyncKeyState(TECLA_D))
		{
			if (view == VIEW_FIRST_PERSON) {
				if (board->IsOpen(myCharacter->x + MOVE_RATIO * cos(myCharacter->angle + RAD(90)), myCharacter->y + MOVE_RATIO * sin(myCharacter->angle + RAD(90))))
				{
					myCharacter->x += MOVE_RATIO * cos(myCharacter->angle + RAD(90));
					myCharacter->y += MOVE_RATIO * sin(myCharacter->angle + RAD(90));
				}
			}
			else {
				if (board->IsOpen(myCharacter->x - MOVE_RATIO-FIX, myCharacter->y))
				{
					myCharacter->x -= MOVE_RATIO;
				}
			}
			//Open doors wih 3 dynamites (pressing 'Q')
			if (GetAsyncKeyState(TECLA_Q) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {
				if (board->IsDoor(myCharacter->x - MOVE_RATIO, myCharacter->y))
				{
					board->OpenDoor(myCharacter->x - MOVE_RATIO, myCharacter->y);
				}
			}

		}
		//move up
		if (GetAsyncKeyState(TECLA_W) && !GetAsyncKeyState(TECLA_S)
			)
		{

			if (view == VIEW_FIRST_PERSON) {
				if (board->IsOpen(myCharacter->x  + MOVE_RATIO * cos(myCharacter->angle), myCharacter->y + MOVE_RATIO * sin(myCharacter->angle)))
				{
					myCharacter->x += MOVE_RATIO * cos(myCharacter->angle);
					myCharacter->y += MOVE_RATIO * sin(myCharacter->angle);
				}
			}
			else {
				if (board->IsOpen(myCharacter->x - MOVE_RATIO, myCharacter->y))
				{
					myCharacter->x -= MOVE_RATIO;
				}
			}
			//Open doors wih 3 dynamites (pressing 'Q')
			if (GetAsyncKeyState(TECLA_Q) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {
				if (board->IsDoor(myCharacter->x - MOVE_RATIO, myCharacter->y))
				{
					board->OpenDoor(myCharacter->x - MOVE_RATIO, myCharacter->y);
				}
			}

			


		}
		else
			//move down
			if (GetAsyncKeyState(TECLA_S) && !GetAsyncKeyState(TECLA_W))
			{
				//printf(" S - DOWN - NEXTPOS = [x = %f][y = %f]\n", round(myCharacter->x + -MOVE_RATIO * cos(myCharacter->angle)-0.5), round(myCharacter->y + MOVE_RATIO * sin(myCharacter->angle)));
				if (view == VIEW_FIRST_PERSON) {
					if (board->IsOpen(myCharacter->x - MOVE_RATIO * cos(myCharacter->angle), myCharacter->y - MOVE_RATIO * sin(myCharacter->angle) ))
					{
						myCharacter->x -= MOVE_RATIO * cos(myCharacter->angle);
						myCharacter->y -= MOVE_RATIO * sin(myCharacter->angle);
					}
				}
				else {
					if (board->IsOpen(myCharacter->x, myCharacter->y + MOVE_RATIO))
					{
						myCharacter->y += MOVE_RATIO;
					}
				}
				//Open doors wih 3 dynamites (pressing 'Q')
				if (GetAsyncKeyState(TECLA_Q) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {

					if (board->IsDoor(myCharacter->x, myCharacter->y + MOVE_RATIO))
					{
						board->OpenDoor(myCharacter->x, myCharacter->y + MOVE_RATIO);
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

	if (bullet->shoot) {
		bullet->Move();
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

void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		printf("Vai entrar\n");
		if (state == GLUT_DOWN) {
			float _yaw = camera->yaw;
			float _pitch = camera->pitch;
			bullet->setInitial(myCharacter->x, myCharacter->y, _yaw,_pitch);
			bullet->shoot = true;
			//bulletConfig();
		}

	}

	if (button == GLUT_RIGHT_BUTTON) {
		printf("Vai entrar\n");
		if (state == GLUT_DOWN) {
			bullet->shoot = false;
		}

	}
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
	glutMouseFunc(mouseClick);
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

	for (int IndexMonster = 0; IndexMonster < NUM_MONSTROS_RANDOM; IndexMonster++) {
		monstros[IndexMonster] = new Monster(board->VecPositionMonsters[IndexMonster].coluna, board->VecPositionMonsters[IndexMonster].linha,CHARACTER_SIZE, IndexMonster, *board);
	}




	init();

	//initial view is the "3D" view
	view = VIEW_FIRST_PERSON;
	v_timer = 0;


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutTimerFunc(15, TimerFunction, 1);
	glutMainLoop();

	return 0; \
}