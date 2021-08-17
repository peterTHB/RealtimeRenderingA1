#include "RTRSceneThree.h"
#include "Geometry.h"

RTRSceneThree::RTRSceneThree(float windowWidth, float windowHeight)
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

void RTRSceneThree::Init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void RTRSceneThree::End() {

}

void RTRSceneThree::DrawAll() {
	Geometry* geom = new Geometry();

	glUseProgram(0);
}

bool* RTRSceneThree::GetDepthBuffer()
{
	bool* state = &m_DepthState;
	return state;
}

bool* RTRSceneThree::GetBackface()
{
	bool* state = &m_BackfaceState;
	return state;
}

bool* RTRSceneThree::GetLighting()
{
	bool* state = &m_LightingState;
	return state;
}

void RTRSceneThree::ToggleDepthBuffer()
{
	m_DepthState = !m_DepthState;
}

void RTRSceneThree::ToggleBackface()
{
	m_BackfaceState = !m_BackfaceState;
}

void RTRSceneThree::ToggleLighting()
{
	m_LightingState = !m_LightingState;
}

int* RTRSceneThree::GetSubdivisions()
{
	int* number = &m_Subdivisions;
	return number;
}

int* RTRSceneThree::GetVertices()
{
	int* number = &m_Vertices;
	return number;
}

int* RTRSceneThree::GetFaces()
{
	int* number = &m_Faces;
	return number;
}

void RTRSceneThree::IncrementSubdivision()
{
	m_Subdivisions += 1;
}

void RTRSceneThree::DecrementSubdivision()
{
	m_Subdivisions -= 1;
}

void RTRSceneThree::IncrementVertices()
{
	m_Vertices += 1;
}

void RTRSceneThree::DecrementVertices()
{
	m_Vertices -= 1;
}

void RTRSceneThree::IncrementFaces()
{
	m_Faces += 1;
}

void RTRSceneThree::DecrementFaces()
{
	m_Faces -= 1;
}