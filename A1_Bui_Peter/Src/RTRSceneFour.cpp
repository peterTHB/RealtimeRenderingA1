#include "RTRSceneFour.h"

#define NUM_INSTANCES 9

RTRSceneFour::RTRSceneFour(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndNormals,
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
	sceneLighting = lighting;

	facesCopy = faces;
	std::vector<std::vector<GLfloat>> placeholder;
	std::vector<GLfloat> newVertexPositions =
		cube->CalculateNewVertexPositions(*cube, vertexAndNormals, facesCopy);
	placeholder.push_back(newVertexPositions);
	listOfVertexes.push_back(placeholder);
	listOfMidVertexes.push_back(newVertexPositions);

	pointLightPositions = {
		glm::vec3(2.0f, 0.0f, 2.0f),
		glm::vec3(-2.0f, 0.0f, -2.0f),
		glm::vec3(0.0f, 2.0f, 2.0f),
		glm::vec3(0.0f, -2.0f, -2.0f),
		glm::vec3(0.0f, -2.0f, 2.0f),
		glm::vec3(0.0f, 2.0f, -2.0f),
		glm::vec3(3.0f, 3.0f, 3.0f),
		glm::vec3(-3.0f, 3.0f, -3.0f)
	};

	pointLightMaterial = {
		// Ambient
		glm::vec3(0.3f, 0.3f, 0.3f),
		// Diffuse
		glm::vec3(0.9f, 0.9f, 0.9f),
		//Specular
		glm::vec3(1.0f, 1.0f, 1.0f),
	};

	m_VertexArray = 0;
	m_VertexBuffer = 0;
	m_FaceElementBuffer = 0;
	m_InstancedArrayVBO = 0;
	pointLightPositions.clear();
	pointLightMaterial.clear();
	cubePositionsInWorld.clear();
}

void RTRSceneFour::Init() {
	// Using shader
	sceneShader->Load("RTRShader.vert", "RTRShader.frag");
}

void RTRSceneFour::End() {
	geom = nullptr;
	cube = nullptr;
	sceneShader = nullptr;
	sceneLighting = nullptr;
	facesCopy.clear();

	for (auto tier1 : listOfVertexes) {
		for (auto tier2 : tier1) {
			tier2.clear();
		}
	}
	listOfVertexes.clear();
}

void RTRSceneFour::DrawAll(Camera* camera) {
	DrawModern(camera);
	int currSubdivision = m_Subdivisions - 1;
	m_VertexData = listOfVertexes.at(currSubdivision).size() *
		listOfVertexes.at(currSubdivision).at(0).size() * sizeof(GLfloat);
}

void RTRSceneFour::DrawModern(Camera* camera)
{
	int currSubdivision = m_Subdivisions - 1;
	std::vector<glm::mat4> m_InstanceModelMatrices = geom->SetMultiCubeTransforms();

	glGenVertexArrays(1, &m_VertexArray);
	glGenBuffers(1, &m_VertexBuffer);
	glBindVertexArray(m_VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	std::vector<GLfloat> allVertices;
	for (int i = 0; i < listOfVertexes.at(currSubdivision).size(); i++) {
		allVertices.insert(allVertices.end(), listOfVertexes.at(currSubdivision).at(i).begin(),
			listOfVertexes.at(currSubdivision).at(i).end());
	}
	glBufferData(GL_ARRAY_BUFFER, allVertices.size() * sizeof(GLfloat), allVertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	// Instanced VBO
	glGenBuffers(1, &m_InstancedArrayVBO);
	InstanceVBO(m_InstanceModelMatrices);

	glUseProgram(*sceneShader->GetID());

	if (m_LightingState) {
		sceneShader->SetBool("LightOn", true);
	}
	else {
		sceneShader->SetBool("LightOn", false);
	}

	this->sceneLighting->ModernLighting(sceneShader, m_NumLights - 1, *camera->GetCameraFront(), 
		*camera->GetCameraPos(), pointLightPositions, pointLightMaterial);

	// Camera View and Proj
	camera->ModernCamera(m_WindowWidth, m_WindowHeight);

	// Scene specific
	sceneShader->SetInt("sceneState", 1);

	glBindVertexArray(m_VertexArray);
	// Model
	geom->DrawCubeArrayInstanced(allVertices.size());

	glBindVertexArray(0);

	glDeleteVertexArrays(1, &m_VertexArray);
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_InstancedArrayVBO);
	m_VertexArray = 0;
	m_VertexBuffer = 0;
	m_InstancedArrayVBO = 0;
}

void RTRSceneFour::InstanceVBO(std::vector<glm::mat4> instanceModelMatrix) {
	int matrixLocation = glGetAttribLocation(*sceneShader->GetID(), "aInstanceModelMatrix");

	glBindBuffer(GL_ARRAY_BUFFER, m_InstancedArrayVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * NUM_INSTANCES, instanceModelMatrix.data(), GL_STATIC_DRAW);

	for (unsigned int i = 0; i < 4; i++) {
		int currIndex = matrixLocation + i;
		glEnableVertexAttribArray(currIndex);
		glVertexAttribPointer(currIndex, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(GLfloat) * i * 4));
		glVertexAttribDivisor(currIndex, 1);
	}
};

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

