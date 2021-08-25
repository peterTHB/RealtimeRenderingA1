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

void Geometry::DrawAllImmediate(std::vector<std::vector<GLfloat>> vertexAndNormalsHolder, std::vector<int> faces) {
	DrawCubeWithPointsImmediate(vertexAndNormalsHolder, faces);
}

void Geometry::DrawAllModern(std::vector<std::vector<GLfloat>> vertexAndNormalsHolder, std::vector<int> faces, int size) {
	DrawCubeWithPointsModern(vertexAndNormalsHolder, faces, size);
}

void Geometry::DrawCubeWithPointsImmediate(std::vector<std::vector<GLfloat>> vertexAndNormalsHolder, std::vector<int> faces) {
	glBegin(GL_TRIANGLES);
	for (auto& VANVertex : vertexAndNormalsHolder) {
		for (int j = 0; j < VANVertex.size() / 24; j++) {
			for (int i = 0; i < faces.size(); i++) {
				int posVertexX = (faces.at(i) + (faces.at(i) * 5)) + (j * 24);
				int posVertexY = (faces.at(i) + (faces.at(i) * 5) + 1) + (j * 24);
				int posVertexZ = (faces.at(i) + (faces.at(i) * 5) + 2) + (j * 24);

				GLfloat colours = (float)i * 0.15f;
				
				GLfloat ambientArray[] = { 0.6f, 0.6f, 0.6f, 1.0f };
				GLfloat diffuseArray[] = { 0.8f, 0.8f, 0.8f, 1.0f };
				GLfloat specularArray[] = { 1.0f, 1.0f, 1.0f, 1.0f };
				GLfloat shinyArray[] = { 50.0f };

				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientArray);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseArray);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shinyArray);

				glColor3f(colours, colours, colours);
				glVertex3f(VANVertex.at(posVertexX),
					VANVertex.at(posVertexY),
					VANVertex.at(posVertexZ));
			}
		}
	}
	glEnd();
	glUseProgram(0);
}

void Geometry::DrawCubeWithPointsModern(std::vector<std::vector<GLfloat>> vertexAndNormalsHolder,
	std::vector<int> faces, int size)
{
	glm::mat4 model = glm::mat4(1.0f);
	sceneShader->SetMat4("model", model);

	int newSize = 36 * size;
	
	glDrawArrays(GL_TRIANGLES, 0, newSize);
	
	//glDrawArraysInstanced(GL_TRIANGLES, 0, 36, Cubes.size());

	/*glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
}
