//
//  FlightControls.h
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/8/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#pragma once

#include "InputManager.h"

class FlightControls : public InputManager {
private:
    float xProp, yProp;
    
public:

	FlightControls();
    
    virtual void passiveMotionCallback(int x, int y);
	virtual void activeMotionCallback(int x, int y);
	virtual void mouseCallback(int button, int state, int x, int y);
	virtual void keyboardCallback(unsigned char key, int x, int y);
    
    float getX();
    float getY();
    
    
};
