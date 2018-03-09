#include "SpaceShip.h"



SpaceShip::SpaceShip()
{
	//sets default values to class variables
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	forward = glm::vec3(0.0f, 0.0f, 1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	camera = NULL;
}

void SpaceShip::initialize(glm::vec3 position, glm::vec3 forward, glm::vec3 up, Camera* camera)
{
	//sets parameters to class variables
	this->position = position;
	this->forward = forward;
	this->up = up;
	this->camera = camera;
}

void SpaceShip::fixedUpdate()
{
	float deltaTime = GLUT_ELAPSED_TIME / 1000.0f;//determins delta time in seconds
	glm::vec3 tempVelocity = glm::vec3(velocity.x * deltaTime, velocity.y * deltaTime, velocity.z * deltaTime);//multiplies velocity with delta time scaler
	position += tempVelocity * deltaTime; //applies velocity to spaceship position again with delta time scaler

	camera->updateCamera(position, forward, up); //updates camera to be in the same place and with the same forward and up vectors
}

void SpaceShip::update()
{

}

void SpaceShip::move(glm::vec3 direction, bool positive)
{
	direction = glm::normalize(direction); //normalizes direction of movement

	if (positive)//using parameter positive establishes whether value is positive or negative
	{
		velocity += direction * acceleration; //multiplies direction vector with acceleration value then adds it to velocity vector
	}
	else
	{
		velocity += direction * -acceleration;
	}

	if (glm::length(velocity) > maxSpeed)//making sure that spaceship does not move faster than its maximum speed
	{
		velocity = glm::normalize(velocity) * maxSpeed;
	}
}

void SpaceShip::rotateX(bool positive)
{
	glm::vec3 xAxis = glm::cross(up, forward);//determins horizontal vector
	xAxis = glm::normalize(xAxis);//normalizes horizontal vector

	if (positive)
	{
		forward = glm::rotate(forward, rotationSpeed, xAxis); //rotates around horizontal vector using already set rotation speed then sets new forward vector
	}
	else
	{
		forward = glm::rotate(forward, -rotationSpeed, xAxis);
	}

	forward = glm::normalize(forward); //makes sure forward vector is normalized

	up = glm::cross(forward, xAxis); //sets new up vector
	up = glm::normalize(up);//normalize up vector
}

void SpaceShip::rotateY(bool positive)
{
	glm::vec3 xAxis = glm::cross(up, forward); //same as above in rotateX
	xAxis = glm::normalize(xAxis);

	if (positive)
	{
		forward = glm::rotate(forward, rotationSpeed, up); //rotates around up vector
	}
	else
	{
		forward = glm::rotate(forward, -rotationSpeed, up);
	}

	forward = glm::normalize(forward); //same as above

	up = glm::cross(forward, xAxis);
	up = glm::normalize(up);
}

void SpaceShip::rotateZ(bool positive)
{
	glm::vec3 xAxis = glm::cross(up, forward); //same as above
	xAxis = glm::normalize(xAxis);

	if (positive)
	{
		up = glm::rotate(up, rotationSpeed, forward); //rotates around forward vector
	}
	else
	{
		up = glm::rotate(up, -rotationSpeed, forward);
	}

	up = glm::normalize(up);
}

glm::vec3 SpaceShip::getForwardVector()
{
	return glm::normalize(forward);
}

glm::vec3 SpaceShip::getLeftVector()
{
	glm::vec3 leftVector = glm::cross(up, forward);
	return glm::normalize(leftVector);
}

glm::vec3 SpaceShip::getRightVector()
{
	glm::vec3 rightVector = glm::cross(forward, up);
	return glm::normalize(rightVector);
}

glm::vec3 SpaceShip::getPosition()
{
	return position;
}

float SpaceShip::getBoundingRadius()
{
	return boundingRadius;
}

SpaceShip::~SpaceShip()
{
}
