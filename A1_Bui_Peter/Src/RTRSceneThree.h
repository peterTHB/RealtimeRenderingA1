#pragma once
#include "RTRSceneBase.h"

class RTRSceneThree : public RTRSceneBase {
public:
	RTRSceneThree(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndNormals,
		std::vector<int> faces, Lighting* lighting, RTRShader* shader);
	virtual void Init();
	virtual void End();
	virtual void DrawAll(Camera* camera);
	virtual void DrawModern(Camera* camera);
	virtual void CreateCubes();
	
	virtual bool* GetDepthBuffer();
	virtual bool* GetBackface();
	virtual bool* GetLighting();
	virtual int* GetNumLights();
	virtual void ToggleDepthBuffer();
	virtual void ToggleBackface();
	virtual void ToggleLighting();

	virtual int* GetSubdivisions();
	virtual int* GetVertices();
	virtual int* GetFaces();
	virtual float* GetVertexData();
	virtual void IncrementSubdivision();
	virtual void DecrementSubdivision();
	virtual void IncrementLights();
	virtual void DecrementLights();

protected:
	float m_WindowHeight;
	float m_WindowWidth;
	bool m_DepthState;
	bool m_BackfaceState;
	bool m_LightingState;
	int m_Subdivisions;
	int m_Vertices;
	int m_Faces;
	int m_NumLights;
	float m_VertexData;

	Geometry* geom;
	Cube* cube;
	Lighting* lighting;
	std::vector<int> amountOfVertices;
	std::vector<int> amountOfFaces;
	std::vector<Cube> Cubes;
	std::vector<int> facesCopy;
	std::vector<std::vector<GLfloat>> listOfMidVertexes;
	std::vector<std::vector<std::vector<GLfloat>>> listOfVertexes;

	RTRShader* sceneShader;
	unsigned int m_VertexArray;
	unsigned int m_VertexBuffer;
	unsigned int m_FaceElementBuffer;
	unsigned int m_InstancedVertexBuffer;
};
