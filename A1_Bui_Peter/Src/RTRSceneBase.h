#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <sdl/SDL.h>
#include <stb/stb_image.h>
#include <vector>
#include "Geometry.h"
#include "Cube.h"
#include "Lighting.h"
#include "Camera.h"
#include "RTRShader.h"
#include "RTRShaderLight.h"

class RTRSceneBase {
public:
	RTRSceneBase();
	RTRSceneBase(float windowWidth, float windowHeight);
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
	std::vector<Cube> Cubes;
	std::vector<int> facesCopy;
	std::vector<std::vector<GLfloat>> listOfVertexes;
};