#pragma once
#include "Camera.h"

#include <math.h>						
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>	//Needed for console output (debugging)
#include <gl/freeglut.h>
#include <iostream>
#include <sstream>

#ifdef WIN32
#include "..\gltools.h"
#include <windows.h>		// Must have for Windows platform builds
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <gl\glu.h>			// OpenGL Utilities
#include "..\shared\glm\glm.hpp"
#endif

#include "..\shared\glm\mat4x4.hpp"
#include "..\shared\glm\gtc\type_ptr.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "..\shared\glm\gtx\rotate_vector.hpp"
#include "..\shared\glm\gtx\quaternion.hpp"

class SpaceShip
{
	glm::vec3 position;
	glm::vec3 velocity;

	glm::vec3 forward;
	glm::vec3 up;

	Camera* camera;

	float maxSpeed = 2.0f;
	float rotationSpeed = 0.02f;
	float acceleration = 0.005f;
	float boundingRadius = 10.0f;

public:
	SpaceShip();

	void initialize(glm::vec3 position, glm::vec3 forward, glm::vec3 up, Camera* camera);
	void fixedUpdate();
	void update();

	//get
	glm::vec3 getForwardVector();
	glm::vec3 getLeftVector();
	glm::vec3 getRightVector();
	glm::vec3 getPosition();
	float getBoundingRadius();

	//controls
	void move(glm::vec3 direction, bool positive);
	void rotateX(bool positive);
	void rotateY(bool positive);
	void rotateZ(bool positive);

	~SpaceShip();
};

