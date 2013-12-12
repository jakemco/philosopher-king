
#include <cstdlib>
#include "GLee.h"

#ifdef WIN32
  #include "GL/glut.h"
#else
  #include "GLUT/glut.h"
#endif

#include <iostream>
#include <ctime>

#include "Building.h"
#include "Texture.h"

#define RAND_FLOAT(min,max) ((min) + (((float)rand()/(float)RAND_MAX)*((max) - (min))))

Building::Building(int d, float size, float width, float height, float depth, bool allow_sphere)
{
	this->wall_part = !allow_sphere;

	float x = RAND_FLOAT(1, depth);
	float y = RAND_FLOAT(1, width);
	float h = RAND_FLOAT(1, height);

	float t = RAND_FLOAT(0, 1);
	if (allow_sphere && t < 0.4) {
		type = Sphere;
		sphere_size = RAND_FLOAT(0.5, 2);
	}
	else type = Cube;

	float s = RAND_FLOAT(0, 1);
	if (s < 0.3) {
		//left
		this->position = Vector4(
			(-size / 2) + (type == Cube ? h/2 : 0),
			RAND_FLOAT(-size/2,size/2),
			d,1);
		this->size = Vector4(h, y, x);
	}
	else if (s < 0.6) {
		//right
		this->position = Vector4(
			(size / 2) - (type == Cube ? h / 2 : 0),
			RAND_FLOAT(-size / 2, size / 2),
			d,1);
		this->size = Vector4(h, y, x);
	}
	else {
		//bottom
		this->position = Vector4(
			RAND_FLOAT(-size / 2, size / 2),
			-size / 2 + (type == Cube ? h / 2 : 0),
			d,1);
		this->size = Vector4(y, h, x);
	}

	crashed = false;

	/*
	std::cout << (type == Sphere ? "Sphere" : "Cube") << " at " << d << ": " << std::endl;
	std::cout << "\t";  position.print();
	std::cout << "\t";  size.print();
	*/

}

Building::~Building() {}

Vector4 Building::getPosition() const {
	return this->position;
}

int Building::getDepth() const {
	return this->position.z();
}

void Building::draw() const {

	glPushMatrix();

	glTranslatef(position.x(), position.y(), position.z());

	if (crashed) glColor3f(1.0, 0.2, 0.2);
	else if (wall_part)
	{
        glColor3f(1, 1, 1);
	}
	else glColor3f(1.0, 1.0, 1.0);

	if (type == Sphere) glutSolidSphere(sphere_size, 20, 20);
	else if (type == Cube) {
		glScalef(size.x(), size.y(), size.z());

        if (wall_part) {
            draw_wall_part();
        }
        else {
            glutSolidCube(1.0);
        }
	}

	glPopMatrix();
}

void Building::draw_wall_part() const {
    glEnable(GL_TEXTURE_2D);
    float x0, x1, y0, y1, z0, z1;

    x0 = y0 = z0 = -0.5;
    x1 = y1 = z1 = 0.5;

    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);   // left face, const x0
    glTexCoord2f(0, 0);  glVertex3f(x0, y1, z0);
    glTexCoord2f(1, 0);  glVertex3f(x0, y1, z1);
    glTexCoord2f(1, 1);  glVertex3f(x0, y0, z1);
    glTexCoord2f(0, 1);  glVertex3f(x0, y0, z0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);   // front face, const z1
    glTexCoord2f(0, 0);  glVertex3f(x0, y1, z1);
    glTexCoord2f(1, 0);  glVertex3f(x1, y1, z1);
    glTexCoord2f(1, 1);  glVertex3f(x1, y0, z1);
    glTexCoord2f(0, 1);  glVertex3f(x0, y0, z1);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);   // right face, const x1
    glTexCoord2f(0, 0);  glVertex3f(x1, y1, z1);
    glTexCoord2f(1, 0);  glVertex3f(x1, y1, z0);
    glTexCoord2f(1, 1);  glVertex3f(x1, y0, z0);
    glTexCoord2f(0, 1);  glVertex3f(x1, y0, z1);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);   // back face, const z0
    glTexCoord2f(0, 0);  glVertex3f(x1, y1, z1);
    glTexCoord2f(1, 0);  glVertex3f(x0, y1, z1);
    glTexCoord2f(1, 1);  glVertex3f(x0, y0, z1);
    glTexCoord2f(0, 1);  glVertex3f(x1, y0, z1);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);   // top face, const y1
    glTexCoord2f(0, 0);  glVertex3f(x0, y1, z0);
    glTexCoord2f(1, 0);  glVertex3f(x1, y1, z0);
    glTexCoord2f(1, 1);  glVertex3f(x1, y1, z1);
    glTexCoord2f(0, 1);  glVertex3f(x0, y1, z1);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);   // bottom face, const y0
    glTexCoord2f(0, 0);  glVertex3f(x0, y0, z0);
    glTexCoord2f(1, 0);  glVertex3f(x1, y0, z0);
    glTexCoord2f(1, 1);  glVertex3f(x1, y0, z1);
    glTexCoord2f(0, 1);  glVertex3f(x0, y0, z1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

BoundingBox Building::getBox() const {
	if (type == Sphere)
		return BoundingBox(this->position, this->sphere_size * 2, this->sphere_size * 2, this->sphere_size * 2);
	else
		return BoundingBox(this->position, this->size.x(), this->size.y(), this->size.z());
}