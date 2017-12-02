#include "globalHeader.h"
#include "Character.h"
#include "Camera.h"
#include "Monster.h"
#include "Bullet.h"
#include "Object.h"

#define TECLA_E 0x45
#define TECLA_S 0x53
#define TECLA_W 0x57
#define TECLA_A 0x41
#define TECLA_D 0x44
#define TECLA_V 0x56
#define TECLA_Q 0x51
#define TECLA_H 0x48

#define TECLA_UP VK_UP
#define TECLA_LEFT VK_LEFT
#define TECLA_RIGHT VK_RIGHT
#define TECLA_DOWN VK_DOWN




///////////////////////////
#define FIX 0.5
///////////////////////////

//delays in game
int start_timer;

void init(void);

//window info
float ratio;
int h, w;

Board *board;
Character *myCharacter;
Camera *camera;
Bullet *c_bullet;
Bullet *m_bullet;

int nr_objets = NUM_DYNAMITES + NUM_BANDAGES + NUM_BULLETS;

Monster *monstros[NUM_MONSTROS_RANDOM];
Object *objects[NUM_BANDAGES + NUM_BULLETS + NUM_DYNAMITES];

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);



	std::string s;
	glColor3f(0, 1, 0);

	s = "+";
	glRasterPos2d(w / 2, h / 2);

	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[0]);

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
	glPushMatrix(); {
		glLoadIdentity();
		gluOrtho2D(1, -0.15, 1, -0.15);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix(); {
			glLoadIdentity();

			// Blending (transparencias)
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_LIGHTING);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_COLOR_MATERIAL);

			glRotatef(180, 0, 0, 1);
			if (view == VIEW_FIRST_PERSON)
				glRotatef(-GRAUS(myCharacter->angle), 0, 0, 1);

			//desenha bussola 2D
			//Norte
			glBegin(GL_POLYGON);
			glColor4f(0.0, 0.3, 0.0, 0.7);
			glVertex2f(0, 0.09);
			glVertex2f(0.03, 0.004);
			glVertex2f(0, 0.015);
			glVertex2f(-0.03, 0.004);
			glEnd();

			glColor4f(1.0, 1.0, 1.0, 0.7);
			strokeCenterString("N", 0, 0.04, 0, 0.0002); // string, x ,y ,z ,scale

																//Sul
			glBegin(GL_POLYGON);
			glColor4f(0.0, 0.7, 0.0, 0.7);
			glVertex2f(0, -0.09);
			glVertex2f(0.03, -0.004);
			glVertex2f(0, -0.015);
			glVertex2f(-0.03, -0.004);
			glEnd();

			glColor4f(1, 1, 1, 0.7);
			strokeCenterString("S", 0, -0.04, 0, 0.0002); // string, x ,y ,z ,scale


			// ropõe estado
			glDisable(GL_BLEND);
			glEnable(GL_LIGHTING);
			//glEnable(GL_COLOR_MATERIAL);
			glEnable(GL_DEPTH_TEST);

		}glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	}glPopMatrix();
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
	glColor4f(0.3, 0, 0,0.7);
	glVertex2f(0, 0);
	glVertex2f(100 * 0.004, 0);
	glVertex2f(100 * 0.004, 0.05);
	glVertex2f(0, 0.05);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor4f(1.0, 0, 0.0, 0.7);
	glVertex2f(0, 0);
	glVertex2f(myCharacter->lives*0.004, 0);
	glVertex2f(myCharacter->lives*0.004, 0.05);
	glVertex2f(0, 0.05);
	glEnd();
	
		std::string s;
	glColor4f(0, 1, 0, 0.7);
	
		s = "Health";
	glRasterPos2d(w / 2 + 0.01, (h / 2) + 0.03);
	int textSize = s.length();
	for (int i = 0; i < textSize; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
		
	}

		 // ropõe estado
		glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
		//glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_DEPTH_TEST);
	
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void drawGameOverText()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(w/2, w/2, h/2, h/2);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	std::string s;
	glColor3f(1, 0, 0);

	s = "GAME OVER (press ESC)";
	glRasterPos2d(w / 2 + 0.01, (h / 2) + 0.03);
	int textSize = s.length();
	for (int i = 0; i < textSize; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);

	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void drawBulletsBar() {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(1,0,1,-3);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		// Blending (transparencias)
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_COLOR_MATERIAL);

		const int numDiv = 1;
		const float sep = 0.01;
		const float barHeight = 0.1 / (float)numDiv;
		glBegin(GL_QUADS);
		glColor4f(0.5, 1, 0, 0.7);
		for (float i = 0; i < 10; i += (sep + barHeight)) {
			glVertex2f(0, i);
			glVertex2f(0.1, i);
			glVertex2f(0.1, i + barHeight);
			glVertex2f(0, i + barHeight);
		}
		glEnd();

		// ropõe estado
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

	if (myCharacter->retrys > 0 && myCharacter->lives <= 0) {
		myCharacter->Reinit();
	}
	else if (myCharacter->retrys == 0 && myCharacter->lives <= 0) {
		gameover = true;	
		view = VIEW_MAP;
		drawGameOverText();
	}

	board->Draw();


	if (!gameover) {
		myCharacter->Draw(camera->pitch, camera->yaw, view); //go to stating place


		for (int i = 0; i < nr_objets; i++) {
			//printf("Coord obj: %d,%d\nCoord playr: %d,%d\n", objects[i]->x, objects[i]->y, myCharacter->x, myCharacter->y);
			if ((int)objects[i]->x == (int)myCharacter->x && (int)objects[i]->y == (int)myCharacter->y) {
				objects[i]->got_it = true;
				board_walls[(int)objects[i]->x][(int)objects[i]->y] = 0;
				if (objects[i]->type == BANDAGES) {
					myCharacter->lives = 100;
				}
				else if (objects[i]->type == BULLETS) {
					myCharacter->weapon.SetSequence(1);
					Sleep(5);
				}
			}
		}

		for (int i = 0; i < nr_objets; i++) {
			objects[i]->Draw();
		}


		if (c_bullet->shoot) {
			c_bullet->Draw();
		}

		if (view == VIEW_FIRST_PERSON)
			DrawAim();

		for (int i = 0; i < NUM_MONSTROS_RANDOM; i++) {
			printf("MONESTR[%d] is %s\n", i, monstros[i]->killed?"dead":"alive");
			if (!monstros[i]->killed) {
				monstros[i]->Draw();
			}
				
		}

		for (int i = 0; i < NUM_MONSTROS_RANDOM; i++) {
			if (monstros[i]->shooting && !monstros[i]->killed) {
				monstros[i]->bullet->Draw();
			}
		}
	}

	drawHealthBar();
	drawBulletsBar();
	drawCompass();

	glutSwapBuffers();
	glFlush();
}

