#ifndef DISPLAY_H
#define DISPLAY_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "Vendor/imgui/imgui_impl_opengl3.h"
#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui_impl_glfw.h"

#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Display
{
public:
	Display(const char* name, int width, int height, int refreshRate);
	void InitDisplay();
	void Update();
	
	Display& Get();
	void setFullScreen();
	bool IsClosed();
	~Display();

private:
	const char* m_name;
	GLFWwindow* m_window;
	
	int m_refreshRate;
	float m_width, m_height;
	float m_aspectRatio;

	bool m_isFullScreen;
};
#endif