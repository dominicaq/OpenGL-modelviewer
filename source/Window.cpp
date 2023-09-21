#include "Window.h"
#include "stb_image.h"

#include <iostream>

void Window::CreateWindow(const char *title, int width = 800, int height = 600) {
    glfwInit();
    _target_monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(_target_monitor);

    _window = glfwCreateWindow(mode->width, mode->height, title, _target_monitor, NULL);
    if (_window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    GLFWimage images[1]; 
    images[0].pixels = stbi_load("appicon.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
    glfwSetWindowIcon(_window, 1, images);
    stbi_image_free(images[0].pixels);

    glfwMakeContextCurrent(_window);
    glfwSetWindowUserPointer(_window, this);
    glfwSetWindowSizeCallback(_window, Window::CallbackResize);

    _target_monitor = glfwGetPrimaryMonitor();
    glfwGetWindowSize(_window, &wndSize[0], &wndSize[1]);
    glfwGetWindowPos(_window, &wndPos[0], &wndPos[1]);

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return;
    }

    // ImGui Setup
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    _update_view_port = true;
}

void Window::Update()
{
    if (_update_view_port) {
        glfwGetFramebufferSize(_window, &vpSize[0], &vpSize[1]);
        glViewport(0, 0, vpSize[0], vpSize[1]);
        _update_view_port = false;
    }

    // ..... render the scene
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(_window);
    glfwPollEvents();
}

void Window::CleanUp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(_window);
}

void Window::CallbackResize(GLFWwindow* window, int cx, int cy)
{
    void* ptr = glfwGetWindowUserPointer(window);
    if (Window* wndPtr = static_cast<Window*>(ptr)) {
        wndPtr->resizeWindow(cx, cy);
    }
}

void Window::resizeWindow(int cx, int cy) {
    _update_view_port = true;
}

bool Window::IsFullscreen(void)
{
    return glfwGetWindowMonitor(_window) != nullptr;
}

void Window::SetFullScreen(bool fullscreen)
{
    if (IsFullscreen() == fullscreen) {
        return;
    }

    if (fullscreen) {
        // Backup window position and window size
        glfwGetWindowPos(_window, &wndPos[0], &wndPos[1]);
        glfwGetWindowSize(_window, &wndSize[0], &wndSize[1]);

        // Get resolution of target monitor
        const GLFWvidmode* mode = glfwGetVideoMode(_target_monitor);

        // Switch to full screen
        glfwSetWindowMonitor(
            _window, 
            _target_monitor, 
            0, 
            0, 
            mode->width, 
            mode->height, 
            _refresh_rate
        );
    }
    else {
        // restore last window size and position
        glfwSetWindowMonitor(_window, nullptr, wndPos[0], wndPos[1], wndSize[0], wndSize[1], 0);
    }

    _update_view_port = true;
}

void Window::SetRefreshRate(int new_rate) {
    _refresh_rate = new_rate;
}