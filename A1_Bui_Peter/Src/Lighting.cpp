#include "Lighting.h"

struct Materials
{
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Shininess;
};

Lighting::Lighting()
{
	ambientLighting = { 0.2f, 1.0f, 0.2f, 1.0f };
	diffuseLighting = { 0.2f, 0.2f, 1.0f, 1.0f };
	specularLighting = { 1.0f, 0.2f, 0.2f, 1.0f };
}

void Lighting::InstantiateImmediate() {
	GLfloat* ambientArray = &ambientLighting[0];
	GLfloat* diffuseArray = &diffuseLighting[0];
	GLfloat* specularArray = &specularLighting[0];
	GLfloat positionArrayOne[] = { 1.0f, 0.0f, 0.0f, 0.0f };
	GLfloat positionArrayTwo[] = { -1.0f, 0.0f, 0.0f, 0.0f };
	GLfloat positionArrayThree[] = { 0.0f, 0.0f, -1.0f, 0.0f };
	GLfloat positionArrayFour[] = { 0.0f, 0.0f, 1.0f, 0.0f };
	GLfloat positionArrayFive[] = { 0.0f, 1.0f, 0.0f, 0.0f };
	GLfloat positionArraySix[] = { 0.0f, -1.0f, 0.0f, 0.0f };
	GLfloat positionArraySeven[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glPushMatrix();
	glLoadIdentity();
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientArray);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseArray);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularArray);
	glLightfv(GL_LIGHT1, GL_POSITION, positionArrayOne);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, positionArrayOne);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientArray);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseArray);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularArray);
	glLightfv(GL_LIGHT2, GL_POSITION, positionArrayTwo);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, positionArrayTwo);

	glLightfv(GL_LIGHT3, GL_AMBIENT, ambientArray);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseArray);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specularArray);
	glLightfv(GL_LIGHT3, GL_POSITION, positionArrayThree);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, positionArrayThree);

	glLightfv(GL_LIGHT4, GL_AMBIENT, ambientArray);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuseArray);
	glLightfv(GL_LIGHT4, GL_SPECULAR, specularArray);
	glLightfv(GL_LIGHT4, GL_POSITION, positionArrayFour);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, positionArrayFour);

	glLightfv(GL_LIGHT5, GL_AMBIENT, ambientArray);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuseArray);
	glLightfv(GL_LIGHT5, GL_SPECULAR, specularArray);
	glLightfv(GL_LIGHT5, GL_POSITION, positionArrayFive);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, positionArrayFive);

	glLightfv(GL_LIGHT6, GL_AMBIENT, ambientArray);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuseArray);
	glLightfv(GL_LIGHT6, GL_SPECULAR, specularArray);
	glLightfv(GL_LIGHT6, GL_POSITION, positionArraySix);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, positionArraySix);

	glLightfv(GL_LIGHT7, GL_AMBIENT, ambientArray);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuseArray);
	glLightfv(GL_LIGHT7, GL_SPECULAR, specularArray);
	glLightfv(GL_LIGHT7, GL_POSITION, positionArraySeven);
	glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, positionArraySeven);
	glPopMatrix();
}

void Lighting::ImmediateLighting(glm::vec3 cameraPos)
{
	GLfloat ambientArrayLight[] = { 0.2f, 1.0f, 0.2f, 1.0f };
	GLfloat diffuseArrayLight[] = { 0.2f, 0.2f, 1.0f, 1.0f };
	GLfloat specularArrayLight[] = { 1.0f, 0.2f, 0.2f, 1.0f };
	GLfloat positionArrayLight[] = { -1.0f * cameraPos.x, -1.0f * cameraPos.y, -1.0f * cameraPos.z, 0.0f };
	GLfloat positionDirecArrayLight[] = { -1.0f * cameraPos.x, -1.0f * cameraPos.y, -1.0f * cameraPos.z};

	glPushMatrix();
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientArrayLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseArrayLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularArrayLight);
	glLightfv(GL_LIGHT0, GL_POSITION, positionArrayLight);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, positionDirecArrayLight);
	glPopMatrix();
}

void Lighting::ImmediateSpotLighting(int amountOfLights) 
{
	InstantiateImmediate();

	if (amountOfLights > 0 ) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
	if (amountOfLights > 1) {
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT1);
	}
	if (amountOfLights > 2) {
		glEnable(GL_LIGHT2);
	}
	else {
		glDisable(GL_LIGHT2);
	}
	if (amountOfLights > 3) {
		glEnable(GL_LIGHT3);
	}
	else {
		glDisable(GL_LIGHT3);
	}
	if (amountOfLights > 4) {
		glEnable(GL_LIGHT4);
	}
	else {
		glDisable(GL_LIGHT4);
	}
	if (amountOfLights > 5) {
		glEnable(GL_LIGHT5);
	}
	else {
		glDisable(GL_LIGHT5);
	}
	if (amountOfLights > 6) {
		glEnable(GL_LIGHT6);
	}
	else {
		glDisable(GL_LIGHT6);
	}
	if (amountOfLights > 7) {
		glEnable(GL_LIGHT7);
	}
	else {
		glDisable(GL_LIGHT7);
	}
}

void Lighting::InstantiateModern()
{

}

void Lighting::ModernLighting(glm::vec3 cameraPos)
{
	
}

void Lighting::ModernSpotLighting(int amountOfLights)
{
	InstantiateModern();
}

void Lighting::ImmediateMaterial()
{
}

void Lighting::ModernMaterial()
{
}
