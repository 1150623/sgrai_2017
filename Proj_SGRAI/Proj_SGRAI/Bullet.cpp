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
Bullet::setInitial(float _x, float _y, float _yaw, float _pitch) {
	x = _x;
	y = _y;
	z = 0.5;
	yaw = _yaw;
	pitch = _pitch;

}

void
Bullet::Draw()
{
	//draw sphere
	glColor3f(0, 1, 0);
	glPushMatrix();
	{

		glTranslatef(x, y, z);

		glutSolidSphere(size / 2, 10, 10);
	}
	glPopMatrix();
}
void
Bullet::Move() {
	if (DEBBUG)printf("Bullet x: %d\n", x);
	if (DEBBUG)printf("Bullet y: %d\n", y);

	x += BULLET_SPEED * cos(yaw) * cos(pitch);
	y += BULLET_SPEED * sin(yaw) * cos(pitch);
	z += BULLET_SPEED * sin(-pitch);
	if (DEBBUG)printf("Monster x: %d\n", x_dest);
	if (DEBBUG)printf("Monster y: %d\n", y_dest);

}