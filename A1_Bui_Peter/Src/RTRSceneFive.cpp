#include "RTRSceneFive.h"
#include "Geometry.h"

RTRSceneFive::RTRSceneFive(float windowWidth, float windowHeight, GLfloat vertexAndColours[], unsigned int faces[])
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

void RTRSceneFive::Init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void RTRSceneFive::End() {

}

void RTRSceneFive::DrawAll() {
	geom->DrawCubeWithPoints(verAndColCopy, facesCopy);
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