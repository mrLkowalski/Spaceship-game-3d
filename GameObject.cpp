#include "GameObject.h"



GameObject::GameObject(glm::vec3 worldPosition, glm::vec3 localRotation)
{
	this->worldPosition = worldPosition;
	this->localRotation = localRotation;
}


GameObject::~GameObject()
{
}
