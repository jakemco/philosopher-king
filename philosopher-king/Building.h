#pragma once

#include "Vector4.h"
#include "BoundingBox.h"

class Building
{
private:
	Vector4 position;
	Vector4 size;

	float sphere_size;

	enum { Sphere , Cube  } type;

	bool crashed;

public:
	Building(int d, float size);
	~Building();

	Vector4 getPosition() const;
	int getDepth() const;

	void draw() const;
	BoundingBox getBox() const;

	void crash() { crashed = true; }
};

inline bool operator>(const Building& a, const Building& b) {
	return a.getDepth() > b.getDepth();
}

