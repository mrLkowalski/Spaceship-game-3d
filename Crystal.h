#pragma once
#include "GameObject.h"
#include <vector>
#include "SpaceShip.h"

#include <math.h>						
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>	//Needed for console output (debugging)
#include <gl/freeglut.h>
#include <iostream>

#ifdef WIN32
#include "..\gltools.h"
#include <windows.h>		// Must have for Windows platform builds
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <gl\glu.h>			// OpenGL Utilities
#include "..\shared\glm\glm.hpp"
#endif

#define GLM_ENABLE_EXPERIMENTAL
#include "..\shared\glm\gtx\rotate_vector.hpp"
#include "..\shared\glm\gtx\quaternion.hpp"

class Crystal :
	public GameObject
{

	float innerRadius;
	float outerRadius;
	GLint texture;
	glm::vec3 crystalLocalRotation;

	float hoopRotationSpeed = 0.2f;
	float crystalRotationSpeed = -0.2f;
	bool isNext = false;
	bool active = true;

	std::vector<glm::vec3> collisionPoints;

public:
	Crystal(glm::vec3 worldPosition, glm::vec3 localRotation);

	void initialize(float innerRadius, float outerRadius, GLint texture);
	void fixedUpdate();
	void update();

	void draw();
	void drawCollisionPoints();

	void checkForCollision(SpaceShip* spaceShip);
	void setNext();
	bool getActive();

	~Crystal();
};

