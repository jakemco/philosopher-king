#pragma once

#include <functional>

#include "Vector4.h"

class BoundingBox
{
private:
	Vector4 max;
	Vector4 min;

public:
	BoundingBox(const Vector4&,float,float,float);
	~BoundingBox();

	bool contains(const Vector4&) const;
	bool contains(const BoundingBox&) const;

	bool custom(std::function<bool(const Vector4&, const Vector4&)>) const;
};

