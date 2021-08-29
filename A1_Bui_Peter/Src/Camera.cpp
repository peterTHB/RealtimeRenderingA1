#include "Camera.h"

Camera::Camera(RTRShader* shader) {
    cameraPos = glm::vec3(0.0f, 0.0f, 4.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraWUp = cameraUp;
    cameraSpeed = 2.0f;
    deltaTime = 0.0f;
    lastFrame = 0.0f;

    proj = glm::mat4(1.0f);
    view = glm::mat4(1.0f);

    width = 0;
    height = 0;

    checkMouse = true;
    pitch = 0.0f;
    yaw = -90.0f;
    lastX = 0.0f;
    lastY = 0.0f;
    fov = 45.0f;

    lighting = new Lighting();
    sceneShader = shader;

    projMatrix = glm::mat4(1.0f);
    viewMatrix = glm::mat4(1.0f);
}

void Camera::ImmediateCamera(int width, int height) {
    UpdateVectors();
    this->width = width;
    this->height = height;

    proj = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 10.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(proj));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));

    glm::vec3 normalDir = glm::normalize(-cameraFront);
    glm::vec3 viewDir = glm::normalize(cameraPos);
    glm::vec3 totalDir = glm::normalize(viewDir + normalDir);
    lighting->ImmediateLighting(viewDir);
}

void Camera::ModernCamera(int width, int height) {
    UpdateVectors();
    this->width = width;
    this->height = height;

    view = glm::mat4(1.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    sceneShader->SetMat4("view", view);
    proj = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 10.0f);
    sceneShader->SetMat4("projection", proj);
}

void Camera::Mouse_Callback(SDL_Window* window, float xRel, float yRel) {
    SDL_GetWindowSize(window, &width, &height);

    int xPos, yPos;
    SDL_GetMouseState(&xPos, &yPos);

    if (checkMouse) {
        lastX = xPos;
        lastY = yPos;
        checkMouse = false;
    }

    float xoffset = xPos - lastX;
    float yoffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += (xRel * sensitivity);
    pitch += (-yRel * sensitivity);

    LockCamera();
    UpdateVectors();
}

void Camera::UpdateVectors() {
    glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
    glGetError();

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(direction);

    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraWUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

void Camera::LockCamera()
{
    if (pitch > 90.0f) {
        pitch = 90.0f;
    }
    if (pitch < -90.0f) {
        pitch = -90.0f;
    }

    if (yaw < 0.0) {
        yaw += 360.0f;
    }

    if (yaw > 360.0f) {
        yaw -= 360.0f;
    }
}

void Camera::SetCameraPos(glm::vec3 cameraPos)
{
    this->cameraPos = cameraPos;
}

glm::vec3* Camera::GetCameraPos()
{
    glm::vec3* cameraNum = &cameraPos;
    return cameraNum;
}

glm::vec3* Camera::GetCameraFront()
{
    glm::vec3* cameraNum = &cameraFront;
    return cameraNum;
}

glm::vec3* Camera::GetCameraUp()
{
    glm::vec3* cameraNum = &cameraUp;
    return cameraNum;
}

const float* Camera::GetCameraSpeed() {
    const float* speed = &cameraSpeed;
    return speed;
}

float* Camera::GetDeltaTime()
{
    float currentFrame = SDL_GetTicks();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    deltaTime /= 1000;

    float* deltaPtr = &deltaTime;
    return deltaPtr;
}
