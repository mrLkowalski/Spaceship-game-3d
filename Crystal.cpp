#include "Crystal.h"



Crystal::Crystal(glm::vec3 worldPosition, glm::vec3 localRotation) : GameObject::GameObject(worldPosition, localRotation)
{
	this->crystalLocalRotation = localRotation;
}

void Crystal::initialize(float innerRadius, float outerRadius, GLint texture)
{
	//saving parameters to class variables
	this->innerRadius = innerRadius;
	this->outerRadius = outerRadius;
	this->texture = texture;

	int noOfPoints = 10;//determins density of collision points inside of a hoop
	glm::vec3 tempColPt(outerRadius, 0.0f, 0.0f);//vector used to generate collision points around hoop, using its radius

	//for loop which rotates vector and creates points
	for (int i = 0; i < noOfPoints; i++)
	{
		if (i == 0)
		{
			collisionPoints.push_back(tempColPt); // creates start collision point
		}
		else
		{
			tempColPt = glm::rotateZ(tempColPt, 360.0f / noOfPoints); //rotates in equal invtervals around 360 degrees 

			collisionPoints.push_back(tempColPt); //creates collision point after rotation occured
		}	
	}

}

void Crystal::fixedUpdate()
{
	float deltaTime = GLUT_ELAPSED_TIME / 1000.0f; //returns delta time in seconds

	localRotation.y += hoopRotationSpeed * deltaTime; //rotates by set rotation value multiplied by deltatime scaler

	//if statement that makes sure rotation is within 0-360 degrees
	if (localRotation.y > 360)
	{
		localRotation.y - 360;
	}
	else if (localRotation.y < 0)
	{
		localRotation.y + 360;
	}

	//same but for crystal that is inside in hoop
	crystalLocalRotation.y += crystalRotationSpeed * deltaTime;

	if (crystalLocalRotation.y > 360)
	{
		crystalLocalRotation.y - 360;
	}
	else if (crystalLocalRotation.y < 0)
	{
		crystalLocalRotation.y + 360;
	}
}

void Crystal::update()
{

}

void Crystal::draw()
{
	glPushMatrix();

	//performing transformations
	glTranslatef(worldPosition.x, worldPosition.y, worldPosition.z);
	glRotatef(localRotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(localRotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(localRotation.z, 0.0f, 0.0f, 1.0f);

	glColor4ub(255, 255, 255, 255);//sets default colour underneeth a texture

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); //these generate texture coordinates
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_2D); //enables textures
	glBindTexture(GL_TEXTURE_2D, texture); //load texture

	glutSolidTorus(innerRadius, outerRadius, 50, 50); //draws a hoop

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);//disables textures

	glPopMatrix();

	glPushMatrix();

	//performs transformations
	glTranslatef(worldPosition.x, worldPosition.y, worldPosition.z);
	glRotatef(crystalLocalRotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(crystalLocalRotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(crystalLocalRotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(20.0f, 20.0f, 20.0f);


	//if this crystal is next for player to obtain it changes colour to green otherwise uses its default colour
	if (isNext)
	{
		glColor4ub(0, 128, 0, 255);
	}
	else
	{
		glColor4ub(128, 0, 0, 255);
	}

	glutSolidIcosahedron();//draws crystal inside a hoop

	glPopMatrix();

	drawCollisionPoints();//draws collision points, used for testing
}

void Crystal::drawCollisionPoints()//only used for testing method
{
	glPushMatrix();

	glColor3ub(255, 0, 0);

	glTranslatef(worldPosition.x, worldPosition.y, worldPosition.z);
	glRotatef(localRotation.y, 0.0f, 1.0f, 0.0f);

	glBegin(GL_POINTS);
	for (auto collisionPoint : collisionPoints)
	{
		glVertex3f(collisionPoint.x, collisionPoint.y, collisionPoint.z);
	}
	glEnd();

	glPopMatrix();
}

void Crystal::checkForCollision(SpaceShip* spaceShip)
{
	//using distance formula, if statement checks whether ship is close enough to the center of the crystal, moreover spaceship radius is doubled to make it easier for player to capture crystal
	if (glm::length(spaceShip->getPosition() - worldPosition) <= spaceShip->getBoundingRadius() * 2.0f)
	{
		if (isNext)
		{
			active = false;
		}
	}

	//for loop that will check using distance formula whether spaceship is not colliding with any of a collision points. 
	for (auto collisionPoint : collisionPoints)
	{
		glm::vec3 tempCollisionPoint = collisionPoint;

		//each point is rotated by crystal local rotation to match hoop location
		tempCollisionPoint = glm::rotateX(tempCollisionPoint, localRotation.x);
		tempCollisionPoint = glm::rotateY(tempCollisionPoint, localRotation.y);
		tempCollisionPoint = glm::rotateZ(tempCollisionPoint, localRotation.z);
		tempCollisionPoint = tempCollisionPoint + worldPosition;

		//if statement that checks if spaceship is close enough to trigger collision
		if (glm::length(tempCollisionPoint - spaceShip->getPosition()) <= spaceShip->getBoundingRadius())
		{
			std::cout << "You have lost the game" << std::endl; // displays in console that ship has collided and the game is over
		}
	}
}

void Crystal::setNext()
{
	isNext = true;
}

bool Crystal::getActive()
{
	return active;
}

Crystal::~Crystal()
{
}
