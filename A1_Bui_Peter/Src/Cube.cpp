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
					Cube newCube(this->pos.x + (i * radius), this->pos.y + (j * radius), this->pos.z + (k * radius), radius);

					cubeVector.push_back(newCube);
				}
			}
		}
	}

	return cubeVector;
}

void Cube::CalculateNewRadius() {
	float radius = dimensions / 3;

	this->dimensions = radius;
}

std::vector<GLfloat> Cube::CalculateNewPositionsImmediate(Cube currCube, std::vector<GLfloat> VerAndColPoints) {
	float currCubePosX = *currCube.GetPosX();
	float currCubePosY = *currCube.GetPosY();
	float currCubePosZ = *currCube.GetPosZ();

	int totalFaceQuadrants = VerAndColPoints.size() / 24;

	for (int j = 0; j < totalFaceQuadrants; j++) {
		for (int i = 0; i < 4; i++) {
			int posX = (i + (i * 5)) + (j * 24);
			int posY = (i + (i * 5) + 1) + (j * 24);
			int posZ = (i + (i * 5) + 2) + (j * 24);

			float newPosX = (VerAndColPoints.at(posX) / 3.0f - currCubePosX);
			float newPosY = (VerAndColPoints.at(posY) / 3.0f + currCubePosY);
			float newPosZ = (VerAndColPoints.at(posZ) / 3.0f - currCubePosZ);

			VerAndColPoints.at(posX) = newPosX;
			VerAndColPoints.at(posY) = newPosY;
			VerAndColPoints.at(posZ) = newPosZ;
		}
	}

	return VerAndColPoints;
}

std::vector<GLfloat> Cube::CalculateNewPositionsModern(Cube currCube, std::vector<GLfloat> VerAndColPoints)
{
	float currCubePosX = *currCube.GetPosX();
	float currCubePosY = *currCube.GetPosY();
	float currCubePosZ = *currCube.GetPosZ();

	int totalFaceQuadrants = VerAndColPoints.size() / 36;

	for (int j = 0; j < totalFaceQuadrants; j++) {
		for (int i = 0; i < 6; i++) {
			int posX = (i + (i * 5)) + (j * 36);
			int posY = (i + (i * 5) + 1) + (j * 36);
			int posZ = (i + (i * 5) + 2) + (j * 36);

			float newPosX = (VerAndColPoints.at(posX) / 3.0f - currCubePosX);
			float newPosY = (VerAndColPoints.at(posY) / 3.0f + currCubePosY);
			float newPosZ = (VerAndColPoints.at(posZ) / 3.0f - currCubePosZ);

			VerAndColPoints.at(posX) = newPosX;
			VerAndColPoints.at(posY) = newPosY;
			VerAndColPoints.at(posZ) = newPosZ;
		}
	}

	//std::cout << "SIZE: " << VerAndColPoints.size() / 36 << std::endl;

	return VerAndColPoints;
}

std::vector<GLfloat> Cube::CalculateNewVertexPositions(Cube currCube, std::vector<GLfloat> VerAndColPoints, 
	std::vector<int> faces) {
	std::vector<GLfloat> newVertexPositions;

	for (int j = 0; j < VerAndColPoints.size() / 24; j++) {
		for (int i = 0; i < faces.size(); i++) {
			GLfloat posColourX = (faces.at(i) + (faces.at(i) * 5) + 3) + (j * 24);
			GLfloat posColourY = (faces.at(i) + (faces.at(i) * 5) + 4) + (j * 24);
			GLfloat posColourZ = (faces.at(i) + (faces.at(i) * 5) + 5) + (j * 24);

			GLfloat posVertexX = (faces.at(i) + (faces.at(i) * 5)) + (j * 24);
			GLfloat posVertexY = (faces.at(i) + (faces.at(i) * 5) + 1) + (j * 24);
			GLfloat posVertexZ = (faces.at(i) + (faces.at(i) * 5) + 2) + (j * 24);

			std::vector<GLfloat> tempPositions = { VerAndColPoints.at(posVertexX),  VerAndColPoints.at(posVertexY), 
				 VerAndColPoints.at(posVertexZ),  VerAndColPoints.at(posColourX),  VerAndColPoints.at(posColourY),  VerAndColPoints.at(posColourZ) };

			newVertexPositions.insert(newVertexPositions.end(), tempPositions.begin(), tempPositions.end());
		}
	}

	return newVertexPositions;
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

float* Cube::GetRadius() {
	float* radius = &dimensions;
	return radius;
}