float normalizeAngle(float angle) {
	if (DEBBUG)printf("Angle : %f\n", angle);
	int voltas = angle / (2 * M_PI);
	if (DEBBUG)printf("voltas : %f\n", angle);
	if (DEBBUG)printf("normalizado : %f\n", angle - (voltas*M_PI));
	return (angle - (voltas*M_PI));
}


void bulletConfig() {
	int boardIndex = board->getBoardValue((int)myCharacter->y, (int)myCharacter->x);
	if (DEBBUG) {
		for (int k = 0; k < 31; k++) {
			for (int j = 0; j < 28; j++) {
				printf(" %2d ", board->getBoardValue(k, j));
			}
			printf("\n");
		}
		printf("X: %d\n", (int)myCharacter->x);
		printf("Y: %d\n", (int)myCharacter->y);
		printf("boardIndex: %d\n", boardIndex);
	}

	int i = (boardIndex - BASE_INDEX_MONSTERS);
	if (DEBBUG)printf("i: %d\n", i);
	if (boardIndex >= BASE_INDEX_MONSTERS && boardIndex <= BASE_INDEX_MONSTERS+ NUM_MONSTROS_RANDOM && !monstros[i]->killed) {

		//bulletDraw
		if (normalizeAngle(myCharacter->angle) - (normalizeAngle(RAD(monstros[i]->angle))) <= RAD(10) ||
			normalizeAngle(myCharacter->angle) - (normalizeAngle(RAD(monstros[i]->angle))) >= RAD(-10) ||
			normalizeAngle(myCharacter->angle) - ((normalizeAngle(RAD(monstros[i]->angle))) - M_PI) <= RAD(10) ||
			normalizeAngle(myCharacter->angle) - ((normalizeAngle(RAD(monstros[i]->angle))) - M_PI) >= RAD(-10)) {
			if (DEBBUG)printf("Char angle : %f     Monster angle: %f\n ", normalizeAngle(myCharacter->angle), normalizeAngle(monstros[i]->angle));
			c_bullet->x_dest = monstros[i]->x;
			c_bullet->y_dest = monstros[i]->y;
			c_bullet->shoot = true;
		}
	}
}

