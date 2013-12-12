#pragma once

#include "Vector4.h"
#include "BoundingBox.h"

class Building
{
private:
	Vector4 position;
	Vector4 size;

	float sphere_size;

	bool wall_part;

	enum { Sphere , Cube  } type;

	bool crashed;
    
    int damage;

public:
	Building(int d, float size,float,float,float,bool);
	~Building();

	Vector4 getPosition() const;
	int getDepth() const;

	void draw() const;
    void draw_wall_part() const; 
	BoundingBox getBox() const;
    
    void addDamage(int);
    int getDamage();

	void crash() { crashed = true; }
};

