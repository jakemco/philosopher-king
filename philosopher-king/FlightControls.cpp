//
//  FlightControls.cpp
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

#include "FlightControls.h"

#include "Window.h"

#define CLAMP(x,a,b) ((x) < (a) ? (a) : ((x) > (b) ? (b) : (x)))

void FlightControls::passiveMotionCallback(int x, int y) {
    
	float mouseX = (float) x / (float) Window::width;
	float mouseY = (float) (Window::height - y) / (float) Window::height;

	this->xProp = (mouseX - 0.5f) * 2.0f;
	this->yProp = (mouseY - 0.5f) * 2.0f;
	
}

void FlightControls::activeMotionCallback(int x, int y) { this->passiveMotionCallback(x, y); }

void FlightControls::mouseCallback(int button, int state, int x, int y) {}
void FlightControls::keyboardCallback(unsigned char key, int x, int y) {}

float FlightControls::getX() { return xProp; }
float FlightControls::getY() { return yProp; }