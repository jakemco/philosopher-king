//
//  DeathStarTrench.cpp
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


#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>

#include "DeathStarTrench.h"
#include "Window.h"
#include "MoveableCamera.h"
#include "Texture.h"

#define DRAW_DIST 1000
#define SKYBOX_RADIUS 500

#define CLAMP(x,a,b) ((x) < (a) ? (a) : ((x) > (b) ? (b) : (x)))


DeathStarTrench::DeathStarTrench() {

	srand((unsigned int)time(NULL));

    this->camera = new MoveableCamera(Vector4(0, 0, 20, 1), Vector4(0, 0, 0, 1), Vector4(0, 1, 0));
    this->mCamera = (MoveableCamera*)this->camera;

	this->controls = new FlightControls(this);

	this->trenchSize = 10;
	this->trench = new RandomTrench(trenchSize);

	this->targetingShaderEnabled = false;
}

void DeathStarTrench::init() {
    glGenTextures(MAX_MAPS, &Texture::textures[0]);
    Texture::loadPPM("yavin.ppm", BG_TEXTURE);
    Texture::loadPPM("trench.ppm", TRENCH_TEXTURE);
    Texture::loadPPM("red_alert_black.ppm", ALERT_BLACK_TEXTURE);
    Texture::loadPPM("red_alert_transparent.ppm", ALERT_TRANS_TEXTURE);
    Texture::loadTexture(ALERT_BLACK_TEXTURE);
    Texture::loadTexture(ALERT_TRANS_TEXTURE);

	this->targetingShader = new Shader(
		"resources/shaders/targeting.vert",
		"resources/shaders/targeting.frag",
		true);
    
    music.openFromFile("music.wav");
    music.setLoop(true);
    music.play();
}

void DeathStarTrench::update(float dt) {
    ship.update(dt, controls->getX() * trenchSize, controls->getY() * trenchSize, controls->getX(), controls->isShooting());

    Vector4 position = mCamera->getPosition();
	position[0] = ship.getPosition().x() / 1.6;
    position[1] = ship.getPosition().y() / 1.2 + 1;
    position[2] = ship.getPosition().z() + 7;
    mCamera->setPosition(position);

	if (controls->getTargetingComputerOn() != this->targetingShaderEnabled) {
		this->targetingShaderEnabled = !this->targetingShaderEnabled;
		if (this->targetingShaderEnabled) {
			this->targetingShader->bind();
		}
		else {
			this->targetingShader->unbind();
		}
	}

	Vector4 shipPos = ship.getPosition();
	glUniform3f(glGetUniformLocationARB(this->targetingShader->getPid(), "ship"), shipPos[0], shipPos[1], shipPos[2]);
	glUniform3f(glGetUniformLocationARB(this->targetingShader->getPid(), "cameraPosition"), 0, 1, 7);

    this->trench->update(dt, position, DRAW_DIST);

    if (this->trench->collision(ship)) ship.crash();
    
    hud.update(dt,trenchSize,ship);
}

void DeathStarTrench::render() {

    Texture::loadTexture(TRENCH_TEXTURE);
    trench->render();
    glBindTexture(GL_TEXTURE_2D, NULL);
    Vector4 position = mCamera->getPosition();

	float skybox_dist = position.z() - DRAW_DIST + 20;

    Texture::loadTexture(BG_TEXTURE);
    glEnable(GL_TEXTURE_2D);

    float w, h;
    w = fmax(SKYBOX_RADIUS, Window::width / 2.0);
    h = fmax(SKYBOX_RADIUS, Window::height / 2.0);
    glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
	glNormal3f(0, 0, 1);

    glTexCoord2f(0, 1);  glVertex3f(-w , -h, skybox_dist);
    glTexCoord2f(1, 1);  glVertex3f(w, -h, skybox_dist);
    glTexCoord2f(1, 0);  glVertex3f(w, h, skybox_dist);
    glTexCoord2f(0, 0);  glVertex3f(-w, h, skybox_dist);
	glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, NULL);
    glEnable(GL_LIGHTING);
    
    /* RENDER HUD LAST */

	if (targetingShaderEnabled) {
		targetingShader->unbind();
	}
    
    ship.render();
    hud.render();

	if (targetingShaderEnabled) {
		targetingShader->bind();
	}
}

void DeathStarTrench::reset() {
	ship.reset();
	delete trench;
	this->trench = new RandomTrench(trenchSize);
}

InputManager* DeathStarTrench::getControls() {
	return this->controls;
}