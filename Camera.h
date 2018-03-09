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

#include <sstream>
#include "../shared/glm/mat4x4.hpp"
#include "..\shared\glm\gtc\type_ptr.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "..\shared\glm\gtx\rotate_vector.hpp"
#include "..\shared\glm\gtx\quaternion.hpp"

class Camera
{

	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;

	bool hudEnabled = true;

	void writeBitmapString(void *font, char *string);

public:
	Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up);

	glm::vec3 yAxisAbs;

	void cameraProjection(float aspectRatio);
	void cameraModelView();
	void setOrthographicProjection(float windowWidth, float windowHeight);
	void resetPerspectiveProjection();
	void drawHud(float windowWidth, float windowHeight, GLint texture);

	void updateCamera(glm::vec3 position, glm::vec3 forward, glm::vec3 up);

	//get
	glm::vec3 getForwardVector();
	glm::vec3 getLeftVector();
	glm::vec3 getRightVector();

	//controls
	void hud();

	~Camera();
};

