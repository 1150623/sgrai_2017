#include "Bullet.h"

// Destructor
Bullet::~Bullet(void) {}
//Constructor (inicializa)
Bullet::Bullet()
{
	Bullet::size = 0.005;
	shoot = false;
	draw = false;
}

void
Bullet::setSize(float _size) {
	size = _size;
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
	x += BULLET_SPEED * cos(yaw) * cos(pitch);
	y += BULLET_SPEED * sin(yaw) * cos(pitch);
	z += BULLET_SPEED * sin(-pitch);
}

void Bullet::Move2() {
	if (yaw == 180) {
		x -= BULLET_SPEED;
	}
	if (yaw == 90) {
		y += BULLET_SPEED;
	}
	if (yaw == 0) {
		x += BULLET_SPEED;
	}

	if (yaw == 270) {
		y -= BULLET_SPEED;
	}
}

void Bullet::updateAngle(float angle) {
	yaw = angle;
}