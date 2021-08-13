#include "Geometry.h"

Geometry::Geometry() {

}

void Geometry::DrawAllImmediate() {
	glPushMatrix();
	//// Back
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	DrawTriangle(0.5, 0.5, 0.5, 0.0, 0.0, 1.0);
	DrawTriangle(-0.5, -0.5, 0.5, 0.0, 1.0, 0.0);
	glPopMatrix();


	//// Left Side
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	DrawTriangle(0.5, 0.5, 0.5, 0.0, 0.0, 1.0);
	DrawTriangle(-0.5, -0.5, 0.5, 0.0, 1.0, 0.0);
	glPopMatrix();


	//// Right Side
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	DrawTriangle(0.5, 0.5, 0.5, 0.0, 0.0, 1.0);
	DrawTriangle(-0.5, -0.5, 0.5, 0.0, 1.0, 0.0);
	glPopMatrix();

	// Front
	DrawTriangle(0.5, 0.5, 0.5, 0.0, 0.0, 1.0);
	DrawTriangle(-0.5, -0.5, 0.5, 0.0, 1.0, 0.0);

	//// Top
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	DrawTriangle(0.5, 0.5, 0.5, 0.0, 0.0, 1.0);
	DrawTriangle(-0.5, -0.5, 0.5, 0.0, 1.0, 0.0);
	glPopMatrix();

	//// Bottom
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	DrawTriangle(0.5, 0.5, 0.5, 0.0, 0.0, 1.0);
	DrawTriangle(-0.5, -0.5, 0.5, 0.0, 1.0, 0.0);
	glPopMatrix();

	glPopMatrix();
	glUseProgram(0);
}

void Geometry::DrawTriangle(float x, float y, float z, float r, float g, float b) {
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
	glVertex3f(-1 * x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(-1 * x, -1 * y, z);
	glEnd();
}