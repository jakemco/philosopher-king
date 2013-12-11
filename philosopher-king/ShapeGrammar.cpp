#include "ShapeGrammar.h"
#include <cstring>

#ifdef WIN32
#include "GL/glut.h"
#else
#include "GLUT/glut.h"
#endif

char* ShapeGrammar::namesDroids[TYPES] = {
    "../resources/models/objects/awing_droid.obj",
    "../resources/models/objects/xwing_droid.obj",
    "../resources/models/objects/ywing_droid.obj"};
char* ShapeGrammar::namesEngines[TYPES] = {
    "../resources/models/objects/awing_engine.obj",
    "../resources/models/objects/xwing_engine.obj",
    "../resources/models/objects/ywing_engine.obj"};
char* ShapeGrammar::namesFront[TYPES] = {
    "../resources/models/objects/awing_front.obj",
    "../resources/models/objects/xwing_front.obj",
    "../resources/models/objects/ywing_front.obj" };
char* ShapeGrammar::namesWings[TYPES] = {
    "../resources/models/objects/awing_wing.obj",
    "../resources/models/objects/xwing_wing.obj",
    "../resources/models/objects/ywing_wing.obj" };

ObjReader ShapeGrammar::droids[TYPES];
ObjReader ShapeGrammar::engines[TYPES];
ObjReader ShapeGrammar::fronts[TYPES];
ObjReader ShapeGrammar::rightWings[TYPES];
ObjReader ShapeGrammar::leftWings[TYPES];

int ShapeGrammar::initialized = 0;

void ShapeGrammar::init()
{
    int i;
    for (i = 0; i < TYPES; ++i) {
        droids[i] = ObjReader(namesDroids[i]);
        engines[i] = ObjReader(namesEngines[i]);
        fronts[i] = ObjReader(namesFront[i]);
        rightWings[i] = ObjReader(namesWings[i]);
        leftWings[i] = ObjReader(namesWings[i]);
        leftWings[i].flipHorizontal();
    }

    initialized = 1;
}

void ShapeGrammar::designShip(int d, int e, int f, int w) {
    if (!initialized)
        ShapeGrammar::init();

    render(droids[d]);
    render(engines[e]);
    render(fronts[f]);
    render(rightWings[w]);
    render(leftWings[w]);
}

void ShapeGrammar::render(ObjReader obj) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(float)* 3, obj.getVertices());

    if (obj.getNormals() != nullptr)
    {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, sizeof(float)* 3, obj.getNormals());
    }

    if (obj.getTexcoords() != nullptr)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(3, GL_FLOAT, sizeof(float)* 3, obj.getTexcoords());
    }

    glDrawElements(GL_TRIANGLES, obj.getNIndices(), GL_UNSIGNED_INT, obj.getIndices());
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


void ShapeGrammar::makeAWing() {
    designShip(AWING, AWING, AWING, AWING);
}

void ShapeGrammar::makeXWing() {
    designShip(XWING, XWING, XWING, XWING);
}

void ShapeGrammar::makeYWing() {
    designShip(YWING, YWING, YWING, YWING);
}