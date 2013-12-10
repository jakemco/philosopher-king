#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

class Texture {
public:
    static unsigned char* loadPPM(const char* filename, int& width, int& height);
    static void loadPPM(const char* filename, int index);
    static void loadTexture(int index);

private:
    static const int MAX_MAPS = 10;
    static unsigned char* data[MAX_MAPS];
    static int width[MAX_MAPS];
    static int height[MAX_MAPS];
};