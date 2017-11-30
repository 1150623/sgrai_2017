#include "Bullet.h"

// Destructor
Bullet::~Bullet(void) {}
//Constructor (inicializa)
Bullet::Bullet()
{
	Bullet::size = 0.005;
	shoot = false;
}

void
Bullet::setInitial(float _x, float _y, float _angle) {
	x = _x;
	y = _y;
	angle = _angle;

}

void
Bullet::Draw()
{
	//draw spheare
	glColor3f(0, 1, 0);
	glPushMatrix();
	{

		glTranslatef(x, y, 0.45);
		/*glTranslatef(x, -y + CHARACTER_SIZE * 2, -CHARACTER_SIZE);
		glTranslatef(CHARACTER_SIZE / 2, CHARACTER_SIZE + 0.12, 0);
		glTranslatef((float)31 / -2, (float)28 / 2.0, 0.73);*/

		glutSolidSphere(size / 2, 10, 10);
	}
	glPopMatrix();
}
void
Bullet::Move() {
	printf("Monster x: %d\n", x);
	printf("Monster y: %d\n", y);
	x += BULLET_SPEED *cos(angle);
	y += BULLET_SPEED *sin(angle);
	if (x_dest == (int)x && y_dest == (int)y)
		shoot = false;
}