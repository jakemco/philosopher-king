//
//  Ship.cpp
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/8/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#include <cstdlib>

#ifdef WIN32
  #include "GLee.h"
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
sf::SoundBuffer Ship::buffer;


Ship::Ship() {
    if(buffer.getDuration().asSeconds() == 0)
        buffer.loadFromFile("blaster.wav");
    
    blaster = new sf::Sound(buffer);

    flying.openFromFile("xwing.wav");
    flying.setLoop(true);
    
	this->reset();
}

Ship::~Ship() {
    if(blaster) delete blaster;
}

void Ship::update(float dt, float x, float y, float controlsX, bool shooting) {
	if (!crashed) {
        if (flying.getStatus() != sf::Music::Status::Playing) {
            flying.play();
        }
		charge += dt;

		Vector4 destination(position.x() + x, position.y() + y, position.z() - SPEED, 1.0f);
		Vector4 dir = Vector4::normalize(destination - position)*SPEED*dt;

		this->rotate = Vector4::cross(Vector4(0, 0, -1), dir);
		this->angle = Vector4::angle(Vector4(0, 0, -1), dir);
		
		this->zrotAngle = -controlsX;

		this->position += dir;

		if (shooting && charge > 0.15) {
			charge = 0;

			Vector4 lStart = position + Vector4(-0.5, 0, 0);
			Vector4 rStart = position + Vector4(0.5, 0, 0);

			Vector4 target = position + Vector4::normalize(destination - position) * 200;

			Vector4 color(0.8, 0.4, 0.2);

			this->lasers.insert(new Laser(lStart,target,color));
			this->lasers.insert(new Laser(rStart, target, color));
            
            blaster->play();
		}

		std::set<Laser*> trash;

		for (Laser* l : lasers) {
			if (l->dead(200)) trash.insert(l);
			else l->update(dt);
		}

		for (Laser*l : trash) {
			lasers.erase(l);
			delete l;
		}
	} else flying.stop();
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

	for (Laser* l : lasers) l->render();
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
	this->charge = 0;
}