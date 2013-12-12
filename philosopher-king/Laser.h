#pragma once

#include "Vector4.h"

class Laser
{
private:
	const Vector4 start;
	Vector4 position;
	Vector4 direction;

	Vector4 color;

public:
	static const float SPEED;

	Laser(const Vector4&, const Vector4&);
	Laser(const Vector4&, const Vector4&, const Vector4&);
	~Laser();

	void update(float);
	void render();

	bool dead(float);

	Vector4 getPosition();
};

