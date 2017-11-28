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




#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif


//MAIN GLOBAL INFO
#define TEXTURE_ON 1
#define FULLSCREEN 1
#define DEBBUG 1
#define MOVE_RATIO 0.25
#define DYNAMITE_NEEDED 3
#define HIDE_MOUSE 1


//TEXTURES INFO
#define NUM_TEXTURES 2
#define TEXTURE_FLOOR_1 "Texturas/FLOOR4_128_128.ppm" //FLOOR{Nr_IMAGE}_128_128.ppm
#define TEXTURE_FLOOR_2 "Texturas/FLOOR4_128_128.ppm" //FLOOR{Nr_IMAGE}_128_128.ppm
#define TEXTURE_FLOOR_3 "Texturas/FLOOR4_128_128.ppm" //FLOOR{Nr_IMAGE}_128_128.ppm
#define TEXTURE_FLOOR_4 "Texturas/FLOOR4_128_128.ppm" //FLOOR{Nr_IMAGE}_128_128.ppm
#define TEXTURE_WALL_1 "Texturas/WALL1_128_128.ppm"	//WALL{Nr_IMAGE}_128_128.ppm


//CHARACTER
#define NUM_LIVES 3
#define CHAR_ANGLE 0
#define CHAR_SPEED 0.2
#define CHARACTER_SIZE 0.25
#define CHARACTER_STARTLOCATION_X 1
#define CHARACTER_STARTLOCATION_Y 17

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