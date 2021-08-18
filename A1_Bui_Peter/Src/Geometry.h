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
#include "Cube.h"

class Geometry {
public:
	Geometry();
	virtual void DrawAllImmediate();
	virtual void DrawAllModern();
	virtual void DrawCubeWithPoints(GLfloat vertexAndColours[], unsigned int faces[]);
	virtual void DrawCube();
	virtual glm::vec3 CalculateNormals(glm::vec3 point0, glm::vec3 point1, glm::vec3 point2);

private:
	std::vector<Cube> Cubes;
};