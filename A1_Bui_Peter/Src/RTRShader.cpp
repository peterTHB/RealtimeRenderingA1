#include "RTRShader.h"

RTRShader::RTRShader()
{
    ID = 0;
}

void RTRShader::Load(const char* vertexFile, const char* fragmentFile)
{
    int err_ok;
    char err_info[512];

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream verShaderFile;
    std::ifstream fragShaderFile;

    verShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        verShaderFile.open(vertexFile);
        fragShaderFile.open(fragmentFile);

        std::stringstream verShaderStream, fragShaderStream;

        verShaderStream << verShaderFile.rdbuf();
        fragShaderStream << fragShaderFile.rdbuf();

        verShaderFile.close();
        fragShaderFile.close();

        vertexCode = verShaderStream.str();
        fragmentCode = fragShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* verShaderCode = vertexCode.c_str();
    const char* fragShaderCode = fragmentCode.c_str();

    unsigned int vertex_shader, fragment_shader;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &verShaderCode, nullptr);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &err_ok);
    if (!err_ok) {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, err_info);
        std::cout << "RTR:ERROR: Vertex Shader failed to compile. Error: " << err_info << std::endl;
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragShaderCode, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &err_ok);
    if (!err_ok) {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, err_info);
        std::cout << "RTR:ERROR: Fragment Shader failed to compile. Error: " << err_info << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex_shader);
    glAttachShader(ID, fragment_shader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &err_ok);
    if (!err_ok) {
        glGetProgramInfoLog(ID, 512, NULL, err_info);
        std::cout << "RTR:ERROR: Shader Program failed to link. Error: " << err_info << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

unsigned int* RTRShader::GetID()
{
	unsigned int* currId = &ID;
	return currId;
}
