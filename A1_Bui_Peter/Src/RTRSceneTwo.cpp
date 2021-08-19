#include "RTRSceneTwo.h"

RTRSceneTwo::RTRSceneTwo(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndColours, std::vector<int> faces)
{
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
	m_DepthState = false;
	m_BackfaceState = false;
	m_LightingState = false;
	m_Subdivisions = 1;
	m_Vertices = 1;
	m_Faces = 1;

	geom = new Geometry;
	cube = new Cube(0.0f, 0.0f, 0.0f, 1.0f);
	Cubes.push_back(*cube);

	facesCopy = faces;
	std::vector<std::vector<GLfloat>> placeholder;
	placeholder.push_back(vertexAndColours);
	listOfVertexes.push_back(placeholder);
}

void RTRSceneTwo::Init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void RTRSceneTwo::End() {
	geom = nullptr;
	cube = nullptr;
	facesCopy.clear();
	
	for (auto tier1 : listOfVertexes) {
		for (auto tier2 : tier1) {
			tier2.clear();
		}
	}
	listOfVertexes.clear();
}

void RTRSceneTwo::DrawAll() {
	
}

void RTRSceneTwo::DrawCubes()
{
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
