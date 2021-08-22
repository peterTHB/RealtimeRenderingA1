#include "RTRSceneTwo.h"

RTRSceneTwo::RTRSceneTwo(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndColours, 
	std::vector<int> faces, Lighting* lighting)
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

    // Instantiate shader
    SceneShader = new RTRShader();

    m_VertexArray = 0;
    m_VertexBuffer = 0;
    m_FaceElementBuffer = 0;
    m_SquareProgram = 0;
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

    glDeleteVertexArrays(1, &m_VertexArray);
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteBuffers(1, &m_FaceElementBuffer);
    glDeleteProgram(m_SquareProgram);
    m_VertexArray = 0;
    m_VertexBuffer = 0;
    m_FaceElementBuffer = 0;
    m_SquareProgram = 0;
}

void RTRSceneTwo::DrawAll() {
    DrawModern();
}

void RTRSceneTwo::DrawModern() {
    // Use shader here
    SceneShader->Load("RTRShader.vert", "RTRShader.frag");

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, listOfVertexes.at(0).at(0).size() * sizeof(GLfloat),
        listOfVertexes.at(0).at(0).data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &m_FaceElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_FaceElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesCopy.size() * sizeof(int), facesCopy.data(), GL_STATIC_DRAW);

    glUseProgram(*SceneShader->GetID());
    glBindVertexArray(m_VertexArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void RTRSceneTwo::CreateCubes()
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