void printHelp() {
	printf("+---------------------------------------------------+\n");
	printf("|                                                   |\n");
	printf("|                 HELP REQUESTED                    |\n");
	printf("|                                                   |\n");
	printf("+---------------------------------------------------+\n");
	printf("+---------------------------------------------------+\n");
	printf("|                    Controls                       |\n");
	printf("+---------------------------------------------------+\n");
	printf("|                                                   |\n");
	printf("|---++Character Motion++                            |\n");
	printf("|                                                   |\n");
	printf("| This game uses W, A, S, D for character motion.   |\n");
	printf("| If in First person, use yout mouse to rotate the  |\n");
	printf("| camera.                                           |\n");
	printf("|                                                   |\n");
	printf("| + W goes Up                                       |\n");
	printf("| + A goes Left                                     |\n");
	printf("| + S goes Right                                    |\n");
	printf("| + D goes Down                                     |\n");
	printf("|                                                   |\n");
	printf("|---++Camera and Views++                            |\n");
	printf("|                                                   |\n");
	printf("| + V changes view to 3º person, while              |\n");
	printf("| + E changes view to 1º person again               |\n");
	printf("|                                                   |\n");
	printf("|---++Catching Objects++                            |\n");
	printf("|                                                   |\n");
	printf("| Just walk through them                            |\n");
	printf("|                                                   |\n");
	printf("|---++Attacking++                                   |\n");
	printf("|                                                   |\n");
	printf("| + Mouse Left-Button to shoot                      |\n");
	printf("| + To do Melee you just have to bee in the same    |\n");
	printf("| square as yout enemy.                             |\n");
	printf("|									                |\n");
	printf("|---++What OBJECTS ARE AVAILABLE?++                 |\n");
	printf("|                                                   |\n");
	printf("| Bandages - Heal yout wounds                       |\n");
	printf("| Bullets  - To refill your bullets                 |\n");
	printf("| Dinamyte - To open final door                     |\n");
	printf("|									                |\n");
	printf("|---++How do I open the Final door?++               |\n");
	printf("|                                                   |\n");
	printf("| First, you have to find the final door witch is   |\n");
	printf("| already a big challange! Then you must have the   |\n");
	printf("| required amount of dinamyte and finnally.......   |\n");
	printf("| just press 'Q' in front of the door! :)           |\n");
	printf("+---------------------------------------------------+\n");
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

	GLfloat fogColor[4] = { 0.6f, 0.6, 0.6f, 1.0f };      // Fog Color
	glFogi(GL_FOG_MODE, GL_EXP);        // Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.1f);              // How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
	glFogf(GL_FOG_START, 1.0);             // Fog Start Depth
	glFogf(GL_FOG_END, 5.0);               // Fog End Depth
	glEnable(GL_FOG);                   // Enables GL_FOG

	srand((unsigned)time(NULL));
	start_timer = 100;
	myCharacter->Reinit();
	c_bullet = new Bullet();

}




