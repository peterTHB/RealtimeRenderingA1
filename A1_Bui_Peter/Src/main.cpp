//-----------------------------------------------------------------------------
// main.cpp
//-----------------------------------------------------------------------------
// Assignment 1 Starter Code
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#include "RTRApp.h"
#include "RTRSceneOne.h"
#include "RTRSceneTwo.h"
#include "RTRSceneThree.h"
#include "RTRSceneFour.h"
#include "RTRSceneFive.h"
#include "RTRSceneSix.h"
#include "Camera.h"
#include "Cube.h"
#include "Lighting.h"

#define GLT_IMPLEMENTATION
#include <gltext/gltext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

std::vector<GLfloat> VertexPointsAndNormals = {
    // Points         Normals
    //// Back
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    // Front
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    // Left
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    // Right
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    // Bottom
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    // Top
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};

std::vector<int> faces = {
    0, 1, 2,
    0, 2, 3
};

class AssignmentApp : public RTRApp
{
public:
    AssignmentApp(const char* title, bool fullscreen = false, int width = 1024, int height = 768)
        : RTRApp(title, fullscreen, width, height) {}
    int Init();
    void Done();
    bool Tick(unsigned int td_milli);

private:
    bool m_QuitApp = false;

    bool m_ShowOSD = true;
    int m_CurrSceneNum = 1;
    std::string m_Resolution = "";
    float m_RefreshRate = 0;
    float m_FPS = 0;
    float FPSCheckCounter = 0;

    RTRSceneBase* ListOfScenes[6] = {};
    RTRSceneBase* m_CurrScene = nullptr;

    // Instantiate shader
    RTRShader* sceneShader = new RTRShader();

    Camera* camera = new Camera(sceneShader);
    Lighting* lighting = new Lighting();

    float deltaX = 0.0f;
    float deltaY = 0.0f;

    int width = 0;
    int height = 0;

    float xRel = 0;
    float yRel = 0;

    float totalFrames = 0.0f;
    int totalFramesAmountsChecked = 0;
    float totalSecondsPassed = 0.0f;

    void CheckInput();
    void UpdateState(unsigned int td_milli);
    void RenderFrame();
    void RenderOSD();
    void CalculateFrames();
    void GetRefreshRate();
};


bool AssignmentApp::Tick(unsigned int td_milli)
{
    m_QuitApp = false;
    CheckInput();
    UpdateState(td_milli);
    RenderFrame();
    return m_QuitApp;
}

