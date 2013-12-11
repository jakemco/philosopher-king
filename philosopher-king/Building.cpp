
#include <cstdlib>

#ifdef WIN32
  #include "GL/glut.h"
#else
  #include "GLUT/glut.h"
#endif

#include <iostream>
#include <ctime>

#include "Building.h"

#define RAND_FLOAT(min,max) ((min) + (((float)rand()/(float)RAND_MAX)*((max) - (min))))

Building::Building(int d, float size)
{
	float x = RAND_FLOAT(1, 10);
	float y = RAND_FLOAT(1, 3);
	float h = RAND_FLOAT(1, size);
	float t = RAND_FLOAT(0, 1);
	
	if (t < 0.4) {
		type = Sphere;
		sphere_size = RAND_FLOAT(0.5, 2);
	}
	else type = Cube;

	float s = RAND_FLOAT(0, 1);
	if (s < 0.3) {
		//left
		this->position = Vector4(
			(-size / 2) + (type == Cube ? h/2 : 0),
			RAND_FLOAT(-size/2,size/2),
			d,1);
		this->size = Vector4(h, y, x);
	}
	else if (s < 0.6) {
		//right
		this->position = Vector4(
			(size / 2) - (type == Cube ? h / 2 : 0),
			RAND_FLOAT(-size / 2, size / 2),
			d,1);
		this->size = Vector4(h, y, x);
	}
	else {
		//bottom
		this->position = Vector4(
			RAND_FLOAT(-size / 2, size / 2),
			-size / 2 + (type == Cube ? h / 2 : 0),
			d,1);
		this->size = Vector4(y, h, x);
	}

	crashed = false;

	/*
	std::cout << (type == Sphere ? "Sphere" : "Cube") << " at " << d << ": " << std::endl;
	std::cout << "\t";  position.print();
	std::cout << "\t";  size.print();
	*/

}

Building::~Building() {}

Vector4 Building::getPosition() const {
	return this->position;
}

int Building::getDepth() const {
	return this->position.z();
}

void Building::draw() const {

	glPushMatrix();

	glTranslatef(position.x(), position.y(), position.z());

	if (crashed) glColor3f(1.0, 0.2, 0.2);
	else glColor3f(1.0, 1.0, 1.0);

	if (type == Sphere) glutSolidSphere(sphere_size, 20, 20);
	else if (type == Cube) {
		glScalef(size.x(), size.y(), size.z());
		glutSolidCube(1.0);
	}

	glPopMatrix();
}

BoundingBox Building::getBox() const {
	if (type == Sphere)
		return BoundingBox(this->position, this->sphere_size * 2, this->sphere_size * 2, this->sphere_size * 2);
	else
		return BoundingBox(this->position, this->size.x(), this->size.y(), this->size.z());
}