#include "Geometry.h"

struct Materials
{
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Shininess;
};

Geometry::Geometry() {

}

void Geometry::DrawAllImmediate() {

}

void Geometry::DrawAllModern() {

}

void Geometry::DrawCubeWithPoints(std::vector<std::vector<GLfloat>> vertexAndColoursHolder, std::vector<int> faces) {
	glBegin(GL_TRIANGLES);
	for (auto& VACVertex : vertexAndColoursHolder) {
		for (int j = 0; j < VACVertex.size() / 24; j++) {
			for (int i = 0; i < faces.size(); i++) {
				int posColourZero = (faces.at(i) + (faces.at(i) * 5) + 3) + (j * 24);
				int posColourOne = (faces.at(i) + (faces.at(i) * 5) + 4) + (j * 24);
				int posColourTwo = (faces.at(i) + (faces.at(i) * 5) + 5) + (j * 24);

				int posVertexZero = (faces.at(i) + (faces.at(i) * 5)) + (j * 24);
				int posVertexOne = (faces.at(i) + (faces.at(i) * 5) + 1) + (j * 24);
				int posVertexTwo = (faces.at(i) + (faces.at(i) * 5) + 2) + (j * 24);

				glColor3f(VACVertex.at(posColourZero),
					VACVertex.at(posColourOne),
					VACVertex.at(posColourTwo));
				glVertex3f(VACVertex.at(posVertexZero),
					VACVertex.at(posVertexOne),
					VACVertex.at(posVertexTwo));
			}
		}
	}
	glEnd();
	glUseProgram(0);
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
