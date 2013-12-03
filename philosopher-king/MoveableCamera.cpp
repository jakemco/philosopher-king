#include "MoveableCamera.h"


MoveableCamera::MoveableCamera(const Vector4& e, const Vector4& d, const Vector4& up)
{
	this->e = e;
	this->d = d;
	this->up = up;

	this->update();
}

void MoveableCamera::moveForward(float distance) {
	Vector4 movement = this->forward * distance;
	this->e += movement;
	this->d += movement;

	this->update();
}

void MoveableCamera::moveRight(float distance) {
	Vector4 movement = this->right * distance;
	this->e += movement;
	this->d += movement;

	this->update();
}

void MoveableCamera::lookLeft(float degree) {

	this->d -= e;
	this->d = Matrix4::rotate(this->up, degree) * this->d;
	this->d += e;

	this->update();
}

void MoveableCamera::lookUp(float degree) {
	this->d -= e;
	this->d = Matrix4::rotate(this->right, degree) * this->d;
	this->d += e;

	this->update();
}

void MoveableCamera::update() {
	Vector4 z = Vector4::normalize(this->e - this->d);
	Vector4 x = Vector4::normalize(Vector4::cross(this->up, z));
	Vector4 y = Vector4::normalize(Vector4::cross(z, x));

	this->forward = -z;
	this->right = x;

	double a[4][4] = {
		{ x[0], y[0], z[0], e[0] },
		{ x[1], y[1], z[1], e[1] },
		{ x[2], y[2], z[2], e[2] },
		{ 0, 0, 0, 1 }
	};

	this->matrix = Matrix4(a).rtInverse();
}

Matrix4& MoveableCamera::getMatrix() { return this->matrix; }