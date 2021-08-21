#pragma once
#include "RTRSceneBase.h"

class RTRSceneThree : public RTRSceneBase {
public:
	RTRSceneThree(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndColours, 
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
	int m_Vertices;
	int m_Faces;

	Geometry* geom;
	Cube* cube;
	std::vector<Cube> Cubes;
	std::vector<int> facesCopy;
	std::vector<std::vector<std::vector<GLfloat>>> listOfVertexes;
};
