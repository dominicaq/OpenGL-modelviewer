#include "Window.h"
#include "stb_image.h"

#include <iostream>

void Window::CreateWindow(const char *title, int width = 800, int height = 600)
{
    glfwInit();
    monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    wnd = glfwCreateWindow(mode->width, mode->height, title, monitor, NULL);
    if (wnd == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    GLFWimage images[1]; 
    images[0].pixels = stbi_load("appicon.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
    glfwSetWindowIcon(wnd, 1, images);
    stbi_image_free(images[0].pixels);

    glfwMakeContextCurrent(wnd);
    glfwSetWindowUserPointer(wnd, this);
    glfwSetWindowSizeCallback(wnd, Window::CallbackResize);

    monitor = glfwGetPrimaryMonitor();
    glfwGetWindowSize(wnd, &wndSize[0], &wndSize[1]);
    glfwGetWindowPos(wnd, &wndPos[0], &wndPos[1]);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
    }

    // ImGui Setup
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(wnd, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    updateViewport = true;
}

void Window::Update()
{
    if (updateViewport)
    {
        glfwGetFramebufferSize(wnd, &vpSize[0], &vpSize[1]);
        glViewport(0, 0, vpSize[0], vpSize[1]);
        updateViewport = false;
    }

    // ..... render the scene
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(wnd);
    glfwPollEvents();
}

void Window::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(wnd);
}

void Window::CallbackResize(GLFWwindow* window, int cx, int cy)
{
    void* ptr = glfwGetWindowUserPointer(window);
    if (Window* wndPtr = static_cast<Window*>(ptr))
        wndPtr->Resize(cx, cy);
}

void Window::Resize(int cx, int cy)
{
    updateViewport = true;
}

bool Window::IsFullscreen(void)
{
    return glfwGetWindowMonitor(wnd) != nullptr;
}

void Window::SetFullScreen(bool fullscreen)
{
    if (IsFullscreen() == fullscreen)
        return;

    if (fullscreen)
    {
        // backup window position and window size
        glfwGetWindowPos(wnd, &wndPos[0], &wndPos[1]);
        glfwGetWindowSize(wnd, &wndSize[0], &wndSize[1]);

        // get resolution of monitor
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        // switch to full screen
        glfwSetWindowMonitor(wnd, monitor, 0, 0, mode->width, mode->height, wndRefreshRate);
    }
    else
    {
        // restore last window size and position
        glfwSetWindowMonitor(wnd, nullptr, wndPos[0], wndPos[1], wndSize[0], wndSize[1], 0);
    }

    updateViewport = true;
}

void Window::SetRefreshRate(int newRate)
{
    wndRefreshRate = newRate;
}