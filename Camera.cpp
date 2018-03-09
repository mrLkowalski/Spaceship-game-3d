#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up)
{
	//sets absolute up vector
	yAxisAbs = glm::vec3(0.0f, 1.0f, 0.0f);

	this->position = position;
	this->forward = forward;
	this->up = up;

	this->forward = glm::normalize(this->forward);
	this->up = glm::normalize(this->up);

}

void Camera::cameraProjection(float aspectRatio)
{
	// Set the perspective coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// field of view of 45 degrees, near and far planes 1.0 and 1000
	//that znear and zfar should typically have a ratio of 1000:1 to make sorting out z depth easier for the GPU
	gluPerspective(74.0f, aspectRatio, 1.0, 8000.0); //may need to make larger depending on project
}

void Camera::cameraModelView()
{	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, position.x + forward.x, position.y + forward.y, position.z + forward.z, up.x, up.y, up.z);
}

void Camera::setOrthographicProjection(float windowWidth, float windowHeight)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, windowWidth, 0, windowHeight);
	glScalef(1, -1, 1);
	glTranslatef(0, -windowHeight, 0);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);//disables lighting
}

void Camera::resetPerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);//enable lighting
}

void Camera::drawHud(float windowWidth, float windowHeight, GLint texture)
{
	std::string textToDisplay;
	std::ostringstream ss;

	textToDisplay += "x: ";

	ss << position.x;

	textToDisplay += ss.str();

	textToDisplay += " y: ";

	ss << position.y;

	textToDisplay += ss.str();

	textToDisplay += " z: ";

	ss << position.z;

	textToDisplay += ss.str();

	textToDisplay += " roll: ";

	ss << position.z;

	textToDisplay += ss.str();

	const char *textToDisplayChar = textToDisplay.c_str();

	glLoadIdentity();
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2f(20, 20);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)textToDisplayChar);


	if (hudEnabled)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);

		glLoadIdentity();
		glColor3f(1.0, 1.0, 1.0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(0, 0);
		glTexCoord2f(0, 1); glVertex2f(0, windowHeight);
		glTexCoord2f(1, 1); glVertex2f(windowWidth, windowHeight);
		glTexCoord2f(1, 0); glVertex2f(windowWidth, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		glDisable(GL_BLEND);
	}
}

void Camera::hud()
{
	if (hudEnabled)
	{
		hudEnabled = false;
	}
	else
	{
		hudEnabled = true;
	}
}

void Camera::writeBitmapString(void *font, char *string)
{
	char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void Camera::updateCamera(glm::vec3 position, glm::vec3 forward, glm::vec3 up)
{
	this->position = position;
	this->forward = forward;
	this->up = up;
}

glm::vec3 Camera::getForwardVector()
{
	return glm::normalize(forward);
}

glm::vec3 Camera::getLeftVector()
{
	glm::vec3 leftVector = glm::cross(up, forward);
	return glm::normalize(leftVector);
}

glm::vec3 Camera::getRightVector()
{
	glm::vec3 rightVector = glm::cross(forward, up);
	return glm::normalize(rightVector);
}

Camera::~Camera()
{
}
