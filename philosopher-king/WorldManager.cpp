//
//  WorldManager.cpp
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/8/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#include <cstdlib>

#ifdef WIN32
  #include "GLee.h"
  #include <GL/glut.h>
#else
  #include <GLUT/glut.h>
#endif

#include <chrono>
#include <thread>
#include <iostream>

#include "WorldManager.h"

#define FPS(X) (1000/X)

void WorldManager::idleCallback() {
	typedef std::chrono::milliseconds milliseconds;
    
    auto startTime = std::chrono::steady_clock::now();
    
	this->displayCallback();
    
	std::this_thread::sleep_until(startTime + milliseconds(FPS(60)));
    
    auto timeElapsed = std::chrono::steady_clock::now() - startTime;
    float dt = std::chrono::duration_cast<milliseconds>(timeElapsed).count();
    
    this->update(dt/1000.0f);
    
#ifdef SHOW_FPS
    std::cout << "fps: "<< 1000.0f / dt << std::endl;
#endif
}

void WorldManager::displayCallback() {
    // clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Load Modelview matrix
	glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(this->camera->getMatrix().getPointer());

    this->render();
    
	glFlush();
	glutSwapBuffers();
}