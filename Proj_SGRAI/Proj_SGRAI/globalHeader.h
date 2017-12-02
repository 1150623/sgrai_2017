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
#define MOVE_RATIO 0.02
#define DYNAMITE_NEEDED 3
#define HIDE_MOUSE 1
#define CUTOFF 30
#define LAB_SIZE 31 //must be an odd number

//TEXTURES INFO
#define NUM_TEXTURES 2
#define TEXTURE_FLOOR_1 "Texturas/FLOOR1_128_128.ppm" //FLOOR{Nr_IMAGE}_128_128.ppm
#define TEXTURE_FLOOR_2 "Texturas/FLOOR2_128_128.ppm" //FLOOR{Nr_IMAGE}_128_128.ppm
#define TEXTURE_FLOOR_3 "Texturas/FLOOR3_128_128.ppm" //FLOOR{Nr_IMAGE}_128_128.ppm
#define TEXTURE_FLOOR_4 "Texturas/FLOOR4_128_128.ppm" //FLOOR{Nr_IMAGE}_128_128.ppm
#define TEXTURE_WALL_1 "Texturas/WALL1_128_128.ppm"	//WALL{Nr_IMAGE}_128_128.ppm


//CHARACTER
#define NUM_LIVES 50
#define CHAR_ANGLE 0
#define CHAR_SPEED 0.2
#define CHARACTER_SIZE 0.25
#define CHARACTER_STARTLOCATION_X 1
#define CHARACTER_STARTLOCATION_Y 17
#define SCALE_PLAYER         0.005

//Monstros
#define NUM_MONSTROS_RANDOM 10
#define BASE_INDEX_MONSTERS 10
#define MONSTER_SPEED 0.008

//Objetos

#define BANDAGES 1
#define BULLETS 2
#define DYNAMITE 3

#define NUM_DYNAMITES 1
#define NUM_BANDAGES 10
#define NUM_BULLETS 5

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


}

#endif