void AssignmentApp::CheckInput()
{
    SDL_Event event;

    glm::vec3 cameraPos = *camera->GetCameraPos();
    glm::vec3 cameraFront = *camera->GetCameraFront();
    glm::vec3 cameraUp = *camera->GetCameraUp();
    float cameraDeltaTime = *camera->GetDeltaTime();
    const float cameraSpeed = *camera->GetCameraSpeed() * cameraDeltaTime;

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {

        case SDL_MOUSEMOTION:
            xRel = event.motion.xrel;
            yRel = event.motion.yrel;
            camera->Mouse_Callback(m_SDLWindow, xRel, yRel);
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                m_QuitApp = true;
                break;

                // Changing scenes 1...6
            case SDLK_1:
                m_CurrSceneNum = 1;
                break;
            case SDLK_2:
                m_CurrSceneNum = 2;
                break;
            case SDLK_3:
                m_CurrSceneNum = 3;
                break;
            case SDLK_4:
                m_CurrSceneNum = 4;
                break;
            case SDLK_5:
                m_CurrSceneNum = 5;
                break;
            case SDLK_6:
                m_CurrSceneNum = 6;
                break;

                // Camera Controls
            case SDLK_w:
                cameraPos += cameraSpeed * cameraFront;
                camera->SetCameraPos(cameraPos);
                break;

            case SDLK_s:
                cameraPos -= cameraSpeed * cameraFront;
                camera->SetCameraPos(cameraPos);
                break;

            case SDLK_a:
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                camera->SetCameraPos(cameraPos);
                break;

            case SDLK_d:
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                camera->SetCameraPos(cameraPos);
                break;

                // Increment/Decrement Subdivision
            case SDLK_EQUALS:
                ListOfScenes[m_CurrSceneNum - 1]->CreateCubes();
                ListOfScenes[m_CurrSceneNum - 1]->IncrementSubdivision();
                break;
            case SDLK_KP_PLUS:
                ListOfScenes[m_CurrSceneNum - 1]->CreateCubes();
                ListOfScenes[m_CurrSceneNum - 1]->IncrementSubdivision();
                break;

            case SDLK_MINUS:
                if (*ListOfScenes[m_CurrSceneNum - 1]->GetSubdivisions() > 1) {
                    ListOfScenes[m_CurrSceneNum - 1]->DecrementSubdivision();
                    break;
                }
                break;

            case SDLK_KP_MINUS:
                if (*ListOfScenes[m_CurrSceneNum - 1]->GetSubdivisions() > 1) {
                    ListOfScenes[m_CurrSceneNum - 1]->DecrementSubdivision();
                    break;
                }
                break;

                // Showing OSD
            case SDLK_h:
                m_ShowOSD = !m_ShowOSD;
                break;

                // Toggle Lighting
            case SDLK_l:
                ListOfScenes[m_CurrSceneNum - 1]->ToggleLighting();
                break;

                // Increment/Decrement # of Lights
            case SDLK_PERIOD:
                if (*ListOfScenes[m_CurrSceneNum - 1]->GetNumLights() < 9) {
                    ListOfScenes[m_CurrSceneNum - 1]->IncrementLights();
                    break;
                }
                break;

            case SDLK_COMMA:
                if (*ListOfScenes[m_CurrSceneNum - 1]->GetNumLights() > 0) {
                    ListOfScenes[m_CurrSceneNum - 1]->DecrementLights();
                    break;
                }
                break;

                // Toggle Depth Buffering
            case SDLK_z:
                ListOfScenes[m_CurrSceneNum - 1]->ToggleDepthBuffer();
                break;

                // Toggle Backface Culling
            case SDLK_c:
                ListOfScenes[m_CurrSceneNum - 1]->ToggleBackface();
                break;
            }
        }
    }
}

void AssignmentApp::UpdateState(unsigned int td_milli)
{
    // This is where we will do all our model updating, physics, etc...
    CalculateFrames();
    GetRefreshRate();
}

