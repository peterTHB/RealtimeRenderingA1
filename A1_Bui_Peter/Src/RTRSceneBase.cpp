#include "RTRSceneBase.h"

RTRSceneBase::RTRSceneBase() {
	m_WindowWidth = 0;
	m_WindowHeight = 0;
	m_DepthState = false;
	m_BackfaceState = false;
	m_LightingState = false;
	m_Subdivisions = 1;
	m_Vertices = 1;
	m_Faces = 1;

	geom = nullptr;
	cube = nullptr;
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

	geom = nullptr;
	cube = nullptr;
}

void RTRSceneBase::Init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void RTRSceneBase::End() {
	geom = nullptr;
	cube = nullptr;
	facesCopy.clear();
	listOfVertexes.clear();
}

void RTRSceneBase::DrawAll() {

}

void RTRSceneBase::DrawCubes()
{
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
