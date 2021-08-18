#include "RTRSceneSix.h"
#include "Geometry.h"

RTRSceneSix::RTRSceneSix(float windowWidth, float windowHeight, GLfloat vertexAndColours[], unsigned int faces[])
{
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
	m_DepthState = false;
	m_BackfaceState = false;
	m_LightingState = false;
	m_Subdivisions = 1;
	m_Vertices = 1;
	m_Faces = 1;

	geom = new Geometry();
	
	for (int i = 0; i < sizeof(verAndColCopy) / sizeof(verAndColCopy[0]); i++) {
		verAndColCopy[i] = vertexAndColours[i];
	}
	for (int j = 0; j < sizeof(facesCopy) / sizeof(facesCopy[0]); j++) {
		facesCopy[j] = faces[j];
	}
}

void RTRSceneSix::Init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void RTRSceneSix::End() {

}

void RTRSceneSix::DrawAll() {
	geom->DrawCubeWithPoints(verAndColCopy, facesCopy);
}

bool* RTRSceneSix::GetDepthBuffer()
{
	bool* state = &m_DepthState;
	return state;
}

bool* RTRSceneSix::GetBackface()
{
	bool* state = &m_BackfaceState;
	return state;
}

bool* RTRSceneSix::GetLighting()
{
	bool* state = &m_LightingState;
	return state;
}

void RTRSceneSix::ToggleDepthBuffer()
{
	m_DepthState = !m_DepthState;
}

void RTRSceneSix::ToggleBackface()
{
	m_BackfaceState = !m_BackfaceState;
}

void RTRSceneSix::ToggleLighting()
{
	m_LightingState = !m_LightingState;
}

int* RTRSceneSix::GetSubdivisions()
{
	int* number = &m_Subdivisions;
	return number;
}

int* RTRSceneSix::GetVertices()
{
	int* number = &m_Vertices;
	return number;
}

int* RTRSceneSix::GetFaces()
{
	int* number = &m_Faces;
	return number;
}

void RTRSceneSix::IncrementSubdivision()
{
	m_Subdivisions += 1;
}

void RTRSceneSix::DecrementSubdivision()
{
	m_Subdivisions -= 1;
}

void RTRSceneSix::IncrementVertices()
{
	m_Vertices += 1;
}

void RTRSceneSix::DecrementVertices()
{
	m_Vertices -= 1;
}

void RTRSceneSix::IncrementFaces()
{
	m_Faces += 1;
}

void RTRSceneSix::DecrementFaces()
{
	m_Faces -= 1;
}