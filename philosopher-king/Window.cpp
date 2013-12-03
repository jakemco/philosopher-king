//
//  Window.cpp
//  Final Project
//
//  Created by Jacob Maskiewicz on 11/6/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#include <cstdlib>

#ifdef WIN32
  #include <GL/glut.h>
#else
  #include <GLUT/glut.h>
#endif

#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "Window.h"

#include "Vector4.h"
#include "Matrix4.h"

#define FPS_60 1000/60

//=========================================//

int Window::width = 512;
int Window::height = 512;

int Window::mouseX = 0;
int Window::mouseY = 0;

bool Window::dragging = false;
bool Window::zooming = false;

float Window::left = -10;
float Window::right = 10;
float Window::top = 10;
float Window::bottom = -10;
float Window::near = 10;
float Window::far = 1000;
MoveableCamera Window::camera(Vector4(0,0,10,1),Vector4(0,0,0,1),Vector4(0,1,0,0));

//-----------------------------------------//

void Window::setupWorld() {
    //TODO
}

//-----------------------------------------//

void Window::idleCallback() {
    
    typedef std::chrono::milliseconds milliseconds;
    
    auto startTime = std::chrono::system_clock::now();
    
	displayCallback();
    
	std::this_thread::sleep_until(startTime + milliseconds(FPS_60));
    
    /*
    auto mspf = std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now() - startTime);
    auto fps = 1.0f / ((float)(mspf.count()) / 1000.0f);
    std::cout << "fps: "<< fps << std::endl;
     */
}

void Window::reshapeCallback(int w, int h) {
    
    // store width and height
    Window::width = w;
    Window::height = h;
    
    // adjust viewport
	glViewport(0, 0, w, h);  // set new viewport size
    
    // adjust viewing frustrum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(left, right, bottom, top, near, far);
    
    // slide it all back
	//glTranslatef(0, 0, -20);
}

void Window::displayCallback() {

    // clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Load Modelview matrix
	glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(camera.getMatrix().getPointer());
    
    //TODO - Draw things
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(5.0, 15.0, 15.0);

	glFlush();
	glutSwapBuffers();
}

//-----------------------------------------//

void Window::keyboardCallback(unsigned char c, int x, int y) {
    switch (c) {
        case 'w':
			camera.moveForward(0.5);
            break;
		case 'a':
			camera.moveRight(-0.5);
			break;
		case 's':
			camera.moveForward(-0.5);
			break;
		case 'd':
			camera.moveRight(0.5);
			break;
    }
}

void Window::passiveCallback(int x, int y) {
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

	camera.lookLeft(-degX);
	camera.lookUp(degY);

	/* Move mouse back to center */
	glutWarpPointer(Window::width / 2, Window::height / 2);
}

void Window::mouseCallback(int button, int state, int x, int y) {
	
	Window::mouseX = x;
	Window::mouseY = y;
    
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Window::dragging = true;
	} else if (button == GLUT_RIGHT_BUTTON) {
		Window::zooming = true;
	} else if (state == GLUT_UP) {
		Window::dragging = false;
		Window::zooming = false;
	}
}

void Window::motionCallback(int x, int y) {
	/*
	if (Window::dragging) {
		Vector4 v2;
		Vector4 v1;
        
		double halfWidth = (double) width / 2.0f;
		double halfHeight = (double) height / 2.0f;
        
		double smallSide = std::min(halfWidth, halfHeight);
        
		v1[0] = ((double) mouseX - halfWidth) / smallSide;
		v1[1] = ((double)(height - mouseY) - halfHeight) / smallSide;
		v1[2] = exp(-TRACKBALL_SIZE * v1.lengthSquared());
        
		v2[0] = ((double) x - halfWidth) / smallSide;
		v2[1] = ((double)(height - y) - halfHeight) / smallSide;
		v2[2] = exp(-TRACKBALL_SIZE * v2.lengthSquared());
        
		double angle = v1.angle(v2);
        
		Vector4 a = Vector4::cross(v2, v1);
		a.normalize();
        
        if(angle == 0 || isnan(angle)) return;
        
        //rotate camera around a by angle
        camera.d = Matrix4::rotate(a, -angle) * camera.d;
        camera.e = Matrix4::rotate(a,-angle) * camera.e;
        
        camera.update(camera.e,camera.d,camera.up);
        
	} else if (Window::zooming) {
		int distance = -(y - mouseY);
        
		camera.e = Matrix4::translate((camera.d - camera.e)*((float)distance/100.0f)) * camera.e;
		camera.update(camera.e, camera.d, camera.up);
	}
    
	mouseX = x;
	mouseY = y;
	*/
}

//-----------------------------------------//

int main(int argc, char * argv[])
{

    // initialize GLUT
    glutInit(&argc, argv);
    
    // open a context with double buffer, RGB colors, and depth buffering
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // make the window with size and title
	glutInitWindowSize(Window::width, Window::height);
	glutCreateWindow("Final Project for CSE167");
    
	glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
	glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
	glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
	glShadeModel(GL_SMOOTH);             	      // set shading to smooth
	glMatrixMode(GL_PROJECTION);
    
	// Generate light source:
	glEnable(GL_LIGHTING);
    
    Window::setupWorld();
    
	// Install callback functions:
	glutDisplayFunc(Window::displayCallback);
	glutReshapeFunc(Window::reshapeCallback);
	glutIdleFunc(Window::idleCallback);
    
    glutKeyboardFunc(Window::keyboardCallback);
    
    //glutMouseFunc(Window::mouseCallback);
	glutPassiveMotionFunc(Window::passiveCallback);
    glutMotionFunc(Window::passiveCallback);
    
	glutMainLoop();
	return 0;
}

