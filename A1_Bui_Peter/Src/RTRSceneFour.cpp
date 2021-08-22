#include "RTRSceneFour.h"

RTRSceneFour::RTRSceneFour(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndColours, 
	std::vector<int> faces, Lighting* lighting, RTRShader* shader)
{
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
	m_DepthState = false;
	m_BackfaceState = false;
	m_LightingState = false;
	m_Subdivisions = 1;
	m_Vertices = 1;
	m_Faces = 1;

	amountOfVertices.push_back(8);
	amountOfFaces.push_back(6);

	geom = new Geometry;
	cube = new Cube(0.0f, 0.0f, 0.0f, 1.0f);
	Cubes.push_back(*cube);
	lighting = lighting;

	facesCopy = faces;
	std::vector<std::vector<GLfloat>> placeholder;
	placeholder.push_back(vertexAndColours);
	listOfVertexes.push_back(placeholder);
	listOfMidVertexes.push_back(vertexAndColours);

	sceneShader = shader;
	m_VertexArray = 0;
	m_VertexBuffer = 0;
	m_FaceElementBuffer = 0;
}

void RTRSceneFour::Init() {
	// Using shader
	sceneShader->Load("RTRShader.vert", "RTRShader.frag");
}

void RTRSceneFour::End() {
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

void RTRSceneFour::DrawAll() {
	
}

void RTRSceneFour::CreateCubes()
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

		int totalFaces = 6 * newVertexPositions.size();
		int totalVertices = 8 * newVertexPositions.size();

		amountOfFaces.push_back(totalFaces);
		amountOfVertices.push_back(totalVertices);

		// calculate middle cube position
		cube->CalculateNewRadius();

		std::vector<GLfloat> storingNewMidVector = cube->CalculateNewPositions(*cube, currVector);
		listOfMidVertexes.push_back(storingNewMidVector);
	}
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

