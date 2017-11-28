/***
*
*	Copyright (c) 1998, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
****/
#include "globalHeader.h"
#include "StudioModel.h"

extern vec3_t g_vright;		// needs to be set to viewer's right in order for chrome to work
extern float g_lambert;		// modifier for pseudo-hemispherical lighting

	typedef unsigned char 		byte;

	void mdlviewer_init( char *modelname, StudioModel &tempmodel );
	void mdlviewer_nextsequence( StudioModel &tempmodel );
	void mdlviewer_prevsequence( StudioModel &tempmodel );
	void mdlviewer_display( StudioModel &tempmodel );
