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

DeathStarTrench::DeathStarTrench(FlightControls* f) : trench(10) {
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

    static const float x = trenchWidth / 2.0;
    static const float y = trenchHeight / 2.0;

    glEnable(GL_TEXTURE_2D);
    Texture::loadTexture(TRENCH_TEXTURE);
    glColor3f(1, 1, 1);
    float nearPoint = position.z();
    std::cout << "Position: " << nearPoint << std::endl;

    float farPoint = nearPoint - DRAW_DIST;

    float nearTex = fmod(nearPoint, TEX_SIZE) / TEX_SIZE;
    float farTex = farPoint / TEX_SIZE;

    glBegin(GL_QUADS);  // Death Star surface -- left
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, nearTex); glVertex3f(-100, y, nearPoint);
    glTexCoord2f(0, farTex); glVertex3f(-100, y, farPoint);
    glTexCoord2f(SURFACE_TEX_SIZE, nearTex); glVertex3f(-x, y, nearPoint);
    glTexCoord2f(SURFACE_TEX_SIZE, farTex); glVertex3f(-x, y, farPoint);
    glEnd();

    glBegin(GL_QUADS); // trench surface -- left
    glNormal3f(1, 0, 0);
    glTexCoord2f(0, nearTex); glVertex3f(-x, y, nearPoint);
    glTexCoord2f(0, farTex); glVertex3f(-x, y, farPoint);
    glTexCoord2f(SIDE_TEX_SIZE, nearTex); glVertex3f(-x, -y, nearPoint);
    glTexCoord2f(SIDE_TEX_SIZE, farTex); glVertex3f(-x, -y, farPoint);
    glEnd();

    glBegin(GL_QUADS); // trench surface -- bottom
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, nearTex); glVertex3f(-x, -y, nearPoint);
    glTexCoord2f(0, farTex); glVertex3f(-x, -y, farPoint);
    glTexCoord2f(BOTTOM_TEX_SIZE, nearTex); glVertex3f(x, -y, nearPoint);
    glTexCoord2f(BOTTOM_TEX_SIZE, farTex); glVertex3f(x, -y, farPoint);
    glEnd();

    glBegin(GL_QUADS); // trench surfacee -- right
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, nearTex); glVertex3f(x, -y, nearPoint);
    glTexCoord2f(0, farTex); glVertex3f(x, -y, farPoint);
    glTexCoord2f(SIDE_TEX_SIZE, nearTex); glVertex3f(x, y, nearPoint);
    glTexCoord2f(SIDE_TEX_SIZE, farTex); glVertex3f(x, y, farPoint);
    glEnd();

    glBegin(GL_QUADS); // Death Star surface -- right
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, nearTex); glVertex3f(x, y, nearPoint);
    glTexCoord2f(0, farTex); glVertex3f(x, y, farPoint);
    glTexCoord2f(SURFACE_TEX_SIZE, nearTex); glVertex3f(100, y, nearPoint);
    glTexCoord2f(SURFACE_TEX_SIZE, farTex); glVertex3f(100, y, farPoint);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);
}