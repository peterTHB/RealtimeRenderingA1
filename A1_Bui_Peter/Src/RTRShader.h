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
	virtual void Load(const char* vertexFile, const char* fragmentFile);

	virtual unsigned int* GetID();

protected:
	unsigned int ID;
};