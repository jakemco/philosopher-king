//
//  Ship.cpp
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/8/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#include <cstdlib>

#ifdef WIN32
  #include "GL/glut.h"
#else
  #include "GLUT/glut.h"
#endif

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Ship.h"
#include "ShapeGrammar.h"

const float Ship::SPEED = 50.0f;

Ship::Ship() {
	this->reset();
}

void Ship::update(float dt, float x, float y) {
	if (!crashed) {
		Vector4 destination(position.x() + x, position.y() + y, position.z() - SPEED, 1.0f);
		Vector4 dir = Vector4::normalize(destination - position)*SPEED*dt;

		this->rotate = Vector4::cross(Vector4(0, 0, -1), dir);
		this->angle = Vector4::angle(Vector4(0, 0, -1), dir);

		this->position += dir;
	}
}

void Ship::render() {
	glPushMatrix();
	
	glTranslatef(this->position.x(), this->position.y(), this->position.z());
    glRotatef(this->angle * 180.0 / M_PI, this->rotate.x(), this->rotate.y(), this->rotate.z());

    float maxRange = ShapeGrammar::maxPartRange();
    glScalef(1 / maxRange, 1 / maxRange, 1 / maxRange);

	if (crashed) glColor3f(1.0, 0.2, 0.2);
    else glColor3f(1,1,1);

    ShapeGrammar::designShip();
    
	glPopMatrix();
}

Vector4 Ship::getPosition() const {
    return this->position;
}

BoundingBox Ship::getBox() const {
	return BoundingBox(this->position, 1, 1, 1);
}

void Ship::crash() {
	crashed = true;
}

void Ship::reset() {
	this->position = Vector4(0, 0, 0, 1);
	this->crashed = false;
}