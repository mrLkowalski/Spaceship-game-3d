//Windows includes - DO NOT EDIT AS LOTS OF INTERDEPENDENCE


#include <math.h>						
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>	//Needed for console output (debugging)
#include <gl/freeglut.h>
#include <iostream>

#ifdef WIN32
#include "gltools.h"
#include <windows.h>		// Must have for Windows platform builds
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <gl\glu.h>			// OpenGL Utilities
#include "glm.h"
#endif
//
//  texture.cpp
//
//
//  Created by Philip Trwoga on 09/11/2012. Modified on 20/1/16 and 20/12/17 to include the many VS2015 changes
//  Copyright (c) 2012 __Philip Trwoga__. All rights reserved.
// DO NOT DISTRIBUTE WITHOUT THE AUTHOR'S PERMISSION



//note that this needs gltools.h and gltools.cpp to be included in the shared/library directory

//can define any number of textures here - we just have 2 images
//these are just integers so you can use them as such

//-----------GameEngine refs----------//
#include "3DExample1\Camera.h"
#include "3DExample1\SkyBox.h"
#include "3DExample1\GameObject.h"
#include "3DExample1\Planet.h"
#include "3DExample1\Crystal.h"
#include "3DExample1\CrystalsManager.h"
#include "3DExample1\SpaceShip.h"

#define TEXTURE_SKYBOX 0
#define TEXTURE_PLANET 1
#define TEXTURE_HOOP 2
#define TEXTURE_HUD 3

#define TEXTURE_COUNT 4
GLuint  textures[TEXTURE_COUNT];

//below is simply a character array to hold the file names
//note that you may need to replace the below with the full directory root depending on where you put your image files
//if you put them where the exe is then you just need the name as below - THESE IMAGES  ARE IN THE DEBUG FOLDER, YOU CAN ADD ANY NEW ONES THERE 
const char *textureFiles[TEXTURE_COUNT] = {"tycho_cyl_glow.tga", "jupiterC.tga", "starField.tga", "hud.tga"};

//key handling - only one shown simplly as an example
bool upKeyPressed = false;
bool downKeyPressed = false;
bool leftKeyPressed = false;
bool rightKeyPressed = false;
bool wKeyPressed = false;
bool sKeyPressed = false;
bool aKeyPressed = false;
bool dKeyPressed = false;
bool zKeyPressed = false;
bool xKeyPressed = false;

// lighting

