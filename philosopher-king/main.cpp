//
//  main.cpp
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/8/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//
#include <cstdlib>

#include "Window.h"

#include "DeathStarTrench.h"
#include "FlightControls.h"

int main(int argc, char* argv[]) {
    Window::input = new FlightControls();
    Window::world = new DeathStarTrench((FlightControls*)Window::input);
    
    return Window::main(argc,argv);
}