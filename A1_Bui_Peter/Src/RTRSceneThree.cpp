#include "RTRSceneThree.h"

RTRSceneThree::RTRSceneThree(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndColours, std::vector<int> faces)
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

void RTRSceneThree::Init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void RTRSceneThree::End() {
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

void RTRSceneThree::DrawAll() {
	
}

void RTRSceneThree::DrawCubes()
{
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