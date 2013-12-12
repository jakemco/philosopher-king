#pragma once

#include <stdlib.h>
#include <stdio.h>

#ifdef WIN32
  #include "GLee.h"
  #include <GL/glut.h>
#else
  #include <GLUT/glut.h>
#endif

#include <math.h>
#include <iostream>

#define BG_TEXTURE 0
#define TRENCH_TEXTURE 1
#define ALERT_BLACK_TEXTURE 2
#define ALERT_TRANS_TEXTURE 3
#define MAX_MAPS 4 // last texture id + 1

class Texture {
public:
    static unsigned char* loadPPM(const char* filename, int& width, int& height);
    static void loadPPM(const char* filename, int index);
    static void loadTexture(int index);
    static GLuint textures[MAX_MAPS];

private:
    static unsigned char* data[MAX_MAPS];
    static int width[MAX_MAPS];
    static int height[MAX_MAPS];
    
};