#pragma once

#ifndef _GLOBALHEADER_H_
#define _GLOBALHEADER_H_

#include <iostream>
#include <iomanip>
#include <queue>
#include <ctime>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
#include <gl/glut.h>
#include <GL/gl.h>
#include "mathlib.h"
#include "studio.h"
#include "mathlib.h"
#include <conio.h>
#include <stack>
#include <fstream>
#include <vector>
#include <functional>
#include <set>




#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)


//MAIN GLOBAL INFO
#define TEXTURE_ON 1
#define FULLSCREEN 0
#define DEBBUG 1
//int DEBBUG = 1;
#define MOVE_RATIO 0.02
#define DYNAMITE_NEEDED 3
#define HIDE_MOUSE 1
#define CUTOFF 30
#define LAB_SIZE 31 //must be an odd number

//TEXTURES INFO
#define NUM_TEXTURES 3
#define TEXTURE_FLOOR_1 "Texturas/FLOOR1_128_128.ppm" //FLOOR{Nr_IMAGE}_128_128.ppm
#define TEXTURE_FLOOR_2 "Texturas/FLOOR2_128_128.ppm" //FLOOR{Nr_IMAGE}_128_128.ppm
#define TEXTURE_FLOOR_3 "Texturas/FLOOR3_128_128.ppm" //FLOOR{Nr_IMAGE}_128_128.ppm
#define TEXTURE_FLOOR_4 "Texturas/FLOOR4_128_128.ppm" //FLOOR{Nr_IMAGE}_128_128.ppm
#define TEXTURE_WALL_1 "Texturas/WALL1_128_128.ppm"	//WALL{Nr_IMAGE}_128_128.ppm
#define TEXTURE_START_IMAGE "Texturas/maze_initial_img.ppm"


//CHARACTER
#define NUM_LIVES 100
#define NUM_RETRYS 3
#define CHAR_ANGLE 0
#define CHAR_SPEED 0.2
#define CHARACTER_SIZE 0.25
#define CHARACTER_STARTLOCATION_X 1
#define CHARACTER_STARTLOCATION_Y 17
#define SCALE_PLAYER         0.005
#define CHARACTER_DAMAGE_SHOOT 25
#define CHARACTER_DAMAGE_MELEE 50
#define CHARACTER_SHOOT_COOLDOWN_TIME 40
#define CHARACTER_MELEE_COOLDOWN_TIME 75
#define NEEDED_DYNAMITES 3

//Monstros
#define NUM_MONSTROS_RANDOM 20
#define BASE_INDEX_MONSTERS 10
#define MONSTER_SPEED 0.008
#define MONSTER_LIFE 100
#define MONSTER_DAMAGE_SHOOT 10
#define MONSTER_DAMAGE_MELEE 15
#define MONSTER_SHOOT_COOLDOWN_TIME 75
#define MONSTER_MELEE_COOLDOWN_TIME 100
#define MONSTER_SHOOT_DIST 2.5
#define MONSTER_MELEE_DIST 0.5

//Objetos
#define BANDAGES 1
#define BULLETS 2
#define DYNAMITE 3

#define NUM_DYNAMITES NEEDED_DYNAMITES
#define NUM_BANDAGES 6
#define NUM_BULLETS 6

//Camera
#define VELOCIDADE_ROTACAO	0.01
#define VIEW_FIRST_PERSON	3
#define VIEW_THIRD_PERSON	0
#define VIEW_MAP	1



//BOARD GENERATION
#define START_POSITION_NUMBER 5
#define END_POSITION_NUMBER 6


extern "C" int read_JPEG_file(char *, char **, int *, int *, int *);

extern GLuint textName[];
extern char* textureFloor;
extern char* textureWall;

static void info() {
	printf("+---------------------------------+\n");
	printf("|          GLOBAL INFO            |\n");
	printf("+---------------------------------+\n");
	printf("| TEXTURES	[	%s	] |\n", TEXTURE_ON?"ON":"OFF");
	printf("| FULLSCREEN	[	%s	] |\n", FULLSCREEN ? "ON" : "OFF");
	printf("| DEBBUG	[	%s	] |\n", DEBBUG ? "ON" : "OFF");
	printf("+---------------------------------+\n");
	printf("+-----------------------------------------------+\n");
	printf("|					TEXTURE INFO		        |\n");
	printf("+-----------------------------------------------+\n");
	printf("| TEXTURE_WALL	[	%s	] |\n", textureWall);
	printf("| TEXTURE_Floor	[	%s	] |\n", textureFloor);
	printf("+-----------------------------------------------+\n");

	printf("\n\nPress 'H' for help...");
}

#endif