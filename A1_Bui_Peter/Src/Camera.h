#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <sdl/SDL.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Lighting.h"
#ifndef M_PI
#define M_PI = 3.1415926535
#endif

class Camera {
public:
	Camera();
    virtual void ImmediateCamera(int width, int height);
    virtual void ModernCamera(int width, int height);
    virtual void Mouse_Callback(SDL_Window* window, float xRel, float yRel);
    virtual void UpdateVectors();
    virtual void LockCamera();

    virtual void SetCameraPos(glm::vec3 cameraPos);

    virtual glm::vec3* GetCameraPos();
    virtual glm::vec3* GetCameraFront();
    virtual glm::vec3* GetCameraUp();
    virtual const float* GetCameraSpeed();
    virtual float* GetDeltaTime();

protected:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraWUp;
    glm::mat4 proj;
    glm::mat4 view;
    float cameraSpeed;
    float deltaTime;
    float lastFrame;

    int width;
    int height;

    bool checkMouse;
    float pitch;
    float yaw;
    float lastX;
    float lastY;
    float fov;

    Lighting* lighting;
};