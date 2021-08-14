#include "RTRSceneOne.h"
#include "Geometry.h"

RTRSceneOne::RTRSceneOne(float windowWidth, float windowHeight)
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

void RTRSceneOne::Init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void RTRSceneOne::End() {

}

void RTRSceneOne::DrawAll() {
	Geometry* geom = new Geometry();

	geom->DrawAllImmediate();

	glUseProgram(0);
}

bool* RTRSceneOne::GetDepthBuffer()
{
	bool* state = &m_DepthState;
	return state;
}

bool* RTRSceneOne::GetBackface()
{
	bool* state = &m_BackfaceState;
	return state;
}

bool* RTRSceneOne::GetLighting()
{
	bool* state = &m_LightingState;
	return state;
}

void RTRSceneOne::ToggleDepthBuffer()
{
	m_DepthState = !m_DepthState;
}

void RTRSceneOne::ToggleBackface()
{
	m_BackfaceState = !m_BackfaceState;
}

void RTRSceneOne::ToggleLighting()
{
	m_LightingState = !m_LightingState;
}

int* RTRSceneOne::GetSubdivisions()
{
	int* number = &m_Subdivisions;
	return number;
}

int* RTRSceneOne::GetVertices()
{
	int* number = &m_Vertices;
	return number;
}

int* RTRSceneOne::GetFaces()
{
	int* number = &m_Faces;
	return number;
}

void RTRSceneOne::IncrementSubdivision()
{
	m_Subdivisions += 1;
}

void RTRSceneOne::DecrementSubdivision()
{
	m_Subdivisions -= 1;
}

void RTRSceneOne::IncrementVertices()
{
	m_Vertices += 1;
}

void RTRSceneOne::DecrementVertices()
{
	m_Vertices -= 1;
}

void RTRSceneOne::IncrementFaces()
{
	m_Faces += 1;
}

void RTRSceneOne::DecrementFaces()
{
	m_Faces -= 1;
}

