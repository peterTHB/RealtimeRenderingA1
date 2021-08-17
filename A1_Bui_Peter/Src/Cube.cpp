#include "Cube.h"

Cube::Cube(float x, float y, float z, float dimensions)
{
	this->pos = glm::vec3(x, y, z);
	this->dimensions = dimensions;
}

std::vector<Cube> Cube::DrawCube()
{
	std::vector<Cube> cubeVector;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			for (int k = -1; k < 2; k++) {
				float radius = dimensions / 3;
				Cube newCube(pos.x + i * radius, pos.y + j * radius, pos.z + k * radius, radius);
				cubeVector.push_back(newCube);
			}
		}
	}

	return cubeVector;
}
