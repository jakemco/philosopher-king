#include <iostream>
#include <ctime>
#include <set>

#include "RandomTrench.h"

#define CHANCE_BUILDING 0.05f

RandomTrench::RandomTrench(float size)
{
	this->start = 0;
	this->depth = 0;
	this->size = size;
}


RandomTrench::~RandomTrench()
{
}


void RandomTrench::update(int z, int d)
{
	z = abs(z);

	if (z+d > start+depth) {
		for (int i = start + depth; i < z + d; i++) {
			//generate a building at depth i and add it to the map
			float hasBuilding = (float) rand() / (float) RAND_MAX;

			if (hasBuilding < CHANCE_BUILDING) {
				this->buildings[i] = new Building(-i,size);
			} 
		}// end loop
	}//end depth check

	this->start = z;
	this->depth = d;

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
