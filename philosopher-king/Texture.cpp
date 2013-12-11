#include "Texture.h"

using namespace std; // allow console printouts without std::

/*! GLUT display callback function */
void display(void);
/*! GLUT window reshape callback function */
void reshape(int, int);
/*! GLUT idle callback function */
void idle();

unsigned char* Texture::data[MAX_MAPS];
int Texture::width[MAX_MAPS];
int Texture::height[MAX_MAPS];
GLuint Texture::textures[MAX_MAPS];

/** Load a ppm file from disk.
@input filename The location of the PPM file.  If the file is not found, an error message
will be printed and this function will return 0
@input width This will be modified to contain the width of the loaded image, or 0 if file not found
@input height This will be modified to contain the height of the loaded image, or 0 if file not found
@return Returns the RGB pixel data as interleaved unsigned chars (R0 G0 B0 R1 G1 B1 R2 G2 B2 .... etc) or 0 if an error ocured
**/
unsigned char* Texture::loadPPM(const char* filename, int& width, int& height)
{
    const int BUFSIZE = 128;
    FILE* fp;
    unsigned int read;
    unsigned char* rawData;
    char buf[3][BUFSIZE];
    char* retval_fgets;
    size_t retval_sscanf;

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
        width = 0;
        height = 0;
        return NULL;
    }

    // Read magic number:
    retval_fgets = fgets(buf[0], BUFSIZE, fp);

    // Read width and height:
    do
    {
        retval_fgets = fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
    retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
    width = atoi(buf[1]);
    height = atoi(buf[2]);

    // Read maxval:
    do
    {
        retval_fgets = fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');

    // Read image data:
    rawData = new unsigned char[width * height * 3];
    read = fread(rawData, width * height * 3, 1, fp);
    fclose(fp);
    if (read != 1)
    {
        std::cerr << "error parsing ppm file, incomplete data" << std::endl;
        delete[] rawData;
        width = 0;
        height = 0;
        return NULL;
    }

    return rawData;
}

void Texture::loadPPM(const char* filename, int index)
{
    data[index] = loadPPM(filename, width[index], height[index]);

    if (data[index] == NULL) {
        std::cerr << "rawData is null" << std::endl;
        return;
    }

    glGenTextures(1, &textures[index]);
}

// load image file into texture object
void Texture::loadTexture(int index)
{
    // Load image file
    if (data[index] == NULL) return;

    glBindTexture(GL_TEXTURE_2D, textures[index]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width[index], height[index], 0, GL_RGB, GL_UNSIGNED_BYTE, data[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}
