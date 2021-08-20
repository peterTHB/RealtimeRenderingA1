#include "RTRSceneOne.h"

RTRSceneOne::RTRSceneOne(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndColours, std::vector<int> faces)
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
	listOfMidVertexes.push_back(vertexAndColours);
}

void RTRSceneOne::Init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void RTRSceneOne::End() {
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

void RTRSceneOne::DrawAll() {
	int currSubdivision = m_Subdivisions - 1;
	geom->DrawCubeWithPoints(listOfVertexes.at(currSubdivision), facesCopy);
}

void RTRSceneOne::DrawCubes()
{
	int currCalSubdivision = m_Subdivisions - 1;

	if (listOfVertexes.size() == m_Subdivisions) {
		std::vector<Cube> newCube;

		for (Cube currCube : Cubes) {
			std::vector<Cube> createdCube = currCube.CalculateCube();
			newCube.insert(newCube.end(), createdCube.begin(), createdCube.end());
		}

		this->Cubes = newCube;

		std::vector<std::vector<GLfloat>> newVertexPositions;
		std::vector<GLfloat> currVector = listOfMidVertexes.at(currCalSubdivision);

		for (auto& currCube : Cubes) {
			std::vector<GLfloat> newPositions = cube->CalculateNewPositions(currCube, currVector);
			newVertexPositions.push_back(newPositions);
		}

		listOfVertexes.push_back(newVertexPositions);

		// calculate middle cube position
		cube->CalculateNewRadius();

		std::vector<GLfloat> storingNewMidVector = cube->CalculateNewPositions(*cube, currVector);
		listOfMidVertexes.push_back(storingNewMidVector);
	}
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

