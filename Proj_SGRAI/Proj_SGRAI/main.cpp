#include "globalHeader.h"
#include "Character.h"
#include "Camera.h"
#include "Monster.h"
#include "Bullet.h"
#include "Object.h"
#include "image_loader.h"
#include <string>;

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

bool gameWon = false;
GLuint textName[NUM_TEXTURES];
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

void drawGameWon()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(w / 2, w / 2, h / 2, h / 2);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	std::string s;
	glColor3f(0, 1, 0);

	s = "GAME WON! You managed to Escape, congratulations!! (press ESC to leave)";
	glRasterPos2d(w / 2-0.7, (h / 2) + 0.03);
	int textSize = s.length();
	for (int i = 0; i < textSize; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);

	}

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

	s = "GAME OVER (press ESC to leave)";
	glRasterPos2d(w / 2 -0.1, (h / 2) + 0.75);
	int textSize = s.length();
	for (int i = 0; i < textSize; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);

	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

int numBullets = NUM_BULLETS;
int numDynamite = 1;

void drawBulletsBar() {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(-0.9, 0.1, 0.08, -0.9);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		// Blending (transparencias)
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_COLOR_MATERIAL);

		glBegin(GL_QUADS);
		glColor4f(0, 0, 0, 0.7);
		glVertex2f(0, 0); // Upper left
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)/6, 0); // Upper right
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)/6, glutGet(GLUT_WINDOW_HEIGHT)/6); // Lower right
		glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)/6); // Lower left
		glEnd();

		glColor4f(0, 1, 0, 0.7);


		std::string text_bullets = "Bullets: ";
		text_bullets += std::to_string(numBullets);

		glRasterPos2d(w / 2 + 0.01, (h / 2) + 0.03);
		int textSize = text_bullets.length();
		for (int i = 0; i < textSize; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_bullets[i]);

		}

		std::string text_dyn = "Dynamite: ";
		text_dyn += std::to_string(numDynamite);

		glRasterPos2d(w / 2 + 0.01, (h / 2) + 0.06);
		int textSize2 = text_dyn.length();
		for (int i = 0; i < textSize2; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_dyn[i]);

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

bool reloading2 = false;
bool reloading = false;

bool shootingAnimation = false;
bool shootingAnimation2 = false;
typedef struct {
	int sizeX, sizeY;
	char *data;
} PPMImage2;

extern "C" PPMImage2 *LoadPPM2(char * path) {
	PPMImage2* result = new PPMImage2;
	result->sizeX = 1024;
	result->sizeY = 1024;
	result->data = SAIL_load_image(path, &result->sizeX, &result->sizeY);

	return result;
};

void drawStart()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(1, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Blending (transparencias)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);

	/*PPMImage2 *imagemPPM;
	imagemPPM = LoadPPM2(TEXTURE_START_IMAGE);
	glBindTexture(GL_TEXTURE_2D, textName[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagemPPM->sizeX, imagemPPM->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemPPM->data);*/


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	glColor4f(1, 0, 0, 0.7);
	glVertex2f(0, 0); // Upper left
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH), 0); // Upper right
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)); // Lower right
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)); // Lower left
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
  
	if (!gameWon) {
		//camera update

		camera->Set_position(myCharacter->x, myCharacter->y, view);

		camera->set_light(myCharacter->x, myCharacter->y, myCharacter->size);


		//labirinto Init (where to put objects for example)

		if (myCharacter->retrys > 0 && myCharacter->lives <= 0) {
			myCharacter->Reinit();
			numBullets = NUM_BULLETS;
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
				if (objects[i]->got_it == false) {
					if ((int)objects[i]->x == (int)myCharacter->x && (int)objects[i]->y == (int)myCharacter->y) {

						objects[i]->got_it = true;
						board_walls[(int)objects[i]->x][(int)objects[i]->y] = 0;

						if (objects[i]->type == BANDAGES) {
							myCharacter->lives = NUM_LIVES;
						}
						else if (objects[i]->type == BULLETS) {
							myCharacter->Reload(true);
							reloading = true;
							reloading2 = true;
							numBullets = NUM_BULLETS+numBullets;

						}
						else if (objects[i]->type == DYNAMITE) {
							numDynamite++;
						}
					}
				}
			}
			if (!reloading) {
				myCharacter->Reload(false);
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
				if (!monstros[i]->killed) {
					monstros[i]->Draw();
				}

			}

			for (int i = 0; i < NUM_MONSTROS_RANDOM; i++) {
				if (monstros[i]->shooting && !monstros[i]->killed && monstros[i]->bullet != nullptr) {
					if (monstros[i]->bullet->draw)
						monstros[i]->bullet->Draw();
				}
			}
		}

		drawHealthBar();
		drawBulletsBar();
		drawCompass();
		//drawStart();
	}
	else {

		drawGameWon();

	}
	glutSwapBuffers();
	glFlush();
}

