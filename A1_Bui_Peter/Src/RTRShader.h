#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

class RTRShader {
public:
	RTRShader();
	virtual void Load(const char* vertexFile, const char* fragmentFile, const char* geometryFile = nullptr);

	virtual unsigned int* GetID();

	virtual void SetBool(const std::string& name, bool value) const;
	virtual void SetInt(const std::string& name, int value) const;
	virtual void SetFloat(const std::string& name, float value) const;
	virtual void SetVec2(const std::string& name, const glm::vec2 &value) const;
	virtual void SetVec2(const std::string& name, float x, float y) const;
	virtual void SetVec3(const std::string& name, const glm::vec3 &value) const;
	virtual void SetVec3(const std::string& name, float x, float y, float z) const;
	virtual void SetVec4(const std::string& name, const glm::vec4 &value) const;
	virtual void SetVec4(const std::string& name, float x, float y, float z, float w) const;
	virtual void SetMat2(const std::string& name, const glm::mat2 &mat) const;
	virtual void SetMat3(const std::string& name, const glm::mat3 &mat) const;
	virtual void SetMat4(const std::string& name, const glm::mat4 &mat) const;

protected:
	unsigned int ID;
};