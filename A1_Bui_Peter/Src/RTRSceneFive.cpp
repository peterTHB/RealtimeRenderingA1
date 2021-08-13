#include "RTRSceneFive.h"
#include "Geometry.h"

RTRSceneFive::RTRSceneFive(float windowWidth, float windowHeight)
{
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
	m_DepthState = false;
	m_BackfaceState = false;
	m_LightingState = false;
	m_Subdivisions = 1;
	m_Vertices = 1;
	m_Faces = 1;
}

void RTRSceneFive::Init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void RTRSceneFive::End() {

}

void RTRSceneFive::DrawAll() {
	Geometry* geom = new Geometry();

	glPushMatrix();
	glTranslatef(0.0, 0.5, 0.0);
	geom->DrawTriangle(0.6, 0.9, -0.2, 0.1, 0.5, 1.0);
	geom->DrawTriangle(-0.6, -0.9, -0.2, 0.1, 1.0, 0.5);

	geom->DrawTriangle(0.4, 0.6, 0.0, 0.0, 0.0, 1.0);
	geom->DrawTriangle(-0.4, -0.6, 0.0, 0.0, 1.0, 0.0);
	glPopMatrix();

	glUseProgram(0);
}

bool* RTRSceneFive::GetDepthBuffer()
{
	bool* state = &m_DepthState;
	return state;
}

bool* RTRSceneFive::GetBackface()
{
	bool* state = &m_BackfaceState;
	return state;
}

bool* RTRSceneFive::GetLighting()
{
	bool* state = &m_LightingState;
	return state;
}

void RTRSceneFive::ToggleDepthBuffer()
{
	m_DepthState = !m_DepthState;
}

void RTRSceneFive::ToggleBackface()
{
	m_BackfaceState = !m_BackfaceState;
}

void RTRSceneFive::ToggleLighting()
{
	m_LightingState = !m_LightingState;
}

int* RTRSceneFive::GetSubdivisions()
{
	int* number = &m_Subdivisions;
	return number;
}

int* RTRSceneFive::GetVertices()
{
	int* number = &m_Vertices;
	return number;
}

int* RTRSceneFive::GetFaces()
{
	int* number = &m_Faces;
	return number;
}

void RTRSceneFive::IncrementSubdivision()
{
	m_Subdivisions += 1;
}

void RTRSceneFive::DecrementSubdivision()
{
	m_Subdivisions -= 1;
}

void RTRSceneFive::IncrementVertices()
{
	m_Vertices += 1;
}

void RTRSceneFive::DecrementVertices()
{
	m_Vertices -= 1;
}

void RTRSceneFive::IncrementFaces()
{
	m_Faces += 1;
}

void RTRSceneFive::DecrementFaces()
{
	m_Faces -= 1;
}