float normalizeAngle(float angle) {
	int voltas = angle / (2 * M_PI);
	return (angle - (voltas*M_PI));
}


void bulletConfig() {
	int boardIndex = board->getBoardValue((int)myCharacter->y, (int)myCharacter->x);
	

	int i = (boardIndex - BASE_INDEX_MONSTERS);
	if (boardIndex >= BASE_INDEX_MONSTERS && boardIndex <= BASE_INDEX_MONSTERS+ NUM_MONSTROS_RANDOM && !monstros[i]->killed) {

		//bulletDraw
		if (normalizeAngle(myCharacter->angle) - (normalizeAngle(RAD(monstros[i]->angle))) <= RAD(10) ||
			normalizeAngle(myCharacter->angle) - (normalizeAngle(RAD(monstros[i]->angle))) >= RAD(-10) ||
			normalizeAngle(myCharacter->angle) - ((normalizeAngle(RAD(monstros[i]->angle))) - M_PI) <= RAD(10) ||
			normalizeAngle(myCharacter->angle) - ((normalizeAngle(RAD(monstros[i]->angle))) - M_PI) >= RAD(-10)) {
			c_bullet->x_dest = monstros[i]->x;
			c_bullet->y_dest = monstros[i]->y;
			c_bullet->shoot = true;
		}
	}
}

