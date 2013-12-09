//
//  DeathStarTrench.cpp
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

#include <iostream>
#include <algorithm>
#include <cmath>

#include "DeathStarTrench.h"

#include "MoveableCamera.h"

DeathStarTrench::DeathStarTrench(FlightControls* f) {
    this->camera = new MoveableCamera(Vector4(0, 0, 20, 1), Vector4(0, 0, 0, 1), Vector4(0, 1, 0));
    this->mCamera = (MoveableCamera*)this->camera;
    
    this->controls = f;

	this->trenchHeight = 10;
	this->trenchWidth = 10;
}

void DeathStarTrench::update(float dt) {
    ship.update(dt, controls->getX() * trenchWidth/2.0,controls->getY() * trenchHeight/2.0);
    
    Vector4 position = mCamera->getPosition();
    position[2] = ship.getPosition().z() + 15;
    mCamera->setPosition(position);
    
    
}

void DeathStarTrench::render() {
	/*
	glPushMatrix();
	glTranslatef(controls->getX() * 5, controls->getY() * 5, 0);
	glutSolidCube(5);
	glPopMatrix();
	*/
    ship.render();
    Vector4 position = mCamera->getPosition();
    
    static const float x = trenchWidth/2.0;
    static const float y = trenchHeight/2.0;
    
    for (int i = 0; i < 1000; i++) {
        int depth = position.z() - i;
        
        srand(depth);
        glColor3f((float)rand() /(float)RAND_MAX, (float)rand() /(float)RAND_MAX, (float)rand() /(float)RAND_MAX);
        glBegin(GL_QUAD_STRIP);
        
        glVertex3f(-x, y, depth);
        glVertex3f(-x, y, depth-1);
        
        glVertex3f(-x, -y, depth);
        glVertex3f(-x, -y, depth-1);
        
        glVertex3f(x, -y, depth);
        glVertex3f(x, -y, depth-1);
        
        glVertex3f(x, y, depth);
        glVertex3f(x, y, depth-1);
        
        glEnd();
        
    }
}