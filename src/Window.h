#ifndef WINDOW_H
#define WINDOW_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <array>
#include <stdexcept>
#include <iostream>

// ImGui
#include "Vendor/imgui/imgui_impl_opengl3.h"
#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui_impl_glfw.h"

class Window {
public:
    Window(const char* title, int width, int height);
    ~Window();

    // Callback(s)
    static void resizeCallback(GLFWwindow* window, int cx, int cy);
    
    void update();
    bool shouldClose();
    bool isFullscreen(void);
    void setFullScreen();

private:
    // Window & viewport dimensons: { x, y }
    std::array< int, 2 > _window_position { 0, 0 };
    std::array< int, 2 > _window_size { 0, 0 };
    std::array< int, 2 > _viewport_size { 0, 0 };

    // Window properties
    bool _is_fullscreen = false;
    int _refresh_rate = 60;
    GLFWwindow* _window = nullptr;
    GLFWmonitor* _target_monitor = nullptr;

    bool _update_view_port = true;
    void resizeWindow(int cx, int cy);
};
#endif