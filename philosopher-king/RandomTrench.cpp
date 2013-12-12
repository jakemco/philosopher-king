#include <cstdlib>

#include "GLee.h"

#ifdef WIN32
#include "GL/glut.h"
#else
#include "GLUT/glut.h"
#endif

#include <algorithm>
#include <iostream>
#include <ctime>
#include <set>

#include "RandomTrench.h"

#include "Texture.h"

#define RAND_FLOAT(min,max) ((min) + (((float)rand()/(float)RAND_MAX)*((max) - (min))))

#define CHANCE_BUILDING 0.05f

#define LASERS_PER_SECOND 30

#define DRAW_DIST 1000
#define TEX_SIZE 20
#define SURFACE_TEX_SIZE 5
#define SIDE_TEX_SIZE 2
#define BOTTOM_TEX_SIZE 1

RandomTrench::RandomTrench(float size)
{
	this->start = 0;
	this->depth = 0;
	this->size = size;
}


RandomTrench::~RandomTrench()
{
	for (std::pair<int,Building*> b : this->buildings) delete b.second;
	for (Laser* l : this->lasers) delete l;
}


void RandomTrench::update(float dt, const Vector4& position, int d)
{

	float z = abs(position.z());

	if (z+d > start+depth) {
		for (int i = start + depth; i < z + d; i++) {
			//generate a building at depth i and add it to the map
			float hasBuilding = (float) rand() / (float) RAND_MAX;

			if (hasBuilding < CHANCE_BUILDING) {
				this->buildings[i] = new Building(-i, size, 3, size, 10, true);
			}
			else if (hasBuilding < 0.8) {
				this->buildings[i] = new Building(-i, size, 5, 0.1, 5, false);
			}
		}// end loop
	}//end depth check

	this->start = z;
	this->depth = d;

	/* lasers! */

	for (int i = 0; i < dt*LASERS_PER_SECOND; i++) {
		Vector4 p = Vector4(RAND_FLOAT(-1, 1)*RAND_FLOAT(size / 2, 50), size / 2.0, position.z() - RAND_FLOAT(0, 200), 1);
		Vector4 t = Vector4(position.x() + RAND_FLOAT(-5, 5), max((float) position.y(), size / 2) + RAND_FLOAT(0, 10), position.z() - Ship::SPEED / 2 - RAND_FLOAT(0, 10), 1);

		lasers.insert(new Laser(p, t));
	}

	std::set<Laser*> things;

	for (Laser* l : lasers) {
		l->update(dt);
		if (l->dead(200)) things.insert(l);
	}

	for (Laser* l : things) {
		lasers.erase(l);
		delete l;
	}

}


void RandomTrench::render()
{
	std::set<Building*> things;

	for(std::pair<int,Building*> b : this->buildings) {

		if (b.first < this->start){
			things.insert(b.second);
		} else {
			b.second->draw();
		}
	}

	for (Building* b : things) {
		this->buildings.erase(abs(b->getDepth()));
		delete b;
	}

	/* lasers */
	for (Laser* l : lasers) l->render();

	/* Draw dat trench */

	static const float half = size / 2.0;

	glEnable(GL_TEXTURE_2D);
	Texture::loadTexture(TRENCH_TEXTURE);
	glColor3f(1, 1, 1);
	float nearPoint = -this->start;

	float farPoint = nearPoint - DRAW_DIST;

	float nearTex = nearPoint / TEX_SIZE;
	float farTex = farPoint / TEX_SIZE;

	glBegin(GL_QUADS);  // Death Star surface -- left
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, nearTex); glVertex3f(-250, half, nearPoint);
	glTexCoord2f(0, farTex); glVertex3f(-250, half, farPoint);
	glTexCoord2f(SURFACE_TEX_SIZE, farTex); glVertex3f(-half, half, farPoint);
	glTexCoord2f(SURFACE_TEX_SIZE, nearTex); glVertex3f(-half, half, nearPoint);
	glEnd();

	glBegin(GL_QUADS); // trench surface -- left
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, nearTex); glVertex3f(-half, half, nearPoint);
	glTexCoord2f(0, farTex); glVertex3f(-half, half, farPoint);
	glTexCoord2f(SIDE_TEX_SIZE, farTex); glVertex3f(-half, -half, farPoint);
	glTexCoord2f(SIDE_TEX_SIZE, nearTex); glVertex3f(-half, -half, nearPoint);
	glEnd();

	glBegin(GL_QUADS); // trench surface -- bottom
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, nearTex); glVertex3f(-half, -half, nearPoint);
	glTexCoord2f(0, farTex); glVertex3f(-half, -half, farPoint);
	glTexCoord2f(BOTTOM_TEX_SIZE, farTex); glVertex3f(half, -half, farPoint);
	glTexCoord2f(BOTTOM_TEX_SIZE, nearTex); glVertex3f(half, -half, nearPoint);
	glEnd();

	glBegin(GL_QUADS); // trench surfacee -- right
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, nearTex); glVertex3f(half, -half, nearPoint);
	glTexCoord2f(0, farTex); glVertex3f(half, -half, farPoint);
	glTexCoord2f(SIDE_TEX_SIZE, farTex); glVertex3f(half, half, farPoint);
	glTexCoord2f(SIDE_TEX_SIZE, nearTex); glVertex3f(half, half, nearPoint);
	glEnd();

	glBegin(GL_QUADS); // Death Star surface -- right
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, nearTex); glVertex3f(half, half, nearPoint);
	glTexCoord2f(0, farTex); glVertex3f(half, half, farPoint);
	glTexCoord2f(SURFACE_TEX_SIZE, farTex); glVertex3f(250, half, farPoint);
	glTexCoord2f(SURFACE_TEX_SIZE, nearTex); glVertex3f(250, half, nearPoint);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
}

bool RandomTrench::collision(const Ship& ship) {
	Vector4 pos = ship.getPosition();

	int min = abs(pos.z()) - 5;
	int max = abs(pos.z()) + 5;

	const BoundingBox box = ship.getBox();

	for (int d = min; d <= max; d++) {
		if (buildings.count(d)) {
			if (buildings[d]->getBox().contains(box)) {
				buildings[d]->crash();
				return true;
			}
		}
	}

	return box.custom([&](const Vector4& min, const Vector4& max){
		if (min.y() > size / 2) {
			typedef std::chrono::seconds seconds;
			auto duration = std::chrono::steady_clock::now() - above_t;

			if ( std::chrono::duration_cast<seconds>(duration).count() > 1) return true;
		} else {
			above_t = std::chrono::steady_clock::now();

			if (min.x() < -size / 2) return true;
			if (max.x() > size / 2) return true;
			if (min.y() < -size / 2) return true;
		}
		return false;
	});

}
