#pragma once
#include "GameObject.h"

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

class Planet :
	public GameObject
{
	float radius;
	GLint texture;

	float planetRotationSpeed = 0.02f;
public:
	Planet(glm::vec3 worldPosition, glm::vec3 localRotation);

	void initialize(float radius, GLint texture);
	void fixedUpdate();
	void update();
	void draw();

	~Planet();
};

