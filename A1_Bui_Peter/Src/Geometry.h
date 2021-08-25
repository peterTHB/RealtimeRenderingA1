#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <sdl/SDL.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Lighting.h"
#include "RTRShader.h"

class Geometry {
public:
	Geometry();
	Geometry(RTRShader* shader);
	virtual void DrawAllImmediate(std::vector<std::vector<GLfloat>> vertexAndNormalsHolder,
		std::vector<int> faces);
	virtual void DrawAllModern(std::vector<std::vector<GLfloat>> vertexAndNormalsHolder,
		std::vector<int> faces, int size);
	virtual void DrawCubeWithPointsImmediate(std::vector<std::vector<GLfloat>> vertexAndNormalsHolder,
		std::vector<int> faces);
	virtual void DrawCubeWithPointsModern(std::vector<std::vector<GLfloat>> vertexAndNormalsHolder,
		std::vector<int> faces, int size);

private:
	RTRShader* sceneShader;
};