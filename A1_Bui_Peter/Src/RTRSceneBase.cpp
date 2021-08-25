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
	m_NumLights = 1;
	m_VertexData = 0;

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
	m_NumLights = 1;
	m_VertexData = 0;

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

void RTRSceneBase::DrawAll(Camera* camera) {

}

void RTRSceneBase::CreateCubes()
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

int* RTRSceneBase::GetNumLights()
{
	int* number = &m_NumLights;
	return number;
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

float* RTRSceneBase::GetVertexData()
{
	float* number = &m_VertexData;
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

void RTRSceneBase::IncrementLights()
{
	m_NumLights += 1;
}

void RTRSceneBase::DecrementLights()
{
	m_NumLights -= 1;
}
