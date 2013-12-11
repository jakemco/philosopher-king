#pragma once

#include <map>
#include <chrono>

#include "Building.h"
#include "Ship.h"

class RandomTrench
{
private:
	int start;
	int depth;

	float size;

	std::map<int,Building*> buildings;

	bool above;
	std::chrono::time_point<std::chrono::system_clock> above_t;

public:
	RandomTrench(float size);
	~RandomTrench();
	void update(int minZ, int maxZ);
	void render();

	bool collision(const Ship&);
};

