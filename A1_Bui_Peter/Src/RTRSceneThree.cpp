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
	m_NumLights = 0;
	m_VertexData = 0.0f;

	amountOfVertices.push_back(m_Vertices);
	amountOfFaces.push_back(m_Faces);

	sceneShader = shader;
	sceneLighting = lighting;

	geom = new Geometry(sceneShader);
	cube = new Cube(0.0f, 0.0f, 0.0f, 1.0f);
	std::vector<Cube> cubePlaceholder;
	cubePlaceholder.push_back(*cube);
	listOfCubes.push_back(cubePlaceholder);

	std::vector<std::vector<GLfloat>> placeholder;
	placeholder.push_back(vertexAndNormals);
	listOfVertexes.push_back(placeholder);
	listOfMidVertexes.push_back(vertexAndNormals);
	listOfFaces.push_back(cube->ExtraCubeFaces(faces));

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

	cubePositionsInWorld = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 0.0f, 0.0f),
		glm::vec3(-2.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 2.0f, 0.0f),
		glm::vec3(0.0f, -2.0f, 0.0f),
		glm::vec3(2.0f, 2.0f, 0.0f),
		glm::vec3(-2.0f, 2.0f, 0.0f),
		glm::vec3(2.0f, -2.0f, 0.0f),
		glm::vec3(-2.0f, -2.0f, 0.0f)
	};

	m_VertexArray = 0;
	m_VertexBuffer = 0;
	m_FaceElementBuffer = 0;
}

void RTRSceneThree::Init() {
	// Using shader
	sceneShader->Load("RTRShader.vert", "RTRShader.frag");
}

void RTRSceneThree::End() {
	geom = nullptr;
	cube = nullptr;
	sceneShader = nullptr;
	sceneLighting = nullptr;
	
	for (auto tier1 : listOfVertexes) {
		for (auto tier2 : tier1) {
			tier2.clear();
		}
	}
	listOfVertexes.clear();
	pointLightPositions.clear();
	pointLightMaterial.clear();
	cubePositionsInWorld.clear();
	for (auto tier1 : listOfFaces) {
		tier1.clear();
	}
	listOfFaces.clear();
}

void RTRSceneThree::DrawAll(Camera* camera) {
	DrawModern(camera);
	m_VertexData = listOfVertexes.at(0).size() *
		listOfVertexes.at(0).at(0).size() * sizeof(GLfloat);
}

void RTRSceneThree::DrawModern(Camera* camera) {
	int currSubdivision = m_Subdivisions - 1;

	// VBO
	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, listOfVertexes.at(0).at(0).size() * sizeof(GLfloat), 
		listOfVertexes.at(0).at(0).data(), GL_STATIC_DRAW);

	// VAO
	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// EBO
	glGenBuffers(1, &m_FaceElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_FaceElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, listOfFaces.at(0).size() * sizeof(int), 
		listOfFaces.at(0).data(), GL_STATIC_DRAW);

	glUseProgram(*sceneShader->GetID());

	if (m_LightingState) {
		sceneShader->SetBool("LightOn", true);
	}
	else {
		sceneShader->SetBool("LightOn", false);
	}

	this->sceneLighting->ModernLighting(sceneShader, m_NumLights, *camera->GetCameraFront(), 
		*camera->GetCameraPos(), pointLightPositions, pointLightMaterial);

	// Camera View and Proj
	camera->ModernCamera(m_WindowWidth, m_WindowHeight);

	// Scene specific
	sceneShader->SetInt("sceneState", 0);
	
	glBindVertexArray(m_VertexArray);

	// Model
	geom->DrawMultipleCubes(currSubdivision, listOfCubes.at(currSubdivision), cubePositionsInWorld);

	glBindVertexArray(0);

	glDeleteVertexArrays(1, &m_VertexArray);
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_FaceElementBuffer);
	m_VertexArray = 0;
	m_VertexBuffer = 0;
	m_FaceElementBuffer = 0;
}

void RTRSceneThree::CreateCubes()
{
	int currCalSubdivision = m_Subdivisions - 1;

	if (listOfVertexes.size() == m_Subdivisions) {
		std::vector<Cube> newCube;

		for (Cube currCube : listOfCubes.at(currCalSubdivision)) {
			std::vector<Cube> createdCube = currCube.CalculateCube();
			newCube.insert(newCube.end(), createdCube.begin(), createdCube.end());
		}

		listOfCubes.push_back(newCube);

		int totalFaces = m_Faces * pow(20, m_Subdivisions);
		int totalVertices = m_Vertices * pow(20, m_Subdivisions);

		amountOfFaces.push_back(totalFaces);
		amountOfVertices.push_back(totalVertices);

		// Code underneath shouldn't be required, but removing it causes something to crash
		// So it is kept to ensure nothing crashes
		// ----------------------------------------------------------------------------
		std::vector<std::vector<GLfloat>> newVertexPositions;
		std::vector<GLfloat> currVector = listOfMidVertexes.at(currCalSubdivision);

		for (auto& currCube : listOfCubes.at(currCalSubdivision)) {
			std::vector<GLfloat> newPositions = cube->CalculateNewPositionsModern(currCube, currVector);
			newVertexPositions.push_back(newPositions);
		}

		listOfVertexes.push_back(newVertexPositions);

		// Calculate middle cube position
		cube->CalculateNewRadius();

		std::vector<GLfloat> storingNewMidVector = cube->CalculateNewPositionsModern(*cube, currVector);
		listOfMidVertexes.push_back(storingNewMidVector);

		// Calculate new vertex indices based on size of total cubes
		std::vector<int> tempFaces = cube->AddExtraCubeFaces(listOfFaces.at(0), 
			listOfVertexes.at(m_Subdivisions).size());
		listOfFaces.push_back(tempFaces);
		// ----------------------------------------------------------------------------
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
