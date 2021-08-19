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

class Geometry {
public:
	Geometry();
	virtual void DrawAllImmediate();
	virtual void DrawAllModern();
	virtual void DrawCubeWithPoints(std::vector<std::vector<GLfloat>> vertexAndColoursHolder, std::vector<int> faces);
	virtual glm::vec3 CalculateNormals(glm::vec3 point0, glm::vec3 point1, glm::vec3 point2);

private:
};