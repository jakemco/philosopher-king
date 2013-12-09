#pragma once

#include "camera.h"

#include "Vector4.h"
#include "Matrix4.h"

class MoveableCamera : public Camera {
    
private:
	Matrix4 matrix;
	
	Vector4 e;
	Vector4 d;
	Vector4 up;

	Vector4 forward;
	Vector4 right;

public:
	MoveableCamera(const Vector4& e, const Vector4& d, const Vector4& up);

	void moveForward(float distance);
	void moveRight(float distance);

	void lookLeft(float degrees);
	void lookUp(float degrees);
    
    void setPosition(const Vector4& position);
    Vector4 getPosition();

	void update();
	virtual Matrix4& getMatrix();
};

