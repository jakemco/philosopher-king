#ifndef __ObjReader_h__
#define __ObjReader_h__

class ObjReader
{
public:
    ObjReader();
    ObjReader(char* filename);

    void flipHorizontal();

    int getNVerts();
    float const * const getVertices();
    float const * const getNormals();
    float const * const getTexcoords();
    int const * const getIndices();
    int getNIndices();


    int nVerts;
    float *vertices;
    float *normals;
    float *texcoords;
    int nIndices;
    int *indices;
private:
    static void get_indices(char *word, int *vindex, int *tindex, int *nindex);
    void readObj(char* fileName, int &nVertices, float **vertices,
        float **normals, float **texcoords, int &nIndices, int **indices);
};

#endif 