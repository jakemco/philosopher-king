//
//  Window.cpp
//  Final Project
//
//  Created by Jacob Maskiewicz on 11/6/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#include <cstdlib>

#include "GLee.h"

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
#include "InputManager.h"

// #define FULLSCREEN

//=========================================//

int Window::id;

int Window::width = 512;
int Window::height = 512;

InputManager* Window::input = NULL;
WorldManager* Window::world = NULL;

Shader* Window::targetingShader = NULL;

//-----------------------------------------//

void Window::reshapeCallback(int w, int h) {
    
    // store width and height
    Window::width = w;
    Window::height = h;
    
    // adjust viewport
	glViewport(0, 0, w, h);  // set new viewport size
    
    // adjust viewing frustrum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(45.0f, (float)w/(float)h, 5, 1000);
    
    // slide it all back
	//glTranslatef(0, 0, -20);
}

void Window::quit() {
    glutDestroyWindow(Window::id);
    exit(0);
}

//-----------------------------------------//

int Window::main(int argc, char * argv[])
{

    // initialize GLUT
    glutInit(&argc, argv);
    
    // open a context with double buffer, RGB colors, and depth buffering
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // make the window with size and title
	glutInitWindowSize(Window::width, Window::height);
	Window::id = glutCreateWindow("Final Project for CSE167");
    
	glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
	glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
	glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
	glShadeModel(GL_SMOOTH);             	      // set shading to smooth
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_NORMALIZE);
    
    float specular[]  = {1.0, 1.0, 1.0, 1.0};
    float shininess[] = {100.0};
    float position[]  = {0.0, 10.0, 1.0, 0.0};
    
    // Generate material properties:
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    // Generate light source:
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	Window::targetingShader = new Shader(
		"../resources/shaders/targeting.vert",
		"../resources/shaders/targeting.frag",
		true);
    
    glutReshapeFunc(Window::reshapeCallback);
    
	// Install callback functions:
	glutDisplayFunc([]() { Window::world->displayCallback(); });
    glutIdleFunc([]() { Window::world->idleCallback(); });
    
    // Input Management
    glutKeyboardFunc([](unsigned char c, int x, int y) { Window::input->keyboardCallback(c,x,y); });
    glutMouseFunc([](int b, int s, int x, int y) { Window::input->mouseCallback(b,s,x,y); });
	glutPassiveMotionFunc([](int x, int y) { Window::input->passiveMotionCallback(x,y); });
    glutMotionFunc([](int x, int y) { Window::input->activeMotionCallback(x,y); });
    
#ifdef FULLSCREEN
	glutFullScreen();
#endif
    
    Window::world->init();

	glutMainLoop();
	return 0;
}

