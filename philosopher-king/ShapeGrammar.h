#pragma once

#include "ObjReader.h"
#include "Vector4.h"

class ShapeGrammar
{
public:
    static void init();
    
    static void maxPartRange();
    static void designShip();

    static void nextDroidPart();
    static void nextEnginePart();
    static void nextFrontPart();
    static void nextWingPart();

    static void prevDroidPart();
    static void prevEnginePart();
    static void prevFrontPart();
    static void prevWingPart();

    static void makeAWing();
    static void makeXWing();
    static void makeYWing();

    static Vector4 minVerts;
    static Vector4 maxVerts;
    static float scaleSize;

    static const int AWING = 0;
    static const int XWING = 1;
    static const int YWING = 2;
    
private:

    static const int DROID_TYPES = 3;
    static const int ENGINE_TYPES = 3;
    static const int FRONT_TYPES = 3;
    static const int WING_TYPES = 3;
    static const int MAX_CHAR = 80;

    static char* namesDroids[DROID_TYPES];
    static char* namesEngines[ENGINE_TYPES];
    static char* namesFront[FRONT_TYPES];
    static char* namesWings[WING_TYPES];

    static ObjReader droids[DROID_TYPES];
    static ObjReader engines[ENGINE_TYPES];
    static ObjReader fronts[FRONT_TYPES];
    static ObjReader wings[WING_TYPES];
public:
    
    static int droidPart;
    static int enginePart;
    static int frontPart;
    static int wingPart;
    
private:
    
    static void designShip(int d, int e, int f, int w);
    static void render(ObjReader obj);
    static void renderLeftWing(ObjReader obj);

    static int initialized;
};