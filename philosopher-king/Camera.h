//
//  Camera.h
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/8/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#pragma once

#include "Matrix4.h"

class Camera {
public:
    virtual Matrix4& getMatrix() = 0;
};
