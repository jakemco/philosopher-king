//
//  FPSControls.cpp
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/8/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//
#include <cstdlib>

#include "GLee.h"
#ifdef WIN32
  #include <GL/glut.h>
#else
  #include <GLUT/glut.h>
#endif

#include "FPSControls.h"

#include "Window.h"

void FPSControls::mouseCallback(int button, int state, int x, int y) { }

void FPSControls::activeMotionCallback(int x, int y) {
    this->passiveMotionCallback(x,y);
}

void FPSControls::passiveMotionCallback(int x, int y) {
    int mouseX = x - Window::width / 2;
	int mouseY = (Window::height - y) - Window::height / 2;
    
	if (mouseX == 0 && mouseY == 0) return;
    
	float fovY = 45.0;
	float fovX = 45.0;
    
	float propX = (float) mouseX / (float)(Window::width / 2);
	float propY = (float) mouseY / (float)(Window::height / 2);
    
	float degX = propX * fovX;
	float degY = propY * fovY;
    
	std::cout << mouseX << "," << mouseY << std::endl;
	std::cout << "Go Right " << degX << " degrees." << std::endl;
    
    this->movement.leftDeg -= degX;
    this->movement.upDeg += degY;
    
}

void FPSControls::keyboardCallback(unsigned char c, int x, int y) {
    switch (c) {
        case 'w':
            this->movement.forward += 0.5;
            break;
		case 'a':
			this->movement.right -= 0.5;
			break;
		case 's':
			this->movement.forward -= 0.5;
			break;
		case 'd':
			this->movement.right += 0.5;
			break;
		case 'q':
            Window::quit();
			break;
    }
}

FPSControls::FPSMovement FPSControls::popMovement() {
    
    FPSMovement out = this->movement;
    
    this->movement = {};
    
    return out;
}