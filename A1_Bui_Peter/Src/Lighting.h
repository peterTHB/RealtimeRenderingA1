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

class Lighting {
public:
	Lighting();
	void InstantiateImmediate();
	void ImmediateLighting(glm::vec3 cameraPos);
	void ImmediateSpotLighting(int amountOfLights);

protected:
	std::vector<GLfloat> ambientLighting;
	std::vector<GLfloat> diffuseLighting;
	std::vector<GLfloat> specularLighting;
};