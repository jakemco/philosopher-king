//
//  FlightControls.cpp
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

#include "FlightControls.h"
#include "ShapeGrammar.h"
#include "Window.h"

#define CLAMP(x,a,b) ((x) < (a) ? (a) : ((x) > (b) ? (b) : (x)))

FlightControls::FlightControls(WorldManager* gc) : InputManager() {
	this->xProp = 0;
	this->yProp = 0;
	this->useGlass = false;
	this->glassOverride = new GlassControls();
	this->glassOverride->connectToGlass();
	this->targetingComputerOn = false;

	this->gameController = gc;
    this->shooting = false;
}

void FlightControls::passiveMotionCallback(int x, int y) {
    
	float mouseX = (float) x / (float) Window::width;
	float mouseY = (float) (Window::height - y) / (float) Window::height;

	this->xProp = (mouseX - 0.5f) * 2.0f;
	this->yProp = (mouseY - 0.5f) * 2.0f;
	
}

void FlightControls::activeMotionCallback(int x, int y) { this->passiveMotionCallback(x, y); }

void FlightControls::mouseCallback(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		shooting = true;
	else
		shooting = false;
}

bool FlightControls::isShooting() { return shooting; }

void FlightControls::keyboardCallback(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
    case 'A':
        ShapeGrammar::makeAWing(); break;
    case 'x':
    case 'X':
        ShapeGrammar::makeXWing(); break;
    case 'y':
    case 'Y': 
        ShapeGrammar::makeYWing(); break;

    case '1': ShapeGrammar::nextDroidPart(); break;
    case '2': ShapeGrammar::nextEnginePart(); break;
    case '3': ShapeGrammar::nextFrontPart(); break;
    case '4': ShapeGrammar::nextWingPart(); break;

	case 'g': useGlass = !useGlass; break;
	case 'c': this->glassOverride->calibratePitch(); break;

	case 'r': gameController->reset(); break;
	case 'q': Window::quit(); break;
	case 'f': glutFullScreen(); break;
	case 't':
		this->targetingComputerOn = !this->targetingComputerOn;
		if (targetingComputerOn) {
			Window::targetingShader->bind();
		}
		else {
			Window::targetingShader->unbind();
		}
		break;
    }
}

float FlightControls::getX() { 
	if (useGlass) {
		return this->glassOverride->getInterpolatedX();
	}

	return xProp; 
}

float FlightControls::getY() { 
	if (useGlass) {
		return this->glassOverride->getInterpolatedY();
	}

	return yProp; 
}
