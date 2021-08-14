#include "RTRSceneFour.h"
#include "Geometry.h"

RTRSceneFour::RTRSceneFour(float windowWidth, float windowHeight)
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

void RTRSceneFour::Init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void RTRSceneFour::End() {

}

void RTRSceneFour::DrawAll() {
	Geometry* geom = new Geometry();

	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0.0);
	geom->DrawTriangle(0.6, 0.9, -0.2, 0.1, 0.5, 1.0);
	geom->DrawTriangle(-0.6, -0.9, -0.2, 0.1, 1.0, 0.5);

	geom->DrawTriangle(0.4, 0.6, 0.0, 0.0, 0.0, 1.0);
	geom->DrawTriangle(-0.4, -0.6, 0.0, 0.0, 1.0, 0.0);
	glPopMatrix();

	glUseProgram(0);
}

bool* RTRSceneFour::GetDepthBuffer()
{
	bool* state = &m_DepthState;
	return state;
}

bool* RTRSceneFour::GetBackface()
{
	bool* state = &m_BackfaceState;
	return state;
}

bool* RTRSceneFour::GetLighting()
{
	bool* state = &m_LightingState;
	return state;
}

void RTRSceneFour::ToggleDepthBuffer()
{
	m_DepthState = !m_DepthState;
}

void RTRSceneFour::ToggleBackface()
{
	m_BackfaceState = !m_BackfaceState;
}

void RTRSceneFour::ToggleLighting()
{
	m_LightingState = !m_LightingState;
}

int* RTRSceneFour::GetSubdivisions()
{
	int* number = &m_Subdivisions;
	return number;
}

int* RTRSceneFour::GetVertices()
{
	int* number = &m_Vertices;
	return number;
}

int* RTRSceneFour::GetFaces()
{
	int* number = &m_Faces;
	return number;
}

void RTRSceneFour::IncrementSubdivision()
{
	m_Subdivisions += 1;
}

void RTRSceneFour::DecrementSubdivision()
{
	m_Subdivisions -= 1;
}

void RTRSceneFour::IncrementVertices()
{
	m_Vertices += 1;
}

void RTRSceneFour::DecrementVertices()
{
	m_Vertices -= 1;
}

void RTRSceneFour::IncrementFaces()
{
	m_Faces += 1;
}

void RTRSceneFour::DecrementFaces()
{
	m_Faces -= 1;
}
