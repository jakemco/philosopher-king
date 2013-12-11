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
#include <ctime>

#include "DeathStarTrench.h"

#include "MoveableCamera.h"

#define DRAW_DIST 1000

DeathStarTrench::DeathStarTrench(FlightControls* f) {
    this->camera = new MoveableCamera(Vector4(0, 0, 20, 1), Vector4(0, 0, 0, 1), Vector4(0, 1, 0));
    this->mCamera = (MoveableCamera*)this->camera;
    
    this->controls = f;

	this->trenchHeight = 10;
	this->trenchWidth = 10;
}

void DeathStarTrench::update(float dt) {
    ship.update(dt, controls->getX() * trenchWidth,controls->getY() * trenchHeight);
    
    Vector4 position = mCamera->getPosition();
	position[0] = ship.getPosition().x();
	position[1] = ship.getPosition().y() + 1;
    position[2] = ship.getPosition().z() + 7;
    mCamera->setPosition(position);

	this->trench.update(position.z(), DRAW_DIST);
    
}

void DeathStarTrench::render() {

    ship.render();
	trench.render();
    Vector4 position = mCamera->getPosition();
    
    static const float x = trenchWidth/2.0;
    static const float y = trenchHeight/2.0;
    
    for (int i = 0; i < DRAW_DIST; i++) {
        int depth = position.z() - i;
        
        srand(depth);
		
		/* Draw Trench */
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