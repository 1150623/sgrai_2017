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
	//draw spheare
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
	printf("Bullet x: %d\n", x);
	printf("Bullet y: %d\n", y);

	x += BULLET_SPEED * cos(yaw) * cos(pitch);
	y += BULLET_SPEED * sin(yaw) * cos(pitch);
	z += BULLET_SPEED * sin(-pitch);
	printf("Monster x: %d\n", x_dest);
	printf("Monster y: %d\n", y_dest);
	if (x_dest == (int)x && y_dest == (int)y) {
		printf("Acertou", y);
		shoot = false;
	}
}