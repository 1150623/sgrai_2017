#pragma once

#ifndef _GLOBALHEADER_H_
#define _GLOBALHEADER_H_


#include <time.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
#include <gl/glut.h>


#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif


//MAIN GLOBAL INFO
#define DEBBUG 1
#define BOARD_SCALE_DEFAULT 1
#define MOVE_RATIO 1

//CHARACTER
#define NUM_LIVES 3
#define CHAR_ANGLE 30
#define CHAR_SPEED 0.2
#define CHARACTER_SIZE 1
#define CHARACTER_STARTLOCATION_X 14
#define CHARACTER_STARTLOCATION_Y 23

#endif