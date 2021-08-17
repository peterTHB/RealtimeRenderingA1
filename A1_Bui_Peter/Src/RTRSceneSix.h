#pragma once
#include "RTRSceneBase.h"

class RTRSceneSix : public RTRSceneBase {
public:
	RTRSceneSix(float windowWidth, float windowHeight);
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

	Geometry* geom;
};
