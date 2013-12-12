#include <iostream>
#include "ShapeGrammar.h"


#ifdef WIN32
#include "GL/glut.h"
#else
#include "GLUT/glut.h"
#endif

char* ShapeGrammar::namesDroids[DROID_TYPES] = {
    "resources/models/objects/awing_droid.obj",
    "resources/models/objects/xwing_droid.obj",
    "resources/models/objects/ywing_droid.obj"};
char* ShapeGrammar::namesEngines[ENGINE_TYPES] = {
    "resources/models/objects/awing_engine.obj",
    "resources/models/objects/xwing_engine.obj",
    "resources/models/objects/ywing_engine.obj"};
char* ShapeGrammar::namesFront[FRONT_TYPES] = {
    "resources/models/objects/awing_front.obj",
    "resources/models/objects/xwing_front.obj",
    "resources/models/objects/ywing_front.obj" };
char* ShapeGrammar::namesWings[WING_TYPES] = {
    "resources/models/objects/awing_wing.obj",
    "resources/models/objects/xwing_wing.obj",
    "resources/models/objects/ywing_wing.obj" };

ObjReader ShapeGrammar::droids[DROID_TYPES];
ObjReader ShapeGrammar::engines[ENGINE_TYPES];
ObjReader ShapeGrammar::fronts[FRONT_TYPES];
ObjReader ShapeGrammar::wings[WING_TYPES];

int ShapeGrammar::droidPart = 0;
int ShapeGrammar::enginePart = 0;
int ShapeGrammar::frontPart = 0;
int ShapeGrammar::wingPart = 0;

int ShapeGrammar::initialized = 0;

Vector4 ShapeGrammar::minVerts;
Vector4 ShapeGrammar::maxVerts;
float ShapeGrammar::scaleSize;

void ShapeGrammar::init()
{
    int i;
    for (i = 0; i < DROID_TYPES; ++i) {
        droids[i] = ObjReader(namesDroids[i]);
    }

    for (i = 0; i < ENGINE_TYPES; ++i) {
        engines[i] = ObjReader(namesEngines[i]);
    }

    for (i = 0; i < FRONT_TYPES; ++i) {
        fronts[i] = ObjReader(namesFront[i]);
    }

    for (i = 0; i < WING_TYPES; ++i) {
        wings[i] = ObjReader(namesWings[i]);
    }

    initialized = 1;
}

void ShapeGrammar::maxPartRange() {
    ObjReader parts[] = { droids[droidPart], engines[enginePart], fronts[frontPart], wings[wingPart] };
    
    for (int i = 0; i < 4; ++i) { // find min, max Y
        minVerts.set(1, fmin(parts[i].getMinVerts().get(1), minVerts.get(1)));
        maxVerts.set(1, fmax(parts[i].getMaxVerts().get(1), maxVerts.get(1)));
    }

    minVerts.set(0, -parts[3].getMaxVerts().get(0)); // min X is max wing part X b/c of flip
    maxVerts.set(0, parts[3].getMaxVerts().get(0));  // max X is max wing part X

    minVerts.set(2, parts[2].getMinVerts().get(2)); // min Z is min front part Z
    maxVerts.set(2, parts[3].getMaxVerts().get(2)); // maz Z is max engine part Z


    float rangeX = engines[enginePart].getMaxVerts().get(0) - engines[enginePart].getMinVerts().get(0);
    float rangeY = engines[enginePart].getMaxVerts().get(1) - engines[enginePart].getMinVerts().get(1);
    float rangeZ = engines[enginePart].getMaxVerts().get(2) - engines[enginePart].getMinVerts().get(2);

    scaleSize = fmax(rangeX, (float)fmax(rangeY, rangeZ));
}

void ShapeGrammar::designShip() {
    if (!initialized)
        ShapeGrammar::init();

    render(droids[droidPart]);
    render(engines[enginePart]);
    render(fronts[frontPart]);
    render(wings[wingPart]);
    renderLeftWing(wings[wingPart]);
}

void ShapeGrammar::makeAWing() {
    droidPart = AWING;
    enginePart = AWING;
    frontPart = AWING;
    wingPart = AWING;
}

void ShapeGrammar::makeXWing() {
    droidPart = XWING;
    enginePart = XWING;
    frontPart = XWING;
    wingPart = XWING;
}

void ShapeGrammar::makeYWing() {
    droidPart = YWING;
    enginePart = YWING;
    frontPart = YWING;
    wingPart = YWING;
}

void ShapeGrammar::nextDroidPart() { droidPart = ++droidPart % DROID_TYPES; }
void ShapeGrammar::nextEnginePart() { enginePart = ++enginePart % ENGINE_TYPES; }
void ShapeGrammar::nextFrontPart() { frontPart = ++frontPart % FRONT_TYPES; }
void ShapeGrammar::nextWingPart() { wingPart = ++wingPart % WING_TYPES; }

void ShapeGrammar::prevDroidPart() { droidPart = (DROID_TYPES + --droidPart) % DROID_TYPES; }
void ShapeGrammar::prevEnginePart() { enginePart = (ENGINE_TYPES + --enginePart) % ENGINE_TYPES; }
void ShapeGrammar::prevFrontPart() { frontPart = (FRONT_TYPES + --frontPart) % FRONT_TYPES; }
void ShapeGrammar::prevWingPart() { wingPart = (WING_TYPES + --wingPart) % WING_TYPES; }

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

void ShapeGrammar::renderLeftWing(ObjReader obj) {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < obj.getNIndices(); ++i) {
        float x = -obj.getVertices()[3*obj.getIndices()[i]];
        float y = obj.getVertices()[3*obj.getIndices()[i]+1];
        float z = obj.getVertices()[3*obj.getIndices()[i]+2];
        glVertex3f(x, y, z);

		if (obj.getNormals() != nullptr) {
			float normalX = obj.getNormals()[3 * obj.getIndices()[i]];
			float normalY = obj.getNormals()[3 * obj.getIndices()[i] + 1];
			float normalZ = obj.getNormals()[3 * obj.getIndices()[i] + 2];
			glNormal3f(normalX, normalY, normalZ);
		}
    }
    glEnd();
}