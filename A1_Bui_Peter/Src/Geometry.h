#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <sdl/SDL.h>
#include <stb/stb_image.h>

class Geometry {
public:
	Geometry();
	virtual void DrawAllImmediate();
	virtual void DrawTriangle(float x, float y, float z, float r, float g, float b);

protected:

};