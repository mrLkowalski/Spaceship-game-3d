#include "Planet.h"



Planet::Planet(glm::vec3 worldPosition, glm::vec3 localRotation) : GameObject::GameObject(worldPosition, localRotation)
{
}

void Planet::initialize(float radius, GLint texture)
{
	//saving parameters to class variables
	this->radius = radius;
	this->texture = texture;
}

void Planet::fixedUpdate()
{
	float deltaTime = GLUT_ELAPSED_TIME / 1000.0f; //saves delta time in the variable time is divided by 1000 to obrain it in seconds

	localRotation.y += planetRotationSpeed * deltaTime; //appling planet rotation multiplayed by deltatime scaler

	//if statements that make sure planet rotates within 0-360 degrees angle
	if (localRotation.y > 360)
	{
		localRotation.y - 360;
	}
	else if (localRotation.y < 0)
	{
		localRotation.y + 360;
	}
}

void Planet::update()
{

}

void Planet::draw()
{

	glPushMatrix();

	//performing transformation matrixes local rotations then translation
	glTranslatef(worldPosition.x, worldPosition.y, worldPosition.z);
	glRotatef(localRotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(localRotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(localRotation.z, 0.0f, 0.0f, 1.0f);

	glEnable(GL_TEXTURE_2D); //enable textures
	glBindTexture(GL_TEXTURE_2D, texture); //load texture

	glColor4ub(255, 255, 255, 255); //sets default color of sphere underneeth the texture
	gltDrawSphere(radius, 50, 50); //draws planet sphere

	glDisable(GL_TEXTURE_2D); //disable textures

	glPopMatrix();
}

Planet::~Planet()
{
}
