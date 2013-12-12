//
//  DeathStarTrench.h
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/8/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#pragma once

#include "WorldManager.h"

#include "FlightControls.h"
#include "Ship.h"
#include "MoveableCamera.h"
#include "RandomTrench.h"

class DeathStarTrench : public WorldManager {
    
private:
    MoveableCamera* mCamera;
    FlightControls* controls;
    Ship ship;
	RandomTrench* trench;
    
    float trenchSize;

public:
    
    DeathStarTrench();
    
    virtual void update(float);
    virtual void render();
	virtual void reset();

	InputManager* getControls();
};