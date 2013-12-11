#pragma once

#include <functional>
#include <set>

#include "Building.h"

class RandomTrench
{
private:
	int start;
	int depth;

	std::set<Building*> buildings;

public:
	RandomTrench();
	~RandomTrench();
	void update(int minZ, int maxZ);
	void render();
};

