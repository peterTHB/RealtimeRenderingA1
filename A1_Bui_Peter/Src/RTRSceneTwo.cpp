#include "RTRSceneTwo.h"

RTRSceneTwo::RTRSceneTwo(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndColours, 
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

    amountOfVertices.push_back(8);
    amountOfFaces.push_back(6);

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

    modelMatrix = glm::mat4(1.0f);
}

void RTRSceneTwo::Init() {
    // Using shader
    sceneShader->Load("RTRShader.vert", "RTRShader.frag");
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

void RTRSceneTwo::DrawAll(Camera* camera) {
    DrawModern(camera);
}

void RTRSceneTwo::DrawModern(Camera* camera) {
    int currSubdivision = m_Subdivisions - 1;
         
    // VBO
    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, listOfVertexes.at(currSubdivision).at(0).size() * sizeof(GLfloat),
        listOfVertexes.at(currSubdivision).at(0).data(), GL_STATIC_DRAW);
   /* std::vector<GLfloat> allVertices;
    for (int i = 0; i < listOfVertexes.at(currSubdivision).size(); i++) {
        allVertices.insert(allVertices.end(), listOfVertexes.at(currSubdivision).at(i).begin(), 
            listOfVertexes.at(currSubdivision).at(i).end());
    }

    glBufferData(GL_ARRAY_BUFFER, allVertices.size() * sizeof(GLfloat), allVertices.data(), GL_STATIC_DRAW);*/

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesCopy.size() * sizeof(int), facesCopy.data(), GL_STATIC_DRAW);

    glUseProgram(*sceneShader->GetID());
    
    // Camera View and Proj
    camera->ModernCamera(m_WindowWidth, m_WindowHeight);

    glBindVertexArray(m_VertexArray);
    // Model
    geom->DrawAllModern(listOfVertexes.at(currSubdivision), facesCopy);

    glBindVertexArray(0);

    glDeleteVertexArrays(1, &m_VertexArray);
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteBuffers(1, &m_FaceElementBuffer);
    glDeleteBuffers(1, &m_InstancedVertexBuffer);
    m_VertexArray = 0;
    m_VertexBuffer = 0;
    m_FaceElementBuffer = 0;
    m_InstancedVertexBuffer = 0;
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
            std::vector<GLfloat> newPositions = cube->CalculateNewPositionsModern(currCube, currVector);
            newVertexPositions.push_back(newPositions);
        }

        listOfVertexes.push_back(newVertexPositions);
        
        //-------------------------------------------

         // Make buffer for cubes
        glGenBuffers(1, &m_InstancedVertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_InstancedVertexBuffer);
        std::vector<GLfloat> allNewPositions;
        for (int i = 0; i < newVertexPositions.size(); i++) {
            allNewPositions.insert(allNewPositions.end(), newVertexPositions.at(i).begin(), 
                newVertexPositions.at(i).end());
        }
        glBufferData(GL_ARRAY_BUFFER, newVertexPositions.size() * sizeof(GLfloat),
            &allNewPositions[0], GL_STREAM_DRAW);

        //enable vertex attribute 3 -> mat4
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);

        // tell OpenGL this is an instanced vertex attribute.
        glVertexAttribDivisor(2, 1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //------------------------------------------

        int totalFaces = 6 * newVertexPositions.size();
        int totalVertices = 8 * newVertexPositions.size();

        amountOfFaces.push_back(totalFaces);
        amountOfVertices.push_back(totalVertices);

        // calculate middle cube position
        cube->CalculateNewRadius();

        std::vector<GLfloat> storingNewMidVector = cube->CalculateNewPositionsModern(*cube, currVector);
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
