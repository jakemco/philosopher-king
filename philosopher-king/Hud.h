//
//  Hud.h
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/12/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#pragma once

#include "Ship.h"

class Hud {
private:
    float burst;
    bool over;
    bool cooldown;
    
    int dist;
    
public:
    void update(float, float, const Ship&);
    void render();
};