// Render On-Screen Display
void AssignmentApp::RenderOSD()
{
    // Scene name, display, fps, subdivisions, vertices, faces, data, lighting, depth, backface
    GLTtext* scene_num = gltCreateText();
    GLTtext* display_rates = gltCreateText();
    GLTtext* fps_rates = gltCreateText();
    GLTtext* subdivision_num = gltCreateText();
    GLTtext* vertices_num = gltCreateText();
    GLTtext* faces_num = gltCreateText();
    GLTtext* data_num = gltCreateText();
    GLTtext* lights_on = gltCreateText();
    GLTtext* depth_on = gltCreateText();
    GLTtext* backface_on = gltCreateText();

    std::string sceneNumText = "Scene: " + std::to_string(m_CurrSceneNum);
    std::string displayText = "Resolution: " + m_Resolution + "\n" +
        " Refresh: " + std::to_string(m_RefreshRate);
    std::string fpsText = "FPS: " + std::to_string(m_FPS);
    std::string subdivisionText = "# of Subdivisions: " + std::to_string(
        *ListOfScenes[m_CurrSceneNum - 1]->GetSubdivisions());
    std::string verticesText = "# of Vertices: " + std::to_string(
        *ListOfScenes[m_CurrSceneNum - 1]->GetVertices());
    std::string facesText = "# of Faces: " + std::to_string(
        *ListOfScenes[m_CurrSceneNum - 1]->GetFaces());

    std::string splitVertexString = std::to_string((int)*ListOfScenes[m_CurrSceneNum - 1]->GetVertexData());
    std::string appendVertexString = "";
    int check = 0;
    for (unsigned int i = splitVertexString.length(); i > 0; i -= 1) {
        check++;
        if (check == 3 && i == 1) {
            int value = splitVertexString.at(i - 1) - 48;
            std::string insertString = std::to_string(value);
            appendVertexString.insert(0, insertString);
        }
        else if (check == 3) {
            int value = splitVertexString.at(i - 1) - 48;
            std::string insertString = "," + std::to_string(value);
            appendVertexString.insert(0, insertString);
            check = 0;
        }
        else {
            int value = splitVertexString.at(i - 1) - 48;
            std::string insertString = "" + std::to_string(value);
            appendVertexString.insert(0, insertString);
        }
    }

    std::string vertexDataText = "Vertex Data: " + appendVertexString;
    std::string lightsOnText = "";
    std::string depthOnText = "";
    std::string backfaceOnText = "";

    if (*ListOfScenes[m_CurrSceneNum - 1]->GetLighting()) {
        lightsOnText = "Lights On";
    }
    else {
        lightsOnText = "Lights Off";
    }

    if (*ListOfScenes[m_CurrSceneNum - 1]->GetDepthBuffer()) {
        depthOnText = "Buffer On";
    }
    else {
        depthOnText = "Buffer Off";
    }

    if (*ListOfScenes[m_CurrSceneNum - 1]->GetBackface()) {
        backfaceOnText = "Backface On";
    }
    else {
        backfaceOnText = "Backface Off";
    }

    gltSetText(scene_num, sceneNumText.c_str());
    gltSetText(display_rates, displayText.c_str());
    gltSetText(fps_rates, fpsText.c_str());
    gltSetText(subdivision_num, subdivisionText.c_str());
    gltSetText(vertices_num, verticesText.c_str());
    gltSetText(faces_num, facesText.c_str());
    gltSetText(data_num, vertexDataText.c_str());
    gltSetText(lights_on, lightsOnText.c_str());
    gltSetText(depth_on, depthOnText.c_str());
    gltSetText(backface_on, backfaceOnText.c_str());

    if (m_ShowOSD) {
        gltBeginDraw();
        gltColor(0.0f, 1.0f, 0.0f, 1.0f);
        gltDrawText2D(scene_num, 10, 10, 1.5);
        gltDrawText2D(display_rates, 10, 50, 1.5);
        gltDrawText2D(fps_rates, 10, 120, 1.5);
        gltDrawText2D(subdivision_num, 10, 160, 1.5);
        gltDrawText2D(vertices_num, 10, 200, 1.5);
        gltDrawText2D(faces_num, 10, 240, 1.5);
        gltDrawText2D(data_num, 10, 280, 1.5);
        gltDrawText2D(lights_on, 10, 320, 1.5);
        gltDrawText2D(depth_on, 10, 360, 1.5);
        gltDrawText2D(backface_on, 10, 400, 1.5);
        gltEndDraw();
        glUseProgram(0);

        gltDeleteText(scene_num);
        gltDeleteText(display_rates);
        gltDeleteText(fps_rates);
        gltDeleteText(subdivision_num);
        gltDeleteText(vertices_num);
        gltDeleteText(faces_num);
        gltDeleteText(data_num);
        gltDeleteText(lights_on);
        gltDeleteText(depth_on);
        gltDeleteText(backface_on);
    }
    else {
        gltBeginDraw();
        gltDrawText2D(fps_rates, 10, 10, 2.0);
        gltEndDraw();
        glUseProgram(0);
        gltDeleteText(fps_rates);
    }
}

void AssignmentApp::CalculateFrames()
{
    static float frameRate = 0.0f;
    static float lastTime = 0.0f;

    float currentTime = SDL_GetTicks() * 0.001;

    if (currentTime - lastTime > 1.0f) {
        totalFrames += FPSCheckCounter;
        lastTime = currentTime;
        totalSecondsPassed++;
        FPSCheckCounter = 0;
    }

    ++FPSCheckCounter;
    ++totalFramesAmountsChecked;

    if (totalFramesAmountsChecked == 100) {
        m_FPS = totalFrames / totalSecondsPassed;
        totalFramesAmountsChecked = 0;
        totalFrames = 0;
        totalSecondsPassed = 0;
    }
}

void AssignmentApp::GetRefreshRate() {
    SDL_DisplayMode mode;
    int displayIndex = SDL_GetWindowDisplayIndex(m_SDLWindow);

    int defaultRefreshRate = 60;

    if (SDL_GetDesktopDisplayMode(displayIndex, &mode) != 0) {
        m_RefreshRate = defaultRefreshRate;
    }
    if (mode.refresh_rate == 0) {
        m_RefreshRate = defaultRefreshRate;
    }
    m_RefreshRate = mode.refresh_rate;
}

