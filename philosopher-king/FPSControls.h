//
//  FPSControls.h
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/8/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#pragma once

#include <iostream>

#include "InputManager.h"

class FPSControls : InputManager {
    
    struct FPSMovement {
        float leftDeg;
        float upDeg;
        
        float forward;
        float right;
    };
    
private:
    
    FPSMovement movement;
    
public:
    virtual void passiveMotionCallback(int x, int y);
	virtual void activeMotionCallback(int x, int y);
	virtual void mouseCallback(int button, int state, int x, int y);
	virtual void keyboardCallback(unsigned char key, int x, int y);
    
    FPSMovement popMovement();
};