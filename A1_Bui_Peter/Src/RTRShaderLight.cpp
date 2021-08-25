#include "RTRShaderLight.h"

RTRShaderLight::RTRShaderLight()
{
    ID = 0;
}

void RTRShaderLight::Load(const char* vertexFile, const char* fragmentFile, const char* geometryFile)
{
    int err_ok;
    char err_info[512];

    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream verShaderFile;
    std::ifstream fragShaderFile;
    std::ifstream geomShaderFile;

    verShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    geomShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

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

        if (geometryFile != nullptr) {
            geomShaderFile.open(geometryFile);
            std::stringstream geomShaderStream;
            geomShaderStream << geomShaderFile.rdbuf();
            geomShaderFile.close();
            geometryCode = geomShaderStream.str();
        }
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

    unsigned int geometry_shader;
    if (geometryFile != nullptr) {
        const char* geomShaderCode = geometryCode.c_str();
        geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry_shader, 1, &geomShaderCode, nullptr);
        glCompileShader(geometry_shader);
        glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &err_ok);
        if (!err_ok) {
            glGetShaderInfoLog(geometry_shader, 512, nullptr, err_info);
            std::cout << "RTR:ERROR: Geometry Shader failed to compile. Error: " << err_info << std::endl;
        }
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex_shader);
    glAttachShader(ID, fragment_shader);
    if (geometryFile != nullptr) {
        glAttachShader(ID, geometry_shader);
    }
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &err_ok);
    if (!err_ok) {
        glGetProgramInfoLog(ID, 512, NULL, err_info);
        std::cout << "RTR:ERROR: Shader Program failed to link. Error: " << err_info << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    if (geometryFile != nullptr) {
        glDeleteShader(geometry_shader);
    }
}

unsigned int* RTRShaderLight::GetID()
{
    unsigned int* currId = &ID;
    return currId;
}

void RTRShaderLight::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void RTRShaderLight::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void RTRShaderLight::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void RTRShaderLight::SetVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void RTRShaderLight::SetVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void RTRShaderLight::SetVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void RTRShaderLight::SetVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void RTRShaderLight::SetVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void RTRShaderLight::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void RTRShaderLight::SetMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void RTRShaderLight::SetMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void RTRShaderLight::SetMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
