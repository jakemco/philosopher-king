#include <iostream>
#include <ctime>

#include "RandomTrench.h"

#define CHANCE_BUILDING 0.05f

RandomTrench::RandomTrench()
{
	this->start = 0;
	this->depth = 0;
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
				this->buildings.insert(new Building(-i));
			} 
		}// end loop
	}//end depth check

	this->start = z;
	this->depth = d;

}


void RandomTrench::render()
{
	std::set<Building*> things;

	for(Building* b : this->buildings) {

		if (abs(b->getDepth()) < this->start){
			things.insert(b);
		} else {
			b->draw();
		}
	}

	for (Building* b : things) {
		this->buildings.erase(b);
		delete b;
	}
}