void printHelp() {
	printf("\t+---------------------------------------------------+\n");
	printf("\t|                                                   |\n");
	printf("\t|                 HELP REQUESTED                    |\n");
	printf("\t|                                                   |\n");
	printf("\t+---------------------------------------------------+\n");
	printf("\t+---------------------------------------------------+\n");
	printf("\t|                    Controls                       |\n");
	printf("\t+---------------------------------------------------+\n");
	printf("\t|                                                   |\n");
	printf("\t|---++Character Motion++                            |\n");
	printf("\t|                                                   |\n");
	printf("\t| This game uses W, A, S, D for character motion.   |\n");
	printf("\t| If in First person, use yout mouse to rotate the  |\n");
	printf("\t| camera.                                           |\n");
	printf("\t|                                                   |\n");
	printf("\t| + W goes Up                                       |\n");
	printf("\t| + A goes Left                                     |\n");
	printf("\t| + S goes Right                                    |\n");
	printf("\t| + D goes Down                                     |\n");
	printf("\t|                                                   |\n");
	printf("\t|---++Camera and Views++                            |\n");
	printf("\t|                                                   |\n");
	printf("\t| + V changes view to 3th person, while             |\n");
	printf("\t| + E changes view to 1st person again              |\n");
	printf("\t|                                                   |\n");
	printf("\t|---++Catching Objects++                            |\n");
	printf("\t|                                                   |\n");
	printf("\t| Just walk through them                            |\n");
	printf("\t|                                                   |\n");
	printf("\t|---++Attacking++                                   |\n");
	printf("\t|                                                   |\n");
	printf("\t| + Mouse Left-Button to shoot                      |\n");
	printf("\t| + To do Melee you just have to bee in the same    |\n");
	printf("\t| square as yout enemy.                             |\n");
	printf("\t|                                                   |\n");
	printf("\t|---++What OBJECTS ARE AVAILABLE?++                 |\n");
	printf("\t|                                                   |\n");
	printf("\t| Bandages - Heal yout wounds                       |\n");
	printf("\t| Bullets  - To refill your bullets                 |\n");
	printf("\t| Dinamyte - To open final door                     |\n");
	printf("\t|                                                   |\n");
	printf("\t|---++How do I open the Final door?++               |\n");
	printf("\t|                                                   |\n");
	printf("\t| First, you have to find the final door witch is   |\n");
	printf("\t| already a big challange! Then you must have the   |\n");
	printf("\t| required amount of dinamyte and finnally.......   |\n");
	printf("\t| just press 'Q' in front of the door! :)           |\n");
	printf("\t|                                                   |\n");
	printf("\t|---++Too Easy?++                                   |\n");
	printf("\t|                                                   |\n");
	printf("\t| If you don't know, there is menu in the game, you |\n");
	printf("\t| can open it clicking in the mouse's right button. |\n");
	printf("\t| From the diferent options, you have the ones that |\n");
	printf("\t| regulate the dificulty.                           |\n");
	printf("\t+---------------------------------------------------+\n");
	
}



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
#define FIX 0.2
int monsterShoot_coolDownTime = 0;
int characterShoot_coolDownTime = 0;
int characterShootingAnimation_coolDownTime = 0;
int characterReload_coolDownTime = 0;
int monsterMelee_coolDownTime = 0;
int characterMelee_coolDownTime = 0;
bool m_meleeDone = false, m_shootDone = false, c_shootDone = false, c_meleeDone =  false;
bool first = true;
void TimerFunction(int value)
{

		if (!gameWon) {


			if (reloading2) {
				characterReload_coolDownTime = 100;
				reloading2 = false;
			}

			if (characterReload_coolDownTime > 0) {
				characterReload_coolDownTime--;
				
			}
			if (characterReload_coolDownTime <= 0) {
				reloading = false;
			}

			if (shootingAnimation2) {
				characterShootingAnimation_coolDownTime = 70;
				shootingAnimation2 = false;
			}

			if (characterShootingAnimation_coolDownTime > 0) {
				characterShootingAnimation_coolDownTime--;

			}
			if (characterShootingAnimation_coolDownTime <= 0) {
				shootingAnimation = false;
				myCharacter->Shooting(false);
			}

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
			if (characterMelee_coolDownTime > 0) {
				characterMelee_coolDownTime -= 0.1;
				c_meleeDone = false;
			}

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
					myCharacter->InitModelTerceicaPessoa();
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
				myCharacter->InitModelPrimeiraPessoa();
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
					myCharacter->Moving(true);
					if (view == VIEW_FIRST_PERSON) {
						if (board->IsOpen(myCharacter->x  + MOVE_RATIO * cos(myCharacter->angle - RAD(90)), myCharacter->y  + MOVE_RATIO * sin(myCharacter->angle - RAD(90))))
						{
							myCharacter->x += MOVE_RATIO * cos(myCharacter->angle - RAD(90));
							myCharacter->y += MOVE_RATIO * sin(myCharacter->angle - RAD(90));
						}
						//Open doors wih 3 dynamites (pressing 'Q')
						if (GetAsyncKeyState(TECLA_Q) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {
							if (board->IsDoor(myCharacter->x  + MOVE_RATIO * cos(myCharacter->angle - RAD(90)), myCharacter->y  + MOVE_RATIO * sin(myCharacter->angle - RAD(90))))
							{
								board->OpenDoor(myCharacter->x  + MOVE_RATIO * cos(myCharacter->angle - RAD(90)), myCharacter->y + MOVE_RATIO * sin(myCharacter->angle - RAD(90)));
								gameWon = true;
							}
						}
					}
					else {
						if (board->IsOpen(myCharacter->x, myCharacter->y - FIX - MOVE_RATIO))
						{
							myCharacter->y -= MOVE_RATIO;
						}
						//Open doors wih 3 dynamites (pressing 'Q')
						if (GetAsyncKeyState(TECLA_Q) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {
							if (board->IsDoor(myCharacter->x, myCharacter->y - FIX - MOVE_RATIO))
							{
								board->OpenDoor(myCharacter->x, myCharacter->y - FIX - MOVE_RATIO);
								gameWon = true;
							}
						}
					}

				}else

				//move left
				if (GetAsyncKeyState(TECLA_A) && !GetAsyncKeyState(TECLA_D))
				{
					myCharacter->Moving(true);
					if (view == VIEW_FIRST_PERSON) {
						if (board->IsOpen(myCharacter->x  + MOVE_RATIO * cos(myCharacter->angle + RAD(90)), myCharacter->y + MOVE_RATIO * sin(myCharacter->angle + RAD(90))))
						{
							myCharacter->x += MOVE_RATIO * cos(myCharacter->angle + RAD(90));
							myCharacter->y += MOVE_RATIO * sin(myCharacter->angle + RAD(90));
						}
						//Open doors wih 3 dynamites (pressing 'Q')
						if (GetAsyncKeyState(TECLA_Q) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {
							if (board->IsDoor(myCharacter->x + MOVE_RATIO * cos(myCharacter->angle + RAD(90)), myCharacter->y +MOVE_RATIO * sin(myCharacter->angle + RAD(90))))
							{
								board->OpenDoor(myCharacter->x  + MOVE_RATIO * cos(myCharacter->angle + RAD(90)), myCharacter->y + MOVE_RATIO * sin(myCharacter->angle + RAD(90))); gameWon = true;
							}
						}
					}
					else {
						if (board->IsOpen(myCharacter->x, myCharacter->y + FIX + MOVE_RATIO))
						{
							myCharacter->y += MOVE_RATIO;
						}
						//Open doors wih 3 dynamites (pressing 'Q')
						if (GetAsyncKeyState(TECLA_Q) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {
							if (board->IsDoor(myCharacter->x, myCharacter->y + FIX + MOVE_RATIO))
							{
								board->OpenDoor(myCharacter->x, myCharacter->y + FIX + MOVE_RATIO); gameWon = true;
							}
						}
					}


				}
				else
				//move up
				if (GetAsyncKeyState(TECLA_W) && !GetAsyncKeyState(TECLA_S))
				{
					myCharacter->Moving(true);

					if (view == VIEW_FIRST_PERSON) {
						if (board->IsOpen(myCharacter->x+ MOVE_RATIO * cos(myCharacter->angle), myCharacter->y + MOVE_RATIO * sin(myCharacter->angle)))
						{
							myCharacter->x += MOVE_RATIO * cos(myCharacter->angle);
							myCharacter->y += MOVE_RATIO * sin(myCharacter->angle);
						}

						if (GetAsyncKeyState(TECLA_Q) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {//Open doors wih 3 dynamites (pressing 'Q')
							if (board->IsDoor(myCharacter->x + MOVE_RATIO * cos(myCharacter->angle), myCharacter->y  + MOVE_RATIO * sin(myCharacter->angle)))
							{
								board->OpenDoor(myCharacter->x + MOVE_RATIO * cos(myCharacter->angle), myCharacter->y + MOVE_RATIO * sin(myCharacter->angle)); gameWon = true;
							}
						}
					}
					else { //3rd view or map
						if (board->IsOpen(myCharacter->x + FIX + MOVE_RATIO, myCharacter->y))
						{
							myCharacter->x += MOVE_RATIO;
						}
						if (GetAsyncKeyState(TECLA_Q) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {//Open doors wih 3 dynamites (pressing 'Q')
							if (board->IsDoor(myCharacter->x + FIX + MOVE_RATIO, myCharacter->y))
							{
								board->OpenDoor(myCharacter->x + FIX + MOVE_RATIO, myCharacter->y); gameWon = true;
							}
						}
					}



				}
				else
				//move down
				if (GetAsyncKeyState(TECLA_S) && !GetAsyncKeyState(TECLA_W))
				{
					myCharacter->Moving(true);
					//printf(" S - DOWN - NEXTPOS = [x = %f][y = %f]\n", round(myCharacter->x + -MOVE_RATIO * cos(myCharacter->angle)-0.5), round(myCharacter->y + MOVE_RATIO * sin(myCharacter->angle)));
					if (view == VIEW_FIRST_PERSON) {
						if (board->IsOpen(myCharacter->x - MOVE_RATIO * cos(myCharacter->angle), myCharacter->y  - MOVE_RATIO * sin(myCharacter->angle)))
						{
							myCharacter->x -= MOVE_RATIO * cos(myCharacter->angle);
							myCharacter->y -= MOVE_RATIO * sin(myCharacter->angle);
						}

						if (GetAsyncKeyState(TECLA_Q) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {

							if (board->IsDoor(myCharacter->x  - MOVE_RATIO * cos(myCharacter->angle), myCharacter->y  - MOVE_RATIO * sin(myCharacter->angle)))
							{
								board->OpenDoor(myCharacter->x  - MOVE_RATIO * cos(myCharacter->angle), myCharacter->y - MOVE_RATIO * sin(myCharacter->angle)); gameWon = true;
							}

						}
					}
					else {
						if (board->IsOpen(myCharacter->x - FIX - MOVE_RATIO, myCharacter->y))
						{
							myCharacter->x -= MOVE_RATIO;
						}

						if (GetAsyncKeyState(TECLA_Q) && myCharacter->dynamiteFound == DYNAMITE_NEEDED) {

							if (board->IsDoor(myCharacter->x - FIX - MOVE_RATIO, myCharacter->y))
							{
								board->OpenDoor(myCharacter->x - FIX - MOVE_RATIO, myCharacter->y); gameWon = true;
							}

						}
					}
					//Open doors wih 3 dynamites (pressing 'Q')


				}
				else
					myCharacter->Moving(false);
				for (int i = 0; i < NUM_MONSTROS_RANDOM; i++)
					if (monstros[i]->killed == false && monstros[i]->patrol)
						monstros[i]->MoveTo();



				for (int i = 0; i < NUM_MONSTROS_RANDOM; i++) {
					if (myCharacter->x <= monstros[i]->x + 0.5 && myCharacter->x >= monstros[i]->x - 0.5 && myCharacter->y <= monstros[i]->y + 0.5 && myCharacter->y >= monstros[i]->y - 0.5) {
						if (monsterMelee_coolDownTime == 0) {
							m_meleeDone = true;
							myCharacter->lives -= MONSTER_DAMAGE_MELEE;
						}
						if (characterMelee_coolDownTime <= 0) {
							c_meleeDone = true;
							monstros[i]->lives -= CHARACTER_DAMAGE_MELEE;
							if (monstros[i]->lives <= 0) {
								monstros[i]->x = -5;
								monstros[i]->killed = true;
							}
						}
					}
				}



				if (c_bullet->shoot) { //if character shoot a bullet...
					
					if (board->IsOpen(c_bullet->x, c_bullet->y))c_bullet->Move();
					for (int i = 0; i < NUM_MONSTROS_RANDOM; i++) {
						if (!monstros[i]->killed) {
							if ((monstros[i]->x <= c_bullet->x + BULLET_SPEED && monstros[i]->x >= c_bullet->x - BULLET_SPEED) && (monstros[i]->y <= c_bullet->y + BULLET_SPEED && monstros[i]->y >= c_bullet->y - BULLET_SPEED)) {
								monstros[i]->lives -= CHARACTER_DAMAGE_SHOOT;

								if (monstros[i]->lives <= 0) {
									monstros[i]->killed = true;
									monstros[i]->x = -5;
								}
							}

						}
					}
				}


				for (int i = 0; i < NUM_MONSTROS_RANDOM; i++) {
					if (monstros[i]->shooting) {
						if (board->IsOpen(monstros[i]->bullet->x, monstros[i]->bullet->y)) {
							monstros[i]->updateShootingAngle(myCharacter->x, myCharacter->y);
							monstros[i]->bullet->updateAngle(monstros[i]->shootingAngle);
							monstros[i]->bullet->Move2();
						}

						if ((myCharacter->x <= monstros[i]->bullet->x + BULLET_SPEED*2.0 && myCharacter->x >= monstros[i]->bullet->x - BULLET_SPEED*2.0) && (myCharacter->y <= monstros[i]->bullet->y + BULLET_SPEED*2.0 && myCharacter->y >= monstros[i]->bullet->y - BULLET_SPEED*2.0)) {
							monstros[i]->bullet->draw = false;
							myCharacter->lives -= MONSTER_DAMAGE_SHOOT;
						}

					}

				}


				int posValue = board->getBoardValue(myCharacter->y, myCharacter->x);

				for (int i = 0; i < NUM_MONSTROS_RANDOM; i++) {
					if (monstros[i]->startIndexMonster + BASE_INDEX_MONSTERS == posValue) {
						switch (monstros[i]->alert(myCharacter->y, myCharacter->x)) {
						case 1://melee aready done in timer
							break;
						case 2://shooting
							monstros[i]->shooting = true;
							monstros[i]->patrol = false;
							if (monsterShoot_coolDownTime <= 0) {
								monstros[i]->shoot(myCharacter->y, myCharacter->x);
								monstros[i]->bullet->draw = true;
								m_shootDone = true;
							}
							break;
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
					gameWon = true;
				}
				if (GetAsyncKeyState(VK_F4) && !GetAsyncKeyState(VK_F3)) { //F4 - Não atribuido
					
				}
				if (GetAsyncKeyState(VK_F5) && !GetAsyncKeyState(VK_F6)) { //F5 - Não atribuido
				}
				if (GetAsyncKeyState(VK_F6) && !GetAsyncKeyState(VK_F5)) { //F6 - Não atribuido
				}
			}

		}
else {

	drawGameWon();

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

void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && characterShoot_coolDownTime <= 0 && numBullets > 0) {
		numBullets--;
		c_shootDone = true;
		if (state == GLUT_DOWN) {
			float _yaw = camera->yaw;
			float _pitch = camera->pitch;
			c_bullet->setInitial(myCharacter->x, myCharacter->y, _yaw,_pitch);
			c_bullet->shoot = true;
			myCharacter->Shooting(true);
			shootingAnimation = true;
			shootingAnimation2 = true;
			bulletConfig();
		}

	}
}

static int menu_id;
static int submenu_id;
static int window;
static int value = 0;
static int dificulty = 4;
bool fullscreen = false;
void menu(int num) {
	if (num == 0) {
		glutDestroyWindow(window);
		exit(0);
	}
	else if (num == 1) {
		if (dificulty==3) {
			numDynamite = 2;
			numBullets = 15;
			myCharacter->lives = NUM_LIVES;
			myCharacter->retrys = NUM_RETRYS + 2;
			init();
			board->tp_restore();
			gameover = false;
			board = new Board();
			board->GenerateRandoMonstersPositions();
			for (int IndexMonster = 0; IndexMonster < NUM_MONSTROS_RANDOM; IndexMonster++) {
				monstros[IndexMonster] = new Monster(board->VecPositionMonsters[IndexMonster].coluna, board->VecPositionMonsters[IndexMonster].linha, CHARACTER_SIZE, IndexMonster, board);
			}
			dificulty = num;
			board->generateRandomObjectsPosition(dificulty);
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
		}else if (dificulty == 4) {
			numDynamite = 1;
			numBullets = 6;
			myCharacter->lives = NUM_LIVES;
			myCharacter->retrys = NUM_RETRYS;
			init();
			board->tp_restore();
			gameover = false;
			board->GenerateRandoMonstersPositions();
			for (int IndexMonster = 0; IndexMonster < NUM_MONSTROS_RANDOM; IndexMonster++) {
				monstros[IndexMonster] = new Monster(board->VecPositionMonsters[IndexMonster].coluna, board->VecPositionMonsters[IndexMonster].linha, CHARACTER_SIZE, IndexMonster, board);
			}
			dificulty = num;
			board->generateRandomObjectsPosition(dificulty);
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
		}else if (dificulty == 3) {
			numDynamite = 0;
			numBullets = 3;
			myCharacter->lives = NUM_LIVES-50;
			myCharacter->retrys = NUM_RETRYS -1;
			init();
			board->tp_restore();
			gameover = false;
			board->GenerateRandoMonstersPositions();
			for (int IndexMonster = 0; IndexMonster < NUM_MONSTROS_RANDOM; IndexMonster++) {
				monstros[IndexMonster] = new Monster(board->VecPositionMonsters[IndexMonster].coluna, board->VecPositionMonsters[IndexMonster].linha, CHARACTER_SIZE, IndexMonster, board);
			}
			dificulty = num;
			board->generateRandomObjectsPosition(dificulty);
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
		}
	}
	else if (num == 2) {
		glutFullScreen();
	}
	else if (num == 3) {
		numDynamite = 2;
		numBullets = 15;
		myCharacter->lives = NUM_LIVES;
		myCharacter->retrys = NUM_RETRYS + 2;
		init();
		board->tp_restore();
		gameover = false;
		board->GenerateRandoMonstersPositions();
		for (int IndexMonster = 0; IndexMonster < NUM_MONSTROS_RANDOM; IndexMonster++) {
			monstros[IndexMonster] = new Monster(board->VecPositionMonsters[IndexMonster].coluna, board->VecPositionMonsters[IndexMonster].linha, CHARACTER_SIZE, IndexMonster, board);
		}
		dificulty = num;
		board->generateRandomObjectsPosition(dificulty);
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
	}
	else if (num == 4) {
		numDynamite = 1;
		numBullets = 6;
		myCharacter->lives = 100;
		myCharacter->retrys = NUM_RETRYS;
		init();
		board->tp_restore();
		gameover = false;
		board = new Board();
		board->GenerateRandoMonstersPositions();
		for (int IndexMonster = 0; IndexMonster < NUM_MONSTROS_RANDOM; IndexMonster++) {
			monstros[IndexMonster] = new Monster(board->VecPositionMonsters[IndexMonster].coluna, board->VecPositionMonsters[IndexMonster].linha, CHARACTER_SIZE, IndexMonster, board);
		}
		dificulty = num;
		board->generateRandomObjectsPosition(dificulty);
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
	}
	else if (num == 5) {
		numDynamite = 0;
		numBullets = 3;
		myCharacter->lives = 50;
		myCharacter->retrys = NUM_RETRYS - 1;
		init();
		board->tp_restore();
		gameover = false;
		board = new Board();
		board->GenerateRandoMonstersPositions();
		for (int IndexMonster = 0; IndexMonster < NUM_MONSTROS_RANDOM; IndexMonster++) {
			monstros[IndexMonster] = new Monster(board->VecPositionMonsters[IndexMonster].coluna, board->VecPositionMonsters[IndexMonster].linha, CHARACTER_SIZE, IndexMonster, board);
		}
		dificulty = num;
		board->generateRandomObjectsPosition(dificulty);
		for (int k = 0; k < nr_objets - 3; k++) {
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
	}
}

void createMenu(void) {

	submenu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Easy", 3);
	glutAddMenuEntry("Medium", 4);
	glutAddMenuEntry("Hard", 5);
	menu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Restart", 1);
	glutAddMenuEntry("FullScreen", 2);
	glutAddSubMenu("Difficulty", submenu_id);
	glutAddMenuEntry("Quit", 0);     
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}


int main(int argc, char **argv) {


	info();
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	if (!FULLSCREEN) {
		//windowed mode
		glutInitWindowSize(1080, 820);
		window=glutCreateWindow("Labirinto 3D");
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
	board->generateRandomObjectsPosition(dificulty);

	for (int IndexMonster = 0; IndexMonster < NUM_MONSTROS_RANDOM; IndexMonster++) {
		monstros[IndexMonster] = new Monster(board->VecPositionMonsters[IndexMonster].coluna, board->VecPositionMonsters[IndexMonster].linha,CHARACTER_SIZE, IndexMonster, board);
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

	createMenu();
	

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