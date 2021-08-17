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
	virtual std::vector<Cube> DrawCube();

protected:
	glm::vec3 pos;
	float dimensions;
};