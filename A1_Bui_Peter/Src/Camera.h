#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <sdl/SDL.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	Camera();
    virtual void ImmediateCamera();
    virtual void ModernCamera();
    virtual void Mouse_Callback(SDL_Window* window, double xpos, double ypos);

    virtual void SetCameraPos(glm::vec3 cameraPos);
    virtual void SetCameraFront(glm::vec3 cameraFront);
    virtual void SetCameraUp(glm::vec3 cameraUp);
    virtual void SetPitch(float pitch);
    virtual void SetYaw(float yaw);
    virtual void SetLastX(float lastX);
    virtual void SetLastY(float lastY);
    virtual void SetFov(float fov);

    virtual glm::vec3* GetCameraPos();
    virtual glm::vec3* GetCameraFront();
    virtual glm::vec3* GetCameraUp();
    virtual const float* GetCameraSpeed();
    virtual float* GetDeltaTime();
    virtual float* GetPitch();
    virtual float* GetYaw();
    virtual float* GetLastX();
    virtual float* GetLastY();
    virtual float* GetFov();

protected:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraWUp;
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
};