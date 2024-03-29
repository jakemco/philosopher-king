//
//  Hud.cpp
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/12/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#include <cstdlib>

#ifdef WIN32
#include "GLee.h"
#include "GL/glut.h"
#else
#include "GLUT/glut.h"
#endif

#include <algorithm>
#include <iostream>

#include "Hud.h"
#include "Texture.h"
#include "Window.h"

void Hud::update(float dt, float size, const Ship& ship) {
    burst = ship.getBurst();
    over = ship.getPosition().y() > size/2;
    cooldown = ship.onCooldown();
    
    dist = abs(ship.getPosition().z());
}

void Hud::render() {
    
    //switch to 2d mode
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, Window::width, Window::height, 0.0, -1.0, 10.0);
    
    //Fresh Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_CULL_FACE);
    
    glClear(GL_DEPTH_BUFFER_BIT);
    
    glDisable(GL_LIGHTING);
    /* DRAW BELOW HERE */
    
    if(over) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, Texture::textures[ALERT_BLACK_TEXTURE]);
        glBegin(GL_QUADS);
        
        //glColor3f(1.0f, 0.0f, 0.0);
        glColor4f(1.0, 0.0, 0.0, 0.0);

        glTexCoord2d(0, 0); glVertex2f(10.0, 10.0);
        glTexCoord2d(1, 0); glVertex2f(10 + Window::width/6,10.0);
        glTexCoord2d(1, 1); glVertex2f(10 + Window::width/6,10 + Window::width/6);
        glTexCoord2d(0, 1); glVertex2f(10.0,10 + Window::width/6);
        
        glTexCoord2d(0, 0); glVertex2f(Window::width - 10 - Window::width/6, 10);
        glTexCoord2d(1, 0); glVertex2f(Window::width - 10,10.0);
        glTexCoord2d(1, 1); glVertex2f(Window::width - 10,10 + Window::width/6);
        glTexCoord2d(0, 1); glVertex2f(Window::width - 10 - Window::width/6,10 + Window::width/6);
        
        glEnd();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, NULL);
    }
    
    
    
    glBegin(GL_QUADS);
    
    if(cooldown) glColor3f(1.0,0.1,0.1);
    else glColor3f(0.8,0.8,0.8);
    
    glVertex2f(10, Window::height - 10);
    glVertex2f( 10 + (Window::width/2) * (burst < 0 ? 0 : burst) / Ship::RECHARGE , Window::height -10);
    glVertex2f( 10 + (Window::width/2) * (burst < 0 ? 0 : burst) / Ship::RECHARGE , Window::height -50);
    glVertex2f(10, Window::height - 50);

    
    glEnd();
    
    char buf[BUFSIZ];
    snprintf(buf, BUFSIZ, "Score: %4.4d",dist);
    
    glColor3f(1,1,1);
    glRasterPos2f(Window::width-120, Window::height - 20);
    
    char* p = buf;
    while(*p != 0)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
        

    
    /* DRAW ABOVE HERE */
    glEnable(GL_LIGHTING);
    
    // Making sure we can render 3d again
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}