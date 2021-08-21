#pragma once
#include "RTRSceneBase.h"

class RTRSceneTwo : public RTRSceneBase {
public:
	RTRSceneTwo(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndColours, 
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

	virtual int DrawModern();

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

	unsigned int m_VertexArray;
	unsigned int m_VertexBuffer;
	unsigned int m_FaceElementBuffer;
	unsigned int m_SquareProgram;
};
