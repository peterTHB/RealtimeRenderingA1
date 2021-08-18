#include "Geometry.h"

GLfloat VertexPointsAndColoursCopy[] = {
	// Points         Colours
	// Front
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
	// Back
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
	// Left
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
	// Right
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
	// Top
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
	// Bottom
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f
};

unsigned int facesCopy[] = {
	0, 1, 2,
	0, 2, 3
};

struct Materials
{
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Shininess;
};

Geometry::Geometry() {
	/*Cube c = Cube(0, 0, 0, 0.5);
	Cubes.push_back(c);*/
}

void Geometry::DrawAllImmediate() {

}

void Geometry::DrawAllModern() {

}

void Geometry::DrawCubeWithPoints(GLfloat vertexAndColours[], unsigned int faces[]) {
	glBegin(GL_TRIANGLES);
	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < 6; i++) {
			glColor3f(vertexAndColours[(faces[i] + (faces[i] * 5) + 3) + (j * 24)],
				vertexAndColours[(faces[i] + (faces[i] * 5) + 4) + (j * 24)],
				vertexAndColours[(faces[i] + (faces[i] * 5) + 5) + (j * 24)]);
			glVertex3f(vertexAndColours[(faces[i] + (faces[i] * 5)) + (j * 24)],
				vertexAndColours[(faces[i] + (faces[i] * 5) + 1) + (j * 24)],
				vertexAndColours[(faces[i] + (faces[i] * 5) + 2) + (j * 24)]);
		}
	}
	glEnd();
	glUseProgram(0);
}

void Geometry::DrawCube()
{
	std::vector<Cube> newCube;

	for (Cube cube : Cubes) {
		std::vector<Cube> createdCube = cube.DrawCube();
		newCube.insert(newCube.end(), createdCube.begin(), createdCube.end());
	}

	this->Cubes = newCube;
}

glm::vec3 Geometry::CalculateNormals(glm::vec3 point0, glm::vec3 point1, glm::vec3 point2)
{
	glm::vec3 pointFirst = glm::vec3(1.0f);
	glm::vec3 pointSecond = glm::vec3(1.0f);
	glm::vec3 pointNormal = glm::vec3(1.0f);

	pointFirst.x = point1.x - point0.x;
	pointFirst.y = point1.y - point0.y;
	pointFirst.z = point1.z - point0.z;

	pointSecond.x = point2.x - point1.x;
	pointSecond.y = point2.y - point1.y;
	pointSecond.z = point2.z - point1.z;

	pointNormal.x = (pointFirst.y * pointSecond.z) - (pointFirst.z * pointSecond.y);
	pointNormal.y = (pointFirst.z * pointSecond.x) - (pointFirst.x * pointSecond.z);
	pointNormal.z = (pointFirst.x * pointSecond.y) - (pointFirst.y * pointSecond.x);

	float len = sqrt((pointNormal.x * pointNormal.x) + (pointNormal.y * pointNormal.y) + (pointNormal.z * pointNormal.z));

	pointNormal.x /= len;
	pointNormal.y /= len;
	pointNormal.z /= len;

	return pointNormal;
}
