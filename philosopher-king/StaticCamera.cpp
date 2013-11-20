#include "StaticCamera.h"

#include <iostream>

StaticCamera::StaticCamera() {
	matrix.identity();
}

StaticCamera::~StaticCamera() {}



StaticCamera::StaticCamera(const Vector4& e, const Vector4& d, const Vector4& up) : StaticCamera() {
	this->update(e, d, up);
}

void StaticCamera::update(const Vector4& e, const Vector4& d, const Vector4& up) {
	this->e = e;
	this->d = d;
	this->up = up;

	Vector4 z = Vector4::normalize(e - d);
	Vector4 x = Vector4::normalize(Vector4::cross(up, z));
	Vector4 y = Vector4::normalize(Vector4::cross(z, x));
    
    this->y = y;
    this->right = x;

	double a[4][4] = {
		{ x[0], y[0], z[0], e[0] },
		{ x[1], y[1], z[1], e[1] },
		{ x[2], y[2], z[2], e[2] },
		{ 0, 0, 0, 1 }

	};

	//std::cout << "Camera Matrix:" << std::endl; Matrix4(a).print();

	this->matrix = Matrix4(a).rtInverse();
}

Matrix4& StaticCamera::getMatrix() { return this->matrix; } // this is C-inverse