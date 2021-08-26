#pragma once
#include "RTRSceneBase.h"

class RTRSceneOne : public RTRSceneBase {
public:
	RTRSceneOne(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndNormals,
		std::vector<int> faces, Lighting* lighting);
	virtual void Init();
	virtual void End();
	virtual void DrawAll(Camera* camera);
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
	Lighting* sceneLighting;
	std::vector<int> amountOfVertices;
	std::vector<int> amountOfFaces;
	std::vector<Cube> Cubes;
	std::vector<int> facesCopy;
	std::vector<std::vector<GLfloat>> listOfMidVertexes;
	std::vector<std::vector<std::vector<GLfloat>>> listOfVertexes;
};
