#pragma once

#include "Vector4.h"
#include "Matrix4.h"

class StaticCamera
{
protected:
	Matrix4 matrix;

public:
	StaticCamera();
	StaticCamera(const Vector4& e, const Vector4& d, const Vector4& up);
	~StaticCamera();

	Vector4 e;
	Vector4 d;
	Vector4 up;
    Vector4 right;
    Vector4 y;

	void update(const Vector4& e, const Vector4& d, const Vector4& up);
	Matrix4& getMatrix();
};