GLfloat  whiteLightLessBright[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat  whiteLightBright[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat	 lightPos0[] = { 50.0f, 50.0f, 0.0f, 0.0f };

//we need these for the texture loader
//they are to do with the image format and size
GLint iWidth, iHeight, iComponents;
GLenum eFormat;
// this is a pointer to memory where the image bytes will be held 
GLbyte *pBytes0;

//end of intialisation 

//------------------------------------//

//--------Game engine variables----------//
float fixedUpdateTimerDelay = 1400.0f;
float fixedUpdateTimerAccumulator = fixedUpdateTimerDelay;
//--------Game engine variables end------//

//--------Game Instances----------//
Camera camera(glm::vec3(0.0f, 0.0f, -600.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
SkyBox skybox;
Planet planet1(glm::vec3(500.0f, 100.0f, 50.0f), glm::vec3(0.0f, 0.0f, 0.0f));
Planet planet2(glm::vec3(-500.0f, -100.0f, -50.0f), glm::vec3(0.0f, 0.0f, 0.0f));
CrystalsManager crystalsManager;
SpaceShip spaceShip;

//----------GameEngine essential methods---------//

void initialize(void)
{
	//--------------------Textures----------------//

	GLuint texture;
	// allocate a texture name
	glGenTextures(1, &texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// photoshop is a good converter to targa (TGA)
	//the gltLoadTGA method is found in gltools.cpp and is orignally from the OpenGL SuperBible book
	//there are quite a few ways of loading images
	// Load textures in a for loop
	glGenTextures(TEXTURE_COUNT, textures);
	//this puts the texture into OpenGL texture memory
	//   glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); - not defined so probably need to update GLEW - not needed here so ignore
	for (int iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++)
	{
		// Bind to next texture object
		glBindTexture(GL_TEXTURE_2D, textures[iLoop]);

		// Load texture data, set filter and wrap modes
		//note that gltLoadTGA is in the glm.cpp file and not a built-in openGL function
		pBytes0 = gltLoadTGA(textureFiles[iLoop], &iWidth, &iHeight,
			&iComponents, &eFormat);

		glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes0);

		//set up texture parameters

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		free(pBytes0);

		//--------------------Textures-END------------//
	}

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal    
	glFrontFace(GL_CCW);// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside
	glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);//enable lighting

	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLightLessBright);//sets ambient light

	//defines position and colour of gl_light0 then enables it
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLightBright);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glEnable(GL_LIGHT0);


	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//------------GAME-INITIALIZATIONS-----------//
	planet1.initialize(100.0f, textures[TEXTURE_PLANET]);
	planet2.initialize(200.0f, textures[TEXTURE_PLANET]);
	crystalsManager.initialize(5.0f, 60.0f, textures[TEXTURE_HOOP], &spaceShip);
	spaceShip.initialize(glm::vec3(0.0f, 0.0f, -600.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), &camera);
	//------------GAME-INITIALIZATIONS-END-------//
}

void update(void)
{

}

void fixedUpdate(void)
{
	//using booleans processing imputs
	if (upKeyPressed)
	{
		spaceShip.rotateX(true);
	}
	if (downKeyPressed)
	{
		spaceShip.rotateX(false);
	}
	if (leftKeyPressed)
	{
		spaceShip.rotateZ(false);
	}
	if (rightKeyPressed)
	{
		spaceShip.rotateZ(true);
	}
	if (zKeyPressed)
	{
		spaceShip.rotateY(true);
	}
	if (xKeyPressed)
	{
		spaceShip.rotateY(false);
	}
	if (wKeyPressed)
	{
		spaceShip.move(spaceShip.getForwardVector(), true);
	}
	if (sKeyPressed)
	{
		spaceShip.move(spaceShip.getForwardVector(), false);
	}
	if (aKeyPressed)
	{
		spaceShip.move(spaceShip.getLeftVector(), true);
	}
	if (dKeyPressed)
	{
		spaceShip.move(spaceShip.getRightVector(), true);
	}

	fixedUpdateTimerAccumulator += GLUT_ELAPSED_TIME;

	if (fixedUpdateTimerAccumulator >= fixedUpdateTimerDelay)
	{
		fixedUpdateTimerAccumulator = 0.0f;
		planet1.fixedUpdate();
		planet2.fixedUpdate();
		crystalsManager.fixedUpdate();
		spaceShip.fixedUpdate();
	}
}

void draw(void)
{
	// Clear the window with current clearing colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.cameraModelView();

	skybox.drawSkyBox(textures[TEXTURE_SKYBOX]);

	planet1.draw();
	planet2.draw();
	crystalsManager.draw();

	camera.setOrthographicProjection(800.0f, 600.0f);
	camera.drawHud(800.0f, 600.0f, textures[TEXTURE_HUD]);
	camera.resetPerspectiveProjection();
}

void gameLoop(void)
{
	fixedUpdate();
	update();
	draw();

	glutSwapBuffers();
	glutPostRedisplay();
}

//----------GameEngine essential methods END---------//

void ChangeSize(int w, int h)
{
    GLfloat fAspect;
    
    // Prevent a divide by zero
    if(h == 0)
        h = 1;
    
    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);
    
    // Calculate aspect ratio of the window
    fAspect = (GLfloat)w/(GLfloat)h;
    
	camera.cameraProjection(fAspect);
}


void processsArrowKeys(int key, int x, int y)
{
	//setting booleans responsible for holding buttons on after pressing special keys

	if (key == GLUT_KEY_LEFT)
	{
		leftKeyPressed = true;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		rightKeyPressed = true;
	}

	if (key == GLUT_KEY_UP)
	{
		upKeyPressed = true;
	}

	if (key == GLUT_KEY_DOWN)
	{
		downKeyPressed = true;
	}

}

void keyGoneUP(int key, int x, int y)
{
	//setting booleans responsible for holding buttons off after relasing special keys
	switch (key) {
	case GLUT_KEY_UP:
		upKeyPressed = false;
		break;
	case GLUT_KEY_DOWN:
		downKeyPressed = false;
		break;
	case GLUT_KEY_LEFT:
		leftKeyPressed = false;
		break;
	case GLUT_KEY_RIGHT:
		rightKeyPressed = false;
		break;
	}
}

void keyGoneUPstd(unsigned char key, int x, int y)
{
	//setting booleans responsible for holding buttons off after relasing keys
	switch (key) {
	case 'w':
		wKeyPressed = false;
		break;
	case 's':
		sKeyPressed = false;
		break;
	case 'a':
		aKeyPressed = false;
		break;
	case 'd':
		dKeyPressed = false;
		break;
	case 'z':
		zKeyPressed = false;
		break;
	case 'x':
		xKeyPressed = false;
		break;
	}
}

void processKeys(unsigned char key, int x, int y)
{
	//setting booleans responsible for holding buttons on after pressing keys
	switch (key) {
	case 'w':
		wKeyPressed = true;
		break;
	case 's':
		sKeyPressed = true;
		break;
	case 'a':
		aKeyPressed = true;
		break;
	case 'd':
		dKeyPressed = true;
		break;
	case 'z':
		zKeyPressed = true;
		break;
	case 'x':
		xKeyPressed = true;
		break;
	case 'h':
		camera.hud();
		break;
	}
}



int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);// a 4:3 ratio
	glutCreateWindow("SpaceShip game");
	initialize();
	glutSpecialFunc(processsArrowKeys);
	glutSpecialUpFunc(keyGoneUP);
	glutKeyboardFunc(processKeys);
	glutKeyboardUpFunc(keyGoneUPstd);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(gameLoop);
	glutMainLoop();
	return 0;
}






