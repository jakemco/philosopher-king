#pragma once

#include "ObjReader.h"

class ShapeGrammar
{
public:
    static void init();
    
    static void render(ObjReader obj);
    static void designShip(int d, int e, int f, int w);

    static void makeAWing();
    static void makeXWing();
    static void makeYWing();

private:
    static const int AWING = 0;
    static const int XWING = 1;
    static const int YWING = 2;
    static const int TYPES = 3;
    static const int MAX_CHAR = 80;

    static char* path;
    static char* namesDroids[TYPES];
    static char* namesEngines[TYPES];
    static char* namesFront[TYPES];
    static char* namesWings[TYPES];

    static ObjReader droids[TYPES];
    static ObjReader engines[TYPES];
    static ObjReader fronts[TYPES];
    static ObjReader leftWings[TYPES];
    static ObjReader rightWings[TYPES];

    static int initialized;
};