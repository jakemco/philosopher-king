#include <cstdlib>
#include "GLee.h"
#ifdef WIN32
  #include "GL/glut.h"
#else
  #include "GLUT/glut.h"
#endif

#define _USE_MATH_DEFINES
#include <cmath>

#include "Laser.h"

const float Laser::SPEED = 100.0f;

Laser::Laser(const Vector4& start, const Vector4& target, const Vector4& color) : start(start)
{
	this->color = color;
	this->position = start;
	this->direction = Vector4::normalize(target - start);
}

Laser::Laser(const Vector4& s, const Vector4& t) : Laser(s, t, Vector4(0, 1, 0)) {}


Laser::~Laser()
{
}

void Laser::update(float dt) {
	this->position += direction*Laser::SPEED*dt;
}

void Laser::render() {
	glPushMatrix();

	glTranslatef(position.x(), position.y(), position.z());
	Vector4 rotate = Vector4::cross(Vector4(0, 0, -1), direction);
	glRotatef(Vector4::angle(Vector4(0, 0, -1), direction) * 180.0 / M_PI, rotate.x(), rotate.y(), rotate.z());
	glScalef(0.05, 0.05, 5);

	glColor3f(color.x(), color.y(), color.z());
	glutSolidCube(1.0);

	glPopMatrix();
}

Vector4 Laser::getPosition() {
	return this->position;
}

bool Laser::dead(float range) {
	return (position - start).length() > range;
}
