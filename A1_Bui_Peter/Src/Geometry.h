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
#include "Cube.h"

class Geometry {
public:
	Geometry();
	Geometry(RTRShader* shader);
	virtual void DrawCubeWithPointsImmediate(std::vector<std::vector<GLfloat>> vertexAndNormalsHolder,
		std::vector<int> faces);
	virtual void DrawCubeWithPoints(int size);
	virtual void DrawMultipleCubes(int currSubdivision, std::vector<Cube> cubePositions, 
		std::vector<glm::vec3> cubePositionsInWorld);
	virtual std::vector<glm::mat4> SetMultiCubeTransforms();
	virtual void DrawCubeArrayInstanced(int size);

private:
	RTRShader* sceneShader;
};