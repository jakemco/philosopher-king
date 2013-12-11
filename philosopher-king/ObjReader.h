#ifndef __ObjReader_h__
#define __ObjReader_h__

#include <cmath>

class ObjReader
{
public:
    ObjReader();
    ObjReader(char* filename);

    float maxVert();

    int getNVerts();
    float const * const getVertices();
    float const * const getNormals();
    float const * const getTexcoords();
    int const * const getIndices();
    int getNIndices();
    int getMaxRange();

private:
    int nVerts;
    float *vertices;
    float *normals;
    float *texcoords;
    int nIndices;
    int *indices;
    float maxRange;

    static void get_indices(char *word, int *vindex, int *tindex, int *nindex);
    void readObj(char* fileName, int &nVertices, float **vertices,
        float **normals, float **texcoords, int &nIndices, int **indices);
    void findMinMaxVerts();
};

#endif 