int monsterShoot_coolDownTime = 0;
int characterShoot_coolDownTime = 0;

int monsterMelee_coolDownTime = 0;
int characterMelee_coolDownTime = 0;
bool m_meleeDone, m_shootDone, c_shootDone;
bool c_meleeDone = m_meleeDone = m_shootDone = c_shootDone = false;
bool first = true;
void TimerFunction(int value)
{
	//COOL DOWN TIMES FROM ATTACKS (Monsters + Character)
	if (c_meleeDone) {
		characterMelee_coolDownTime = CHARACTER_MELEE_COOLDOWN_TIME;
	}
	if (m_meleeDone) {
		monsterMelee_coolDownTime = MONSTER_MELEE_COOLDOWN_TIME;
	}
	if (c_shootDone) {
		characterShoot_coolDownTime = CHARACTER_SHOOT_COOLDOWN_TIME;
	}
	if (m_shootDone) {
		monsterShoot_coolDownTime = MONSTER_SHOOT_COOLDOWN_TIME;
	}
	if (characterMelee_coolDownTime > 0) { characterMelee_coolDownTime -= 0.1; c_meleeDone = false; }
	
	if (monsterMelee_coolDownTime > 0) {
		monsterMelee_coolDownTime -= 0.1;
		m_meleeDone = false;
	}
		if (characterShoot_coolDownTime > 0) {
			characterShoot_coolDownTime -= 0.1;
			c_shootDone = false;
		}
		if (monsterShoot_coolDownTime > 0) {
			monsterShoot_coolDownTime -= 0.1;
			m_shootDone = false;
		}



	if (GetAsyncKeyState(TECLA_H))
	{
		printHelp();
	}

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
				if (board->IsOpen(myCharacter->x, myCharacter->y - MOVE_RATIO))
				{
					myCharacter->y -= MOVE_RATIO;
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
				if (board->IsOpen(myCharacter->x, myCharacter->y + MOVE_RATIO))
				{
					myCharacter->y += MOVE_RATIO;
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
				if (board->IsOpen(myCharacter->x + MOVE_RATIO * cos(myCharacter->angle), myCharacter->y + MOVE_RATIO * sin(myCharacter->angle)))
				{
					myCharacter->x += MOVE_RATIO * cos(myCharacter->angle);
					myCharacter->y += MOVE_RATIO * sin(myCharacter->angle);
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
					if (board->IsOpen(myCharacter->x - MOVE_RATIO * cos(myCharacter->angle), myCharacter->y - MOVE_RATIO * sin(myCharacter->angle)))
					{
						myCharacter->x -= MOVE_RATIO * cos(myCharacter->angle);
						myCharacter->y -= MOVE_RATIO * sin(myCharacter->angle);
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

					if (board->IsDoor(myCharacter->x, myCharacter->y + MOVE_RATIO))
					{
						board->OpenDoor(myCharacter->x, myCharacter->y + MOVE_RATIO);
					}

				}

			}

		for (int i = 0; i < NUM_MONSTROS_RANDOM; i++)
			if (monstros[i]->killed == false)
				monstros[i]->MoveTo();
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

	if (c_bullet->shoot) { //if character shoot a bullet...
		c_shootDone = true;
		if (board->IsOpen(c_bullet->x, c_bullet->y))c_bullet->Move();
			for (int i = 0; i < NUM_MONSTROS_RANDOM; i++) {
				if (!monstros[i]->killed) {
					if ((monstros[i]->x <= c_bullet->x + 0.2 && monstros[i]->x >= c_bullet->x - 0.2) && (monstros[i]->y <= c_bullet->y + 0.2 && monstros[i]->y >= c_bullet->y - 0.2) ) {
						monstros[i]->lives -= CHARACTER_DAMAGE_SHOOT;
						c_shootDone = false;
						if (monstros[i]->lives <= 0) {
							monstros[i]->killed = true;
						}
					}
				}
			}
	}
	int pos = board->getBoardValue(myCharacter->y, myCharacter->x);
	printf("POS = %d\n", pos);
	if (pos >= BASE_INDEX_MONSTERS && pos <= BASE_INDEX_MONSTERS + NUM_MONSTROS_RANDOM) { //if character is in a monster zone...
		if (!monstros[pos]->killed) {
			int meleeDamage = monstros[pos]->alert(myCharacter->x, myCharacter->y);
			if (meleeDamage == 1) { //melee
				m_meleeDone = true;
				myCharacter->lives -= MONSTER_DAMAGE_MELEE;
			}
			if (meleeDamage == 2 ) { //shooting
				m_shootDone = true;
				monstros[pos]->shoot(myCharacter->x, myCharacter->y);
				myCharacter->lives -= MONSTER_DAMAGE_SHOOT;
			}
		}
	}

	for (int i = 0; i < NUM_MONSTROS_RANDOM; i++) {
		if (monstros[i]->shooting) {
			if (board->IsOpen(monstros[i]->bullet->x, monstros[i]->bullet->y))monstros[i]->bullet->Move();
			
		}
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
		if (DEBBUG)printf("Vai entrar\n");
		if (state == GLUT_DOWN) {
			float _yaw = camera->yaw;
			float _pitch = camera->pitch;
			c_bullet->setInitial(myCharacter->x, myCharacter->y, _yaw,_pitch);
			c_bullet->shoot = true;
			bulletConfig();
		}

	}

	if (button == GLUT_RIGHT_BUTTON) {
		if (DEBBUG)printf("Vai entrar\n");
		if (state == GLUT_DOWN) {
			c_bullet->shoot = false;
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
		if (!glutCreateWindow("Labirinto 3D"))
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
	myCharacter = new Character(board->startPositionX, board->startPositionY, CHARACTER_SIZE, *board);
	//myCharacter->MoveTo(20, 20);
	// gerar labirinto aleatorio
	board->GenerateRandoMonstersPositions();
	board->generateRandomObjectsPosition();

	for (int IndexMonster = 0; IndexMonster < NUM_MONSTROS_RANDOM; IndexMonster++) {
		monstros[IndexMonster] = new Monster(board->VecPositionMonsters[IndexMonster].coluna, board->VecPositionMonsters[IndexMonster].linha,CHARACTER_SIZE, IndexMonster, board);
	}

	if (DEBBUG) {
		printf("Posição dos objetos: \n");
		for (int i = 0; i < board->VecPositionObjects.size(); i++)
		{
			printf("	coord: %d,%d\n	tipo:%d\n", board->VecPositionObjects[i].x, board->VecPositionObjects[i].y, board->VecPositionObjects[i].type);

		}
	}

	for (int k = 0; k < nr_objets; k++) {
		if (board->VecPositionObjects[k].type == DYNAMITE) {
			objects[k] = new Object(board->VecPositionObjects[k].type, board->VecPositionObjects[k].x,
				board->VecPositionObjects[k].y, CHARACTER_SIZE, *board);

		}

		else if (board->VecPositionObjects[k].type == BANDAGES) {

			objects[k] = new Object(board->VecPositionObjects[k].type, board->VecPositionObjects[k].x,
				board->VecPositionObjects[k].y, CHARACTER_SIZE, *board);

		}
		else if (board->VecPositionObjects[k].type == BULLETS) {
			objects[k] = new Object(board->VecPositionObjects[k].type, board->VecPositionObjects[k].x,
				board->VecPositionObjects[k].y, CHARACTER_SIZE, *board);
		}
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