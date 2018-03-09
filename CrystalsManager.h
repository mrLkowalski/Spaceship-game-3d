#pragma once
#include "Crystal.h"
#include "SpaceShip.h"
#include <list>

class CrystalsManager
{
	SpaceShip* spaceShip;
	std::list<Crystal*> crystals;

public:
	CrystalsManager();

	void spawnCrystals();

	void initialize(float innerRadius, float outerRadius, GLint texture, SpaceShip* spaceShip);
	void fixedUpdate();
	void update();
	void draw();

	~CrystalsManager();
};

