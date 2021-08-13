#include "RTRSceneTwo.h"
#include "Geometry.h"

RTRSceneTwo::RTRSceneTwo(float windowWidth, float windowHeight)
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

void RTRSceneTwo::Init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void RTRSceneTwo::End() {

}

void RTRSceneTwo::DrawAll() {
	Geometry* geom = new Geometry();

	glPushMatrix();
	glTranslatef(0.2, 0.0, 0.0);
	geom->DrawTriangle(0.6, 0.9, -0.2, 0.1, 0.5, 1.0);
	geom->DrawTriangle(-0.6, -0.9, -0.2, 0.1, 1.0, 0.5);

	geom->DrawTriangle(0.4, 0.6, 0.0, 0.0, 0.0, 1.0);
	geom->DrawTriangle(-0.4, -0.6, 0.0, 0.0, 1.0, 0.0);
	glPopMatrix();

	glUseProgram(0);
}

bool* RTRSceneTwo::GetDepthBuffer()
{
	bool* state = &m_DepthState;
	return state;
}

bool* RTRSceneTwo::GetBackface()
{
	bool* state = &m_BackfaceState;
	return state;
}

bool* RTRSceneTwo::GetLighting()
{
	bool* state = &m_LightingState;
	return state;
}

void RTRSceneTwo::ToggleDepthBuffer()
{
	m_DepthState = !m_DepthState;
}

void RTRSceneTwo::ToggleBackface()
{
	m_BackfaceState = !m_BackfaceState;
}

void RTRSceneTwo::ToggleLighting()
{
	m_LightingState = !m_LightingState;
}

int* RTRSceneTwo::GetSubdivisions()
{
	int* number = &m_Subdivisions;
	return number;
}

int* RTRSceneTwo::GetVertices()
{
	int* number = &m_Vertices;
	return number;
}

int* RTRSceneTwo::GetFaces()
{
	int* number = &m_Faces;
	return number;
}

void RTRSceneTwo::IncrementSubdivision()
{
	m_Subdivisions += 1;
}

void RTRSceneTwo::DecrementSubdivision()
{
	m_Subdivisions -= 1;
}

void RTRSceneTwo::IncrementVertices()
{
	m_Vertices += 1;
}

void RTRSceneTwo::DecrementVertices()
{
	m_Vertices -= 1;
}

void RTRSceneTwo::IncrementFaces()
{
	m_Faces += 1;
}

void RTRSceneTwo::DecrementFaces()
{
	m_Faces -= 1;
}
