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

	geom = new Geometry;
	cube = new Cube(0.0f, 0.0f, 0.0f, 1.0f);
	Cubes.push_back(*cube);

	facesCopy = faces;
	std::vector<std::vector<GLfloat>> placeholder;
	placeholder.push_back(vertexAndColours);
	listOfVertexes.push_back(placeholder);

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

int RTRSceneTwo::DrawModern() {
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

    int err_ok;
    char err_info[512];

    const char* vertex_shader_source = "#version 400\n"
        "layout (location = 0) in vec3 vertex_position;\n"
        "layout (location = 1) in vec3 vertex_color;\n"
        "out vec3 v_color;\n"
        "void main() {\n"
        "  v_color = vertex_color;\n"
        "  gl_Position = vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1.0);\n"
        "}\0";
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &err_ok);
    if (!err_ok) {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, err_info);
        std::cout << "RTR:ERROR: Vertex Shader failed to compile. Error: " << err_info << std::endl;
        return -1;
    }

    const char* fragment_shader_source = "#version 400\n"
        "in vec3 v_color;\n"
        "out vec4 fragment_color;\n"
        "void main() {\n"
        "  fragment_color = vec4(v_color, 1.0f);\n"
        "}\0";
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &err_ok);
    if (!err_ok) {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, err_info);
        std::cout << "RTR:ERROR: Fragment Shader failed to compile. Error: " << err_info << std::endl;
        return -2;
    }

    m_SquareProgram = glCreateProgram();
    glAttachShader(m_SquareProgram, vertex_shader);
    glAttachShader(m_SquareProgram, fragment_shader);
    glLinkProgram(m_SquareProgram);
    glGetProgramiv(m_SquareProgram, GL_LINK_STATUS, &err_ok);
    if (!err_ok) {
        glGetProgramInfoLog(m_SquareProgram, 512, NULL, err_info);
        std::cout << "RTR:ERROR: Shader Program failed to link. Error: " << err_info << std::endl;
        return -3;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glUseProgram(m_SquareProgram);
    glBindVertexArray(m_VertexArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    return 0;
}

void RTRSceneTwo::DrawCubes()
{
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
