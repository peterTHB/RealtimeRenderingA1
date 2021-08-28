#include "Cube.h"

Cube::Cube(float x, float y, float z, float dimensions)
{
	this->pos = glm::vec3(x, y, z);
	this->dimensions = dimensions;
	this->oldTimeStart = 0;
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

std::vector<GLfloat> Cube::CalculateNewPositionsImmediate(Cube currCube, std::vector<GLfloat> VerAndNormPoints) {
	float currCubePosX = *currCube.GetPosX();
	float currCubePosY = *currCube.GetPosY();
	float currCubePosZ = *currCube.GetPosZ();

	int totalFaceQuadrants = VerAndNormPoints.size() / 24;

	for (int j = 0; j < totalFaceQuadrants; j++) {
		for (int i = 0; i < 4; i++) {
			int posX = (i + (i * 5)) + (j * 24);
			int posY = (i + (i * 5) + 1) + (j * 24);
			int posZ = (i + (i * 5) + 2) + (j * 24);

			float newPosX = (VerAndNormPoints.at(posX) / 3.0f - currCubePosX);
			float newPosY = (VerAndNormPoints.at(posY) / 3.0f + currCubePosY);
			float newPosZ = (VerAndNormPoints.at(posZ) / 3.0f - currCubePosZ);

			VerAndNormPoints.at(posX) = newPosX;
			VerAndNormPoints.at(posY) = newPosY;
			VerAndNormPoints.at(posZ) = newPosZ;
		}
	}

	return VerAndNormPoints;
}

std::vector<GLfloat> Cube::CalculateNewPositionsModern(Cube currCube, std::vector<GLfloat> VerAndNormPoints)
{
	float currCubePosX = *currCube.GetPosX();
	float currCubePosY = *currCube.GetPosY();
	float currCubePosZ = *currCube.GetPosZ();

	int totalFaceQuadrants = VerAndNormPoints.size() / 36;

	for (int j = 0; j < totalFaceQuadrants; j++) {
		for (int i = 0; i < 6; i++) {
			int posX = (i + (i * 5)) + (j * 36);
			int posY = (i + (i * 5) + 1) + (j * 36);
			int posZ = (i + (i * 5) + 2) + (j * 36);

			float newPosX = (VerAndNormPoints.at(posX) / 3.0f - currCubePosX);
			float newPosY = (VerAndNormPoints.at(posY) / 3.0f + currCubePosY);
			float newPosZ = (VerAndNormPoints.at(posZ) / 3.0f - currCubePosZ);

			VerAndNormPoints.at(posX) = newPosX;
			VerAndNormPoints.at(posY) = newPosY;
			VerAndNormPoints.at(posZ) = newPosZ;
		}
	}
	return VerAndNormPoints;
}

std::vector<GLfloat> Cube::CalculateNewVertexPositions(Cube currCube, std::vector<GLfloat> VerAndNormPoints, 
	std::vector<int> faces) {
	std::vector<GLfloat> newVertexPositions;

	for (int j = 0; j < VerAndNormPoints.size() / 24; j++) {
		for (int i = 0; i < 6; i++) {
			GLfloat posNormalX = (faces.at(i) + (faces.at(i) * 5) + 3) + (j * 24);
			GLfloat posNormalY = (faces.at(i) + (faces.at(i) * 5) + 4) + (j * 24);
			GLfloat posNormalZ = (faces.at(i) + (faces.at(i) * 5) + 5) + (j * 24);

			GLfloat posVertexX = (faces.at(i) + (faces.at(i) * 5)) + (j * 24);
			GLfloat posVertexY = (faces.at(i) + (faces.at(i) * 5) + 1) + (j * 24);
			GLfloat posVertexZ = (faces.at(i) + (faces.at(i) * 5) + 2) + (j * 24);

			std::vector<GLfloat> tempPositions = { VerAndNormPoints.at(posVertexX),  VerAndNormPoints.at(posVertexY),
				 VerAndNormPoints.at(posVertexZ),  VerAndNormPoints.at(posNormalX),  VerAndNormPoints.at(posNormalY),
				VerAndNormPoints.at(posNormalZ) };

			newVertexPositions.insert(newVertexPositions.end(), tempPositions.begin(), tempPositions.end());
		}
	}

	return newVertexPositions;
}

std::vector<int> Cube::ExtraCubeFaces(std::vector<int> faces) {
	int faceOne = faces.at(0);
	int faceTwo = faces.at(1);
	int faceThree = faces.at(2);
	int faceFour = faces.at(3);
	int faceFive = faces.at(4);
	int faceSix = faces.at(5);

	for (int i = 1; i < 6; i++) {
		int extraFaceOne = faceOne + (4 * i);
		int extraFaceTwo = faceTwo + (4 * i);
		int extraFaceThree = faceThree + (4 * i);
		int extraFaceFour = faceFour + (4 * i);
		int extraFaceFive = faceFive + (4 * i);
		int extraFaceSix = faceSix + (4 * i);

		std::vector<int> tempFaces = { extraFaceOne, extraFaceTwo, extraFaceThree, 
										extraFaceFour, extraFaceFive, extraFaceSix };

		faces.insert(faces.end(), tempFaces.begin(), tempFaces.end());
	}

	return faces;
}

std::vector<int> Cube::AddExtraCubeFaces(std::vector<int> faces, int size)
{
	std::vector<int> tempFaces = faces;
	std::vector<int> storeAllCalc;

	storeAllCalc.insert(storeAllCalc.end(), faces.begin(), faces.end());

	for (int j = 1; j < size; j++) {
		for (int i = 0; i < faces.size(); i++) {
			tempFaces.at(i) = faces.at(i) + (24 * j);
		}

		storeAllCalc.insert(storeAllCalc.end(), tempFaces.begin(), tempFaces.end());
	}

	return storeAllCalc;
}

std::vector<GLfloat> Cube::CalculatePulsation(std::vector<GLfloat> allVertices, float time, int currSubdivision) {
	if (currSubdivision != 0) {
		for (int i = 0; i < allVertices.size(); i = i + 6) {
			glm::vec3 calcPoint = glm::vec3(0.0f);

			int yLocation = i + 1;
			int zLocation = i + 2;

			float posX = allVertices.at(i);
			float posY = allVertices.at(yLocation);
			float posZ = allVertices.at(zLocation);

			float radius = (abs(posX) > abs(posY) ? posX : posY);
			radius = abs(radius) > abs(posZ) ? radius : posZ;
			radius = abs(radius);

			glm::vec3 currPos = glm::vec3(posX, posY, posZ);
			calcPoint = glm::normalize(currPos);

			calcPoint *= radius;

			glm::vec3 newPos = currPos + ((calcPoint - currPos) * sin(time * time));

			allVertices.at(i) = newPos.x;
			allVertices.at(yLocation) = newPos.y;
			allVertices.at(zLocation) = newPos.z;
		};
	}

	return allVertices;
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
