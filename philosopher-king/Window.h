//
//  Window.h
//  Final Project
//
//  Created by Jacob Maskiewicz on 11/6/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#pragma once

#include "MoveableCamera.h"
#include "Matrix4.h"

#define TRACKBALL_SIZE 1.3f

class Window {
public:
	static int id;

    static int width, height;
    
    static int mouseX, mouseY;
    static bool dragging;
    static bool zooming;
    
    static float left,right,top,bottom,near,far;
    
    static MoveableCamera camera;
        
    static void setupWorld();
    
    static void idleCallback();
	static void reshapeCallback(int w, int h);
	static void displayCallback();
    
    static void keyboardCallback(unsigned char c, int x, int y);
    
	static void passiveCallback(int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    static void motionCallback(int x, int y);
};
