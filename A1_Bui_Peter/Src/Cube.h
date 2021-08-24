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

class Cube {
public:
	Cube(float x, float y, float z, float dimensions);
	virtual std::vector<Cube> CalculateCube();
	virtual std::vector<GLfloat> CalculateNewPositionsImmediate(Cube currCube,
		std::vector<GLfloat> VerAndColPoints);
	virtual std::vector<GLfloat> CalculateNewPositionsModern(Cube currCube,
		std::vector<GLfloat> VerAndColPoints);
	virtual std::vector<GLfloat> CalculateNewVertexPositions(Cube currCube, 
		std::vector<GLfloat> VerAndColPoints, std::vector<int> faces);
	virtual void CalculateNewRadius();
	virtual float* GetPosX();
	virtual float* GetPosY();
	virtual float* GetPosZ();
	virtual float* GetRadius();

protected:
	glm::vec3 pos;
	float dimensions;
};