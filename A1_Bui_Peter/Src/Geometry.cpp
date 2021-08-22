#include "Geometry.h"

Geometry::Geometry()
{
	lighting = new Lighting();
	sceneShader = nullptr;
}

Geometry::Geometry(RTRShader* shader) {
	lighting = new Lighting();
	sceneShader = shader;
}

void Geometry::DrawAllImmediate(std::vector<std::vector<GLfloat>> vertexAndColoursHolder, std::vector<int> faces) {
	GLfloat ambientArray[] = { 0.2f, 1.0f, 0.2f, 1.0f };
	GLfloat diffuseArray[] = { 0.2f, 0.2f, 1.0f, 1.0f };
	GLfloat specularArray[] = { 1.0f, 0.2f, 0.2f, 1.0f };
	GLfloat shinyArray[] = { 100.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientArray);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseArray);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shinyArray);

	DrawCubeWithPoints(vertexAndColoursHolder, faces);
}

void Geometry::DrawAllModern() {

}

void Geometry::DrawCubeWithPoints(std::vector<std::vector<GLfloat>> vertexAndColoursHolder, std::vector<int> faces) {
	glBegin(GL_TRIANGLES);
	for (auto& VACVertex : vertexAndColoursHolder) {
		for (int j = 0; j < VACVertex.size() / 24; j++) {
			for (int i = 0; i < faces.size(); i++) {
				int posColourX = (faces.at(i) + (faces.at(i) * 5) + 3) + (j * 24);
				int posColourY = (faces.at(i) + (faces.at(i) * 5) + 4) + (j * 24);
				int posColourZ = (faces.at(i) + (faces.at(i) * 5) + 5) + (j * 24);

				int posVertexX = (faces.at(i) + (faces.at(i) * 5)) + (j * 24);
				int posVertexY = (faces.at(i) + (faces.at(i) * 5) + 1) + (j * 24);
				int posVertexZ = (faces.at(i) + (faces.at(i) * 5) + 2) + (j * 24);

				glColor3f(VACVertex.at(posColourX),
					VACVertex.at(posColourY),
					VACVertex.at(posColourZ));
				glNormal3f(0.0f, 0.0f, 1.0f);
				glVertex3f(VACVertex.at(posVertexX),
					VACVertex.at(posVertexY),
					VACVertex.at(posVertexZ));
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
