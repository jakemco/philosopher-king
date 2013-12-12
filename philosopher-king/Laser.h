#pragma once

#include "Vector4.h"

class Laser
{
private:
	Vector4 position;
	Vector4 direction;

public:
	static const float SPEED;

	Laser(const Vector4&, const Vector4&);
	~Laser();

	void update(float);
	void render();

	Vector4 getPosition();
};

