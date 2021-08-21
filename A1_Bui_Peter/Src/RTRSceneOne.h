#pragma once
#include "RTRSceneBase.h"

class RTRSceneOne : public RTRSceneBase {
public:
	RTRSceneOne(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndColours, 
		std::vector<int> faces, Lighting* lighting);
	virtual void Init();
	virtual void End();
	virtual void DrawAll();
	virtual void DrawCubes();

	virtual bool* GetDepthBuffer();
	virtual bool* GetBackface();
	virtual bool* GetLighting();
	virtual void ToggleDepthBuffer();
	virtual void ToggleBackface();
	virtual void ToggleLighting();

	virtual int* GetSubdivisions();
	virtual int* GetVertices();
	virtual int* GetFaces();
	virtual void IncrementSubdivision();
	virtual void DecrementSubdivision();

protected:
	float m_WindowHeight;
	float m_WindowWidth;
	bool m_DepthState;
	bool m_BackfaceState;
	bool m_LightingState;
	int m_Subdivisions;

	Geometry* geom;
	Cube* cube;
	Lighting* lighting;
	std::vector<int> amountOfVertices;
	std::vector<int> amountOfFaces;
	std::vector<Cube> Cubes;
	std::vector<int> facesCopy;
	std::vector<std::vector<GLfloat>> listOfMidVertexes;
	std::vector<std::vector<std::vector<GLfloat>>> listOfVertexes;
};
