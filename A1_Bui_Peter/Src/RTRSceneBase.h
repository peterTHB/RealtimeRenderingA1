#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <sdl/SDL.h>
#include <stb/stb_image.h>

class RTRSceneBase {
public:
	RTRSceneBase();
	RTRSceneBase(float windowWidth, float windowHeight);
	virtual void Init();
	virtual void End();
	virtual void DrawAll();
	
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
	virtual void IncrementVertices();
	virtual void DecrementVertices();
	virtual void IncrementFaces();
	virtual void DecrementFaces();

protected:
	float m_WindowHeight;
	float m_WindowWidth;
	bool m_DepthState;
	bool m_BackfaceState;
	bool m_LightingState;
	int m_Subdivisions;
	int m_Vertices;
	int m_Faces;
};