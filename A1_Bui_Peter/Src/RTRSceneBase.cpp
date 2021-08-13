#include "RTRSceneBase.h"
#include "Geometry.h"

RTRSceneBase::RTRSceneBase() {
	m_WindowWidth = 0;
	m_WindowHeight = 0;
	m_DepthState = false;
	m_BackfaceState = false;
	m_LightingState = false;
	m_Subdivisions = 1;
	m_Vertices = 1;
	m_Faces = 1;
}

RTRSceneBase::RTRSceneBase(float windowWidth, float windowHeight) {
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
	m_DepthState = false;
	m_BackfaceState = false;
	m_LightingState = false;
	m_Subdivisions = 1;
	m_Vertices = 1;
	m_Faces = 1;
}

void RTRSceneBase::Init() {

}

void RTRSceneBase::End() {

}

void RTRSceneBase::DrawAll() {
	Geometry* geom = new Geometry();

	geom->DrawAllImmediate();

	glUseProgram(0);
}

bool* RTRSceneBase::GetDepthBuffer()
{
	bool* state = &m_DepthState;
	return state;
}

bool* RTRSceneBase::GetBackface()
{
	bool* state = &m_BackfaceState;
	return state;
}

bool* RTRSceneBase::GetLighting()
{
	bool* state = &m_LightingState;
	return state;
}

void RTRSceneBase::ToggleDepthBuffer()
{
	m_DepthState = !m_DepthState;
}

void RTRSceneBase::ToggleBackface()
{
	m_BackfaceState = !m_BackfaceState;
}

void RTRSceneBase::ToggleLighting()
{
	m_LightingState = !m_LightingState;
}

int* RTRSceneBase::GetSubdivisions()
{
	int* number = &m_Subdivisions;
	return number;
}

int* RTRSceneBase::GetVertices()
{
	int* number = &m_Vertices;
	return number;
}

int* RTRSceneBase::GetFaces()
{
	int* number = &m_Faces;
	return number;
}

void RTRSceneBase::IncrementSubdivision()
{
	m_Subdivisions += 1;
}

void RTRSceneBase::DecrementSubdivision()
{
	m_Subdivisions -= 1;
}

void RTRSceneBase::IncrementVertices()
{
	m_Vertices += 1;
}

void RTRSceneBase::DecrementVertices()
{
	m_Vertices -= 1;
}

void RTRSceneBase::IncrementFaces()
{
	m_Faces += 1;
}

void RTRSceneBase::DecrementFaces()
{
	m_Faces -= 1;
}
