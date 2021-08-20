#include "Cube.h"

Cube::Cube(float x, float y, float z, float dimensions)
{
	this->pos = glm::vec3(x, y, z);
	this->dimensions = dimensions;
}

// Returns all new positions for new cubes to be drawn
std::vector<Cube> Cube::CalculateCube()
{
	std::vector<Cube> cubeVector;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			for (int k = -1; k < 2; k++) {
				int sum = abs(i) + abs(j) + abs(k);
				float radius = dimensions / 3;
				if (sum > 1) {
					Cube newCube(pos.x + i * radius, pos.y + j * radius, pos.z + k * radius, radius);
					cubeVector.push_back(newCube);
				}
			}
		}
	}

	return cubeVector;
}

std::vector<GLfloat> Cube::CalculateNewPositions(Cube currCube, std::vector<GLfloat> VerAndColPoints, 
	std::vector<int> Faces) {
	float currCubePosX = *currCube.GetPosX();
	float currCubePosY = *currCube.GetPosY();
	float currCubePosZ = *currCube.GetPosZ();

	for (int j = 0; j < VerAndColPoints.size() / 24; j++) {
		for (int i = 0; i < Faces.size(); i++) {
			int posZero = (Faces.at(i) + (Faces.at(i) * 5)) + (j * 24);
			int posOne = (Faces.at(i) + (Faces.at(i) * 5) + 1) + (j * 24);
			int posTwo = (Faces.at(i) + (Faces.at(i) * 5) + 2) + (j * 24);

			float newPosX = (VerAndColPoints.at(posZero) + currCubePosX) / 3;
			float newPosY = (VerAndColPoints.at(posOne) + currCubePosY) / 3;
			float newPosZ = (VerAndColPoints.at(posTwo) + currCubePosZ) / 3;

			VerAndColPoints.at(posZero) = newPosX;
			VerAndColPoints.at(posOne) = newPosY;
			VerAndColPoints.at(posTwo) = newPosZ;
		}
	}

	return VerAndColPoints;
}

float* Cube::GetPosX()
{
	float* position = &pos.x;
	return position;
}

float* Cube::GetPosY()
{
	float* position = &pos.y;
	return position;
}

float* Cube::GetPosZ()
{
	float* position = &pos.z;
	return position;
}
