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
	m_Vertices = 8;
	m_Faces = 6;
	m_NumLights = 1;
	m_VertexData = 0.0f;

	amountOfVertices.push_back(m_Vertices);
	amountOfFaces.push_back(m_Faces);

	sceneShader = shader;
	geom = new Geometry(sceneShader);
	cube = new Cube(0.0f, 0.0f, 0.0f, 1.0f);
	Cubes.push_back(*cube);
	lighting = lighting;

	facesCopy = faces;
	std::vector<std::vector<GLfloat>> placeholder;
	std::vector<GLfloat> newVertexPositions =
		cube->CalculateNewVertexPositions(*cube, vertexAndColours, facesCopy);
	placeholder.push_back(newVertexPositions);
	listOfVertexes.push_back(placeholder);
	listOfMidVertexes.push_back(newVertexPositions);

	m_VertexArray = 0;
	m_VertexBuffer = 0;
	m_FaceElementBuffer = 0;
	m_InstancedVertexBuffer = 0;
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

void RTRSceneFour::DrawAll(Camera* camera) {
	
}

void RTRSceneFour::DrawModern(Camera* camera)
{
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
			std::vector<GLfloat> newPositions = cube->CalculateNewPositionsModern(currCube, currVector);
			newVertexPositions.push_back(newPositions);
		}

		listOfVertexes.push_back(newVertexPositions);

		int totalFaces = m_Faces * newVertexPositions.size();
		int totalVertices = m_Vertices * newVertexPositions.size();

		amountOfFaces.push_back(totalFaces);
		amountOfVertices.push_back(totalVertices);

		// calculate middle cube position
		cube->CalculateNewRadius();

		std::vector<GLfloat> storingNewMidVector = cube->CalculateNewPositionsModern(*cube, currVector);
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

int* RTRSceneFour::GetNumLights()
{
	int* number = &m_NumLights;
	return number;
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
	int currSubdivision = m_Subdivisions - 1;
	int* number = &amountOfVertices.at(currSubdivision);
	return number;
}

int* RTRSceneFour::GetFaces()
{
	int currSubdivision = m_Subdivisions - 1;
	int* number = &amountOfFaces.at(currSubdivision);
	return number;
}

float* RTRSceneFour::GetVertexData()
{
	float* number = &m_VertexData;
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

void RTRSceneFour::IncrementLights()
{
	m_NumLights += 1;
}

void RTRSceneFour::DecrementLights()
{
	m_NumLights -= 1;
}

