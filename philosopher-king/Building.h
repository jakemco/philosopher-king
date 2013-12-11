#pragma once

#include "Vector4.h"

class Building
{
private:
	Vector4 position;
	Vector4 size;

	float sphere_size;

	enum { Sphere , Cube  } type;


public:
	Building(int d);
	~Building();

	Vector4 getPosition() const;
	int getDepth() const;

	void draw() const;
};

inline bool operator>(const Building& a, const Building& b) {
	return a.getDepth() > b.getDepth();
}

