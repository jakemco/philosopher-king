//
//  main.cpp
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/8/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//
#include <cstdlib>

#define SHOW_FPS

#include "Window.h"

#include "DeathStarTrench.h"
#include "FlightControls.h"
#include "Texture.h"

int main(int argc, char* argv[]) {
    
    Window::world = new DeathStarTrench();
	Window::input = ((DeathStarTrench*) (Window::world))->getControls();
    
    return Window::main(argc,argv);
}