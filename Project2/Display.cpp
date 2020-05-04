#include "Display.h"

#include <iostream>

Display::Display(const char* name, int width, int height, int refreshRate = 60)
{
    this->m_name = name;
    this->m_width = width;
    this->m_height = height;
    this->m_aspectRatio = float(width) / (float)height;

    InitDisplay();
}

void Display::InitDisplay()
{
    glfwInit();
    //glfwGetPrimaryMonitor() // fullscreen
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    m_window = glfwCreateWindow(mode->width, mode->height, m_name, NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        Display::~Display();
    }
    glfwMakeContextCurrent(m_window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        Display::~Display();
    }

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    // ImGui Setup
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Display::Update()
{
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Display::setFullScreen()
{
    glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, m_width, m_height, m_refreshRate);
}

bool Display::IsClosed()
{
    return glfwWindowShouldClose(m_window);
}

Display::~Display()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}