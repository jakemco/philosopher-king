//
//  WorldManager.h
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/8/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#pragma once

#include "Camera.h"

class WorldManager {
    
protected:
    Camera* camera;
    
    virtual void update(float) = 0;
    virtual void render() = 0;
    
public:
    virtual void idleCallback();
    virtual void displayCallback();
    
    virtual void init() = 0;
	virtual void reset() = 0;
    
};
