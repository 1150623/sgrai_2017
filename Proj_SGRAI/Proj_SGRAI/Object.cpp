#include "Object.h"
#include <stdio.h>
#include <GL/glut.h>
#include <Math.h>


// Destructor
Object::~Object(void) {}
Board board_o;

Object::Object(int type_o, float x_o, float y_o, float size_o, Board b)
{
	mdlviewer_init("bandage.mdl", bandage);
	mdlviewer_init("bullets.mdl", bullet);
	mdlviewer_init("dynamite.mdl", dynamite);
	type = type_o;
	x = x_o+0.5;
	y = y_o+0.5;
	size = size_o;
	board_o = b;
	got_it = false;
}

void Object::Draw(void)
{
	//draw object
	if (Object::got_it==false) {
		if (type == BANDAGES) {
			glPushMatrix();
			{

				glTranslatef(Object::x, Object::y, size);
				glScalef(SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01);
				mdlviewer_display(bandage);

			}
			glPopMatrix();
		}
		else if (type == BULLETS) {
			glPushMatrix();
			{
				glTranslatef(Object::x, Object::y, size);
				glScalef(SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01);
				mdlviewer_display(bullet);

			}
			glPopMatrix();
		}
		else if (type == DYNAMITE) {
			glColor3f(0, 0, 10);
			glPushMatrix();
			{
				glTranslatef(Object::x, Object::y, size-0.3);
				glScalef(SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01, SCALE_PLAYER + 0.01);
				mdlviewer_display(dynamite);
				//glutSolidSphere(size / 2, 10, 10);

			}
			glPopMatrix();
		}
	}
	
}
