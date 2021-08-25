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
    m_NumLights = 1;
    m_VertexData = 0.0f;

    amountOfVertices.push_back(m_Vertices);
    amountOfFaces.push_back(m_Faces);

    sceneShader = shader;
    lightShader = new RTRShaderLight();
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
}

void RTRSceneTwo::Init() {
    // Using shader
    sceneShader->Load("RTRShader.vert", "RTRShader.frag");
    lightShader->Load("RTRShaderLight.vert", "RTRShaderLight.frag");
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
    glm::vec3 lightPos(1.0f, 0.0f, 0.0f);
         
    // VBO
    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    std::vector<GLfloat> allVertices;
    for (int i = 0; i < listOfVertexes.at(currSubdivision).size(); i++) {
        allVertices.insert(allVertices.end(), listOfVertexes.at(currSubdivision).at(i).begin(), 
            listOfVertexes.at(currSubdivision).at(i).end());
    }
    glBufferData(GL_ARRAY_BUFFER, allVertices.size() * sizeof(GLfloat), allVertices.data(), GL_STATIC_DRAW);

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
    sceneShader->SetInt("material.diffuse", 0);
    sceneShader->SetInt("material.specular", 1);
    
    /*sceneShader->SetVec3("light.position", lightPos);*/
    sceneShader->SetVec3("light.position", *camera->GetCameraPos());
    sceneShader->SetVec3("light.direction", *camera->GetCameraFront());
    sceneShader->SetFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
    sceneShader->SetVec3("viewPos", *camera->GetCameraPos());
    /*sceneShader->SetVec3("viewPos", lightPos);*/

    // Colors
    glm::vec3 lightColor;
    lightColor.x = 0.8f;
    lightColor.y = 0.8f;
    lightColor.z = 0.8f;
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
    sceneShader->SetVec3("material.ambient", ambientColor);
    sceneShader->SetVec3("material.diffuse", diffuseColor);
    sceneShader->SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
    sceneShader->SetFloat("material.shininess", 32.0f);

    sceneShader->SetVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    sceneShader->SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    sceneShader->SetVec3("light.specular", 1.0f, 1.0f, 1.0f);

    sceneShader->SetFloat("light.constant", 1.0f);
    sceneShader->SetFloat("light.linear", 0.09f);
    sceneShader->SetFloat("light.quadratic", 0.032f);

    // Camera View and Proj
    camera->ModernCamera(m_WindowWidth, m_WindowHeight);

    glBindVertexArray(m_VertexArray);
    // Model
    geom->DrawAllModern(listOfVertexes.at(currSubdivision), facesCopy, allVertices.size());

    /*glBindVertexArray(0);*/

    unsigned int lightVAO;

    // Lighting
    /*lighting->ModernLighting(m_NumLights, m_VertexBuffer);*/
    //glGenVertexArrays(1, &lightVAO);
    //glBindVertexArray(lightVAO);
    //glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    //glEnableVertexAttribArray(1);

    //LightCube
    /*glUseProgram(*lightShader->GetID());
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
    lightShader->SetMat4("projection", projection);
    glm::mat4 view = glm::lookAt(*camera->GetCameraPos(), *camera->GetCameraPos() + *camera->GetCameraFront(), *camera->GetCameraUp());
    lightShader->SetMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.3f));
    lightShader->SetMat4("model", model);
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);*/
    //std::cout << "ERROR: " << glGetError() << std::endl;

    glDeleteVertexArrays(1, &m_VertexArray);
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteBuffers(1, &m_FaceElementBuffer);
    m_VertexArray = 0;
    m_VertexBuffer = 0;
    m_FaceElementBuffer = 0;
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

int* RTRSceneTwo::GetNumLights()
{
    int* number = &m_NumLights;
    return number;
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
    int currSubdivision = m_Subdivisions - 1;
    int* number = &amountOfVertices.at(currSubdivision);
    return number;
}

int* RTRSceneTwo::GetFaces()
{
    int currSubdivision = m_Subdivisions - 1;
    int* number = &amountOfFaces.at(currSubdivision);
    return number;
}

float* RTRSceneTwo::GetVertexData()
{
    float* number = &m_VertexData;
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

void RTRSceneTwo::IncrementLights()
{
    m_NumLights += 1;
}

void RTRSceneTwo::DecrementLights()
{
    m_NumLights -= 1;
}
