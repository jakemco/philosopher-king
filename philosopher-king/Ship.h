//
//  Ship.h
//  philosopher-king
//
//  Created by Jacob Maskiewicz on 12/8/13.
//  Copyright (c) 2013 Jacob Maskiewicz. All rights reserved.
//

#pragma once

#include <SFML/Audio.hpp>

#include <set>

#include "Vector4.h"
#include "BoundingBox.h"
#include "Laser.h"

class Ship {
    
friend class RandomTrench;
private:
    Vector4 position;
	Vector4 rotate;
	float angle;
	float zrotAngle;

	bool crashed;

	float charge;
    float burst;
    bool cooldown;
    
    static sf::SoundBuffer buffer;
    sf::Sound* blaster;
    sf::Music flying;

	std::set<Laser*> lasers;

public:
	static const float SPEED;
    static const float RECHARGE;
    
    Ship();
    ~Ship();
    
    void update(float, float, float, float, bool);
    void render();
    
    Vector4 getPosition() const;
	BoundingBox getBox() const;

	void crash();
	void reset();
    
    float getBurst() const;
};