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

#include <cmath>
#include <iostream>

#include "Ship.h"

const float Ship::SPEED = 50.0f;

Ship::Ship() {
	this->position = Vector4(0, 0, 0, 1);
}

void Ship::update(float dt, float x, float y) {
    
	Vector4 destination(x, y, position.z() - SPEED, 1.0f);
	Vector4 dir = Vector4::normalize(destination - position)*SPEED*dt;

	this->rotate = Vector4::cross(Vector4(0, 0, -1), dir);
	this->angle = Vector4::angle(Vector4(0, 0, -1), dir);

	this->position += dir;
}

void Ship::render() {
	glPushMatrix();
	
	glTranslatef(this->position.x(), this->position.y(), this->position.z());
    glRotatef(this->angle * 180.0 / M_PI, this->rotate.x(), this->rotate.y(), this->rotate.z());
    
    glColor3f(1,1,1);
	glutSolidCube(1);
    
	glPopMatrix();
}

Vector4 Ship::getPosition() {
    return this->position;
}