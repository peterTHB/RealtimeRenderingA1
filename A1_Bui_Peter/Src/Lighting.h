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
#include "RTRShader.h"

class Lighting {
public:
	Lighting();
	virtual void InstantiateImmediate();
	virtual void ImmediateLighting(glm::vec3 cameraPos);
	virtual void ImmediateSpotLighting(int amountOfLights);
	virtual void ModernLighting(RTRShader* shader, int numLights, glm::vec3 cameraFront, glm::vec3 cameraPos,
		std::vector<glm::vec3> pointLightPositions, std::vector<glm::vec3> pointLightMaterial);

protected:
	std::vector<GLfloat> ambientLighting;
	std::vector<GLfloat> diffuseLighting;
	std::vector<GLfloat> specularLighting;
};