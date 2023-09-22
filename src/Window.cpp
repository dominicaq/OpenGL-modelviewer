#include "Window.h"
#include "stb_image.h" // app icon

// Callback(s)
// -----------------------------------------------------------------------------
void Window::resizeCallback(GLFWwindow* window, int cx, int cy) {
    void* ptr = glfwGetWindowUserPointer(window);
    if (Window* wndPtr = static_cast<Window*>(ptr)) {
        wndPtr->resizeWindow(cx, cy);
    }
}

// Core window functionality
// -----------------------------------------------------------------------------
Window::Window(const char* title, int width, int height) {
    if (!glfwInit()) {
        std::cerr << "ERROR: Failed to initialize GLFW\n";
        return;
    }

     // Initialize GLFW window hints
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    _target_monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(_target_monitor);
    _window = glfwCreateWindow(
        mode->width,
        mode->height,
        title,
        _target_monitor,
        NULL
    );

    // Check if window creation succeeded
    if (_window == NULL) {
        std::cerr << "ERROR: Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    // Make the OpenGL context of this window current
    glfwMakeContextCurrent(_window);

    // Initialize GLEW (after making the context current)
    if (glewInit() != GLEW_OK) {
        std::cerr << "ERROR: Failed to initialize GLEW\n";
        glfwTerminate();
        return;
    }

    // Initialize ImGui
    if (!ImGui::CreateContext()) {
        std::cerr << "ERROR: Failed to create ImGui context\n";
        return;
    }

    // Initialize ImGui for GLFW and OpenGL
    if (!ImGui_ImplGlfw_InitForOpenGL(_window, true)) {
        std::cerr << "Failed to initialize ImGui for GLFW and OpenGL\n";
        return;
    }

    // Initialize ImGui for OpenGL 3+
    if (!ImGui_ImplOpenGL3_Init("#version 330")) {
        std::cerr << "Failed to initialize ImGui for OpenGL 3+\n";
        return;
    }

    // Set window icon
    GLFWimage window_icon[1];
    window_icon[0].pixels = stbi_load(
        "appicon.png", 
        &window_icon[0].width, 
        &window_icon[0].height, 
        0, 
        4
    );
    if (window_icon[0].pixels == nullptr) {
        std::cout << "ERROR: Failed to load window icon\n";
    } else {
        glfwSetWindowIcon(_window, 1, window_icon);
        stbi_image_free(window_icon[0].pixels);
    }

    // Set context
    glfwMakeContextCurrent(_window);
    glfwSetWindowUserPointer(_window, this);
    glfwSetWindowSizeCallback(_window, Window::resizeCallback);

    // Get window size
    glfwGetWindowSize(_window, &_window_size[0], &_window_size[1]);
    glfwGetWindowPos(_window, &_window_position[0], &_window_position[1]);

    // Update next tick
    _update_view_port = true;
}

Window::~Window() {
    // ImGui cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
}

void Window::update() {
    if (_update_view_port) {
        glfwGetFramebufferSize(_window, &_viewport_size[0], &_viewport_size[1]);
        glViewport(0, 0, _viewport_size[0], _viewport_size[1]);
        _update_view_port = false;
    }

    // Render IMGUI
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(_window);
}

void Window::resizeWindow(int cx, int cy) {
    // TODO
    _update_view_port = true;
}

bool Window::isFullscreen() {
    return glfwGetWindowMonitor(_window) != nullptr;
}

void Window::setFullScreen() {
    // Check if the current window mode is already fullscreen
    if (isFullscreen()) {
        return; // No need to change anything
    }

    // Backup window position and window size
    glfwGetWindowPos(_window, &_window_position[0], &_window_position[1]);
    glfwGetWindowSize(_window, &_window_size[0], &_window_size[1]);

    // Get the resolution of the target monitor
    const GLFWvidmode* mode = glfwGetVideoMode(_target_monitor);

    // Switch to fullscreen
    glfwSetWindowMonitor(
        _window,
        _target_monitor,
        0,
        0,
        mode->width,
        mode->height,
        _refresh_rate
    );

    // Check if we are actually in fullscreen mode after the switch
    if (!isFullscreen()) {
        // Failed to make fullscreen, restore last window size and position
        glfwSetWindowMonitor(
            _window,
            nullptr, // Set monitor to nullptr to return to windowed mode
            _window_position[0],
            _window_position[1],
            _window_size[0],
            _window_size[1],
            0
        );
    }

    // Update the viewport if needed
    _update_view_port = true;
}