void AssignmentApp::RenderFrame()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    if (*ListOfScenes[m_CurrSceneNum - 1]->GetDepthBuffer()) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }

    if (*ListOfScenes[m_CurrSceneNum - 1]->GetBackface()) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }
    else {
        glDisable(GL_CULL_FACE);
    }

    m_CurrScene = ListOfScenes[m_CurrSceneNum - 1];

    if (*ListOfScenes[m_CurrSceneNum - 1]->GetLighting()) {
        if (m_CurrSceneNum == 1) {
            glEnable(GL_NORMALIZE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glShadeModel(GL_SMOOTH);
            glEnable(GL_LIGHTING);
            glEnable(GL_COLOR_MATERIAL);
            lighting->ImmediateSpotLighting(*ListOfScenes[m_CurrSceneNum - 1]->GetNumLights());
        }
        else {
            glDisable(GL_NORMALIZE);
            glDisable(GL_BLEND);
            glDisable(GL_LIGHTING);
            glDisable(GL_COLOR_MATERIAL);
        }
    }
    else {
        glDisable(GL_NORMALIZE);
        glDisable(GL_BLEND);
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
    }

    m_CurrScene->Init();
    m_CurrScene->DrawAll(camera);

    RenderOSD();

    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        std::cout << "Error: " << err << std::endl;

    SDL_GL_SwapWindow(m_SDLWindow);
}

int AssignmentApp::Init()
{
    if (int err = RTRApp::Init() != 0) {
        return err;
    }

    gltInit();

    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_GetWindowSize(m_SDLWindow, &width, &height);
    SDL_WarpMouseInWindow(m_SDLWindow, width, height);

    // Instantiate all 6 scenes and store in an array/data struct
    RTRSceneBase* sceneOne = new RTRSceneOne(m_WindowWidth, m_WindowHeight, 
        VertexPointsAndNormals, faces, lighting);
    RTRSceneBase* sceneTwo = new RTRSceneTwo(m_WindowWidth, m_WindowHeight, 
        VertexPointsAndNormals, faces, lighting, sceneShader);
    RTRSceneBase* sceneThree = new RTRSceneThree(m_WindowWidth, m_WindowHeight, 
        VertexPointsAndNormals, faces, lighting, sceneShader);
    RTRSceneBase* sceneFour = new RTRSceneFour(m_WindowWidth, m_WindowHeight, 
        VertexPointsAndNormals, faces, lighting, sceneShader);
    RTRSceneBase* sceneFive = new RTRSceneFive(m_WindowWidth, m_WindowHeight, 
        VertexPointsAndNormals, faces, lighting, sceneShader);
    RTRSceneBase* sceneSix = new RTRSceneSix(m_WindowWidth, m_WindowHeight, 
        VertexPointsAndNormals, faces, lighting, sceneShader);

    ListOfScenes[0] = sceneOne;
    ListOfScenes[1] = sceneTwo;
    ListOfScenes[2] = sceneThree;
    ListOfScenes[3] = sceneFour;
    ListOfScenes[4] = sceneFive;
    ListOfScenes[5] = sceneSix;

    m_Resolution = std::to_string(width) + "x" + std::to_string(height);

    lighting->InstantiateImmediate();

    return 0;
}

void AssignmentApp::Done()
{
    gltTerminate();

    RTRApp::Done();

    ListOfScenes[0]->End();
    ListOfScenes[1]->End();
    ListOfScenes[2]->End();
    ListOfScenes[3]->End();
    ListOfScenes[4]->End();
    ListOfScenes[5]->End();

    ListOfScenes[0] = nullptr;
    ListOfScenes[1] = nullptr;
    ListOfScenes[2] = nullptr;
    ListOfScenes[3] = nullptr;
    ListOfScenes[4] = nullptr;
    ListOfScenes[5] = nullptr;
    m_CurrScene = nullptr;
    camera = nullptr;
}


static const char* MAIN_WINDOW_TITLE = "COSC1226 - Assignment 1";

int main(int argc, char** argv)
{
    AssignmentApp* app = new AssignmentApp(MAIN_WINDOW_TITLE, true);
    if (int err = app->Init() != 0) {
        std::cout << "RTR:ERROR: Failed to initialise application. Please see error messages for details..." << std::endl;
        return -1;
    };
    app->Run();
    app->Done();
    return 0;
}