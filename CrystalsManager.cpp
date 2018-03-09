#include "CrystalsManager.h"



CrystalsManager::CrystalsManager()
{
}

void CrystalsManager::spawnCrystals()
{
	crystals.push_back(new Crystal(glm::vec3(150.0f, 0.0f, 20.0f), glm::vec3()));
	crystals.push_back(new Crystal(glm::vec3(0.0f, 0.0f, 200.0f), glm::vec3()));
	crystals.push_back(new Crystal(glm::vec3(-20.0f, 100.0f, 400.0f), glm::vec3()));
	crystals.push_back(new Crystal(glm::vec3(-60.0f, -100.0f, 300.0f), glm::vec3()));
	crystals.push_back(new Crystal(glm::vec3(0.0f, 20.0f, 650.0f), glm::vec3()));
	crystals.push_back(new Crystal(glm::vec3(-50.0f, -40.0f, 800.0f), glm::vec3()));

	crystals.front()->setNext();
}

void CrystalsManager::initialize(float innerRadius, float outerRadius, GLint texture, SpaceShip* spaceShip)
{
	this->spaceShip = spaceShip;

	spawnCrystals();

	for (Crystal* crystal : crystals)
	{
			crystal->initialize(innerRadius, outerRadius, texture);
	}
}

void CrystalsManager::fixedUpdate()
{
	for (Crystal* crystal : crystals)
	{
		if (!crystal->getActive())
		{
			crystals.remove(crystal);

			if (crystals.size() != 0)
			{
				crystals.front()->setNext();
			}
			else
			{
				std::cout << "congratulations you won the game" << std::endl;
			}
			break;
		}
			crystal->fixedUpdate();
			crystal->checkForCollision(spaceShip);
	}
}

void CrystalsManager::update()
{
	for (Crystal* crystal : crystals)
	{
			crystal->update();
	}
}

void CrystalsManager::draw()
{
	for (Crystal* crystal : crystals)
	{
			crystal->draw();
	}
}

CrystalsManager::~CrystalsManager()
{
}
