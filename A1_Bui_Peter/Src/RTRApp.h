//-----------------------------------------------------------------------------
// RTRApp.h
//-----------------------------------------------------------------------------
// Assignment 1 Starter Code
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <sdl/SDL.h>
#include <stb/stb_image.h>

class RTRApp
{
public:
    RTRApp(const char* title, bool fullscreen = false, int width = 1024, int height = 768);
    virtual int Init();
    virtual void Done();
    void Run();
    virtual bool Tick(unsigned int td_milli) {
        std::cout << "RTRApp::Tick()" << std::endl;
        return true;
    }

protected:
    std::string m_MainWindowTitle;
    bool m_FullScreen;
    int m_WindowWidth;
    int m_WindowHeight;
    int m_ScreenWidth;
    int m_ScreenHeight;
    SDL_Window* m_SDLWindow;
    SDL_Renderer* m_SDLRenderer;
    SDL_GLContext m_GLContext;
};
