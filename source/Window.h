#ifndef WINDOW_H
#define WINDOW_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <array>
#include <stdexcept>

#include "Vendor/imgui/imgui_impl_opengl3.h"
#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui_impl_glfw.h"

class Window
{
private:
    int wndRefreshRate = 60;
    std::array< int, 2 > wndPos{ 0, 0 };
    std::array< int, 2 > wndSize{ 0, 0 };
    std::array< int, 2 > vpSize{ 0, 0 };
    bool                 updateViewport = true;
    GLFWwindow* wnd = nullptr;
    GLFWmonitor* monitor = nullptr;

    void Resize(int cx, int cy);

public:

    void CreateWindow(const char* title, int width, int height);
    static void CallbackResize(GLFWwindow* window, int cx, int cy);
    void Update();
    bool ShouldClose();
    bool IsFullscreen(void);
    void SetFullScreen(bool fullscreen);
    void SetRefreshRate(int newRate);

    void CleanUp();
};
#endif