#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define BG_TEXTURE 0
#define TRENCH_TEXTURE 1
#define MAX_MAPS 2 // last texture id + 1

class Texture {
public:
    static unsigned char* loadPPM(const char* filename, int& width, int& height);
    static void loadPPM(const char* filename, int index);
    static void loadTexture(int index);

private:
    static unsigned char* data[MAX_MAPS];
    static int width[MAX_MAPS];
    static int height[MAX_MAPS];
};