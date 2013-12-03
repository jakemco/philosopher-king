#pragma once

#include ""

class MoveableCamera
{
public:
	MoveableCamera(const Vector4& e, const Vector4& d, const Vector4& up);
	~MoveableCamera();

	Vector4 e;
	Vector4 d;
	Vector4 up;
	Vector4 right;
	Vector4 y;

	void update(const Vector4& e, const Vector4& d, const Vector4& up);
	Matrix4& getMatrix();
};

