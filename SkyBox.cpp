#include "SkyBox.h"



SkyBox::SkyBox()
{
}

void SkyBox::drawSkyBox(GLint texture)
{
	glPushMatrix();

	glColor3f(0.8, 0.8, 0.8);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glScalef(1.0f, -1.0f, 1.0f);
	gltDrawSphere(6000.0f, 50, 50);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

SkyBox::~SkyBox()
{
}
