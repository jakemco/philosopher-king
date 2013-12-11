#pragma once

#include <map>

#include "Building.h"
#include "Ship.h"

class RandomTrench
{
private:
	int start;
	int depth;

	float size;

	std::map<int,Building*> buildings;

public:
	RandomTrench(float size);
	~RandomTrench();
	void update(int minZ, int maxZ);
	void render();

	bool collision(const Ship&);
};

