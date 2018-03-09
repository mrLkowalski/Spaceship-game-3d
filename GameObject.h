#pragma once
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

class GameObject
{
protected:
	glm::vec3 worldPosition;
	glm::vec3 localRotation;
public:
	GameObject(glm::vec3 worldPosition, glm::vec3 localRotation);

	//virtual void initialize() = 0;
	virtual void fixedUpdate() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	~GameObject();
};

