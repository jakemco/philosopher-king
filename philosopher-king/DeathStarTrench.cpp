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
#define TEX_SIZE 10

DeathStarTrench::DeathStarTrench(FlightControls* f) : trench(10) {
    this->camera = new MoveableCamera(Vector4(0, 0, 20, 1), Vector4(0, 0, 0, 1), Vector4(0, 1, 0));
    this->mCamera = (MoveableCamera*)this->camera;

    this->controls = f;

    this->trenchHeight = 10;
    this->trenchWidth = 10;

    
    glEnable(GL_TEXTURE_2D);
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
    static int last_depth = position.z();

    glEnable(GL_TEXTURE_2D);
    Texture::loadTexture(TRENCH_TEXTURE);
    //glBindTexture(GL_TEXTURE_2D, Texture::textures[TRENCH_TEXTURE]);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    for (int i = 0; i < DRAW_DIST; i++) {
        int depth = position.z() - i;
        if (depth >= last_depth) continue;

        /* Draw Trench */
        glColor3f(1, 1, 1);
        glBegin(GL_QUAD_STRIP);

        float fore = (depth % TEX_SIZE * 1.0) / TEX_SIZE;
        float back = (depth % TEX_SIZE + 1.0) / TEX_SIZE;

        glNormal3f(0, 1, 0);
        for (float j = -100; j < -x; j += TEX_SIZE) {
            float j2 = fmin(j + TEX_SIZE, -x);
            glTexCoord2f(0, fore);
            glVertex3f(j, y, depth);
            glTexCoord2f(0, back);
            glVertex3f(j, y, depth - 1);
            glTexCoord2f(1, fore);
            glVertex3f(j2, y, depth);
            glTexCoord2f(1, back);
            glVertex3f(j2, y, depth - 1);
        }

        glNormal3f(1, 0, 0);
        glTexCoord2f(0, fore);
        glVertex3f(-x, y, depth);
        glTexCoord2f(0, back);
        glVertex3f(-x, y, depth - 1);
        glTexCoord2f(1, fore);
        glVertex3f(-x, -y, depth);
        glTexCoord2f(1, back);
        glVertex3f(-x, -y, depth - 1);

        glNormal3f(0, 1, 0);
        glTexCoord2f(0, fore);
        glVertex3f(-x, -y, depth);
        glTexCoord2f(0, back);
        glVertex3f(-x, -y, depth - 1);
        glTexCoord2f(1, 0);
        glVertex3f(x, -y, depth);
        glTexCoord2f(1, back);
        glVertex3f(x, -y, depth - 1);

        glNormal3f(-1, 0, 0);
        glTexCoord2f(0, fore);
        glVertex3f(x, -y, depth);
        glTexCoord2f(0, back);
        glVertex3f(x, -y, depth - 1);
        glTexCoord2f(1, fore);
        glVertex3f(x, y, depth);
        glTexCoord2f(1, back);
        glVertex3f(x, y, depth - 1);

        glNormal3f(0, 1, 0);
        for (float j = x; j < 100; j += TEX_SIZE) {
            float j2 = fmin(j + TEX_SIZE, 100);
            glTexCoord2f(0, fore);
            glVertex3f(j, y, depth);
            glTexCoord2f(0, back);
            glVertex3f(j, y, depth - 1);
            glTexCoord2f(1, fore);
            glVertex3f(j2, y, depth);
            glTexCoord2f(1, back);
            glVertex3f(j2, y, depth - 1);
        }

        glEnd();
        ++last_depth;
    }
    glDisable(GL_TEXTURE_2D);
}