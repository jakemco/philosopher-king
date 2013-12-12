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
#include "Texture.h"

#define DRAW_DIST 1000
#define TEX_SIZE 20
#define SURFACE_TEX_SIZE 5
#define SIDE_TEX_SIZE 2
#define BOTTOM_TEX_SIZE 1
#define SKYBOX_RADIUS 500

DeathStarTrench::DeathStarTrench(FlightControls* f) : trench(10) {

	srand(time(NULL));

    this->camera = new MoveableCamera(Vector4(0, 0, 20, 1), Vector4(0, 0, 0, 1), Vector4(0, 1, 0));
    this->mCamera = (MoveableCamera*)this->camera;

    this->controls = f;

    this->trenchHeight = 10;
    this->trenchWidth = 10;

    Texture::loadPPM("trench.ppm", TRENCH_TEXTURE);

}

void DeathStarTrench::update(float dt) {
    ship.update(dt, controls->getX() * trenchWidth, controls->getY() * trenchHeight);

    Vector4 position = mCamera->getPosition();
    position[0] = ship.getPosition().x();
    position[1] = ship.getPosition().y() + 1;
    position[2] = ship.getPosition().z() + 7;
    mCamera->setPosition(position);

    this->trench.update(position.z(), DRAW_DIST);

    if (this->trench.collision(ship)) ship.crash();
}

void DeathStarTrench::render() {

    ship.render();
    trench.render();
    Vector4 position = mCamera->getPosition();

	float skybox_dist = position.z() - DRAW_DIST + 20;
	
	glColor3f(0.2, 0.2, 0.5);
	glBegin(GL_QUADS);

	glNormal3f(0, 0, 1);

	glVertex3f(-SKYBOX_RADIUS, -SKYBOX_RADIUS, skybox_dist);
	glVertex3f(SKYBOX_RADIUS, -SKYBOX_RADIUS, skybox_dist);
	glVertex3f(SKYBOX_RADIUS, SKYBOX_RADIUS, skybox_dist);
	glVertex3f(-SKYBOX_RADIUS, SKYBOX_RADIUS, skybox_dist);
	glEnd();


	
}