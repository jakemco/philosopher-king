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

void Ship::update(float dt, float x, float y, float controlsX) {
	if (!crashed) {
		Vector4 destination(position.x() + x, position.y() + y, position.z() - SPEED, 1.0f);
		Vector4 dir = Vector4::normalize(destination - position)*SPEED*dt;

		this->rotate = Vector4::cross(Vector4(0, 0, -1), dir);
		this->angle = Vector4::angle(Vector4(0, 0, -1), dir);
		
		this->zrotAngle = -controlsX;

		this->position += dir;
	}
}

void Ship::render() {
	glPushMatrix();
	
	glTranslatef(this->position.x(), this->position.y(), this->position.z());
	glRotatef(this->zrotAngle * 180.0 / M_PI, 0, 0, 1);
    glRotatef(this->angle * 180.0 / M_PI, this->rotate.x(), this->rotate.y(), this->rotate.z());

    ShapeGrammar::maxPartRange();
    float scale = 2 * ShapeGrammar::scaleSize;
    glScalef(1 / scale, 1 / scale, 1 / scale);

	if (crashed) glColor3f(1.0, 0.2, 0.2);
    else glColor3f(1,1,1);

    ShapeGrammar::designShip();
    
	glPopMatrix();
}

Vector4 Ship::getPosition() const {
    return this->position;
}

BoundingBox Ship::getBox() const {    
    float xRange, yRange, zRange, scale;
    scale = 2 * ShapeGrammar::scaleSize;
    xRange = (ShapeGrammar::maxVerts.get(0) - ShapeGrammar::minVerts.get(0)) / scale;
    yRange = (ShapeGrammar::maxVerts.get(1) - ShapeGrammar::minVerts.get(1)) / scale;
    zRange = (ShapeGrammar::maxVerts.get(2) - ShapeGrammar::minVerts.get(2)) / scale;
    return BoundingBox(this->position, xRange, yRange, zRange);
}

void Ship::crash() {
	crashed = true;
}

void Ship::reset() {
	this->position = Vector4(0, 0, 0, 1);
	this->crashed = false;
}