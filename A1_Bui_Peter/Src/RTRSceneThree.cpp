#include "RTRSceneThree.h"

RTRSceneThree::RTRSceneThree(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndNormals,
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
		cube->CalculateNewVertexPositions(*cube, vertexAndNormals, facesCopy);
	placeholder.push_back(newVertexPositions);
	listOfVertexes.push_back(placeholder);
	listOfMidVertexes.push_back(newVertexPositions);

	m_VertexArray = 0;
	m_VertexBuffer = 0;
	m_FaceElementBuffer = 0;
	m_InstancedVertexBuffer = 0;
}

void RTRSceneThree::Init() {
	// Using shader
	sceneShader->Load("RTRShader.vert", "RTRShader.frag");
}

void RTRSceneThree::End() {
	geom = nullptr;
	cube = nullptr;
	facesCopy.clear();

	Cubes.clear();
	
	for (auto tier1 : listOfVertexes) {
		for (auto tier2 : tier1) {
			tier2.clear();
		}
	}
	listOfVertexes.clear();
}

void RTRSceneThree::DrawAll(Camera* camera) {
	
}

void RTRSceneThree::DrawModern(Camera* camera) {
	/*glDeleteVertexArrays(1, &m_VertexArray);
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_FaceElementBuffer);
	glDeleteBuffers(1, &m_InstancedVertexBuffer);
	m_VertexArray = 0;
	m_VertexBuffer = 0;
	m_FaceElementBuffer = 0;
	m_InstancedVertexBuffer = 0;*/
}

void RTRSceneThree::CreateCubes()
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

		//-------------------------------------------

		//// Make buffer for cubes
		//glGenBuffers(1, &m_InstancedVertexBuffer);
		//glBindBuffer(GL_ARRAY_BUFFER, m_InstancedVertexBuffer);
		//std::vector<GLfloat> allNewPositions;
		//for (int i = 0; i < newVertexPositions.size(); i++) {
		//    allNewPositions.insert(allNewPositions.end(), newVertexPositions.at(i).begin(),
		//        newVertexPositions.at(i).end());
		//}
		//glBufferData(GL_ARRAY_BUFFER, newVertexPositions.size() * sizeof(GLfloat),
		//    &allNewPositions[0], GL_STREAM_DRAW);

		////enable vertex attribute 3 -> mat4
		//glEnableVertexAttribArray(2);
		//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);

		//// tell OpenGL this is an instanced vertex attribute.
		//glVertexAttribDivisor(2, 1);

		///*glBindBuffer(GL_ARRAY_BUFFER, 0);*/

		//------------------------------------------
	}
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

int* RTRSceneThree::GetNumLights()
{
	int* number = &m_NumLights;
	return number;
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
	int currSubdivision = m_Subdivisions - 1;
	int* number = &amountOfVertices.at(currSubdivision);
	return number;
}

int* RTRSceneThree::GetFaces()
{
	int currSubdivision = m_Subdivisions - 1;
	int* number = &amountOfFaces.at(currSubdivision);
	return number;
}

float* RTRSceneThree::GetVertexData()
{
	float* number = &m_VertexData;
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

void RTRSceneThree::IncrementLights()
{
	m_NumLights += 1;
}

void RTRSceneThree::DecrementLights()
{
	m_NumLights -= 1;
}
