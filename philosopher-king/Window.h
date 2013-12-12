//
//  Window.h
//  Final Project
//
//  Created by Jacob Maskiewicz on 11/6/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#pragma once

#include "InputManager.h"
#include "WorldManager.h"
#include "shader.h"

class Window {
public:
	static int id;

    static int width, height;
    
    static InputManager* input;
    static WorldManager* world;
    
    static int main(int argc, char* argv[]);
	static void reshapeCallback(int w, int h);
	static void quit();
};
