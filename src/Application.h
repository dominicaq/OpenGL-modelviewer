#ifndef APPLICATION_H
#define APPLICATION_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "GameObject/Camera.h"
#include "GameTime.h"
#include "Window.h"

class Application
{
public:
	Application();
	void Run();
	void HandleEvents();
private:
	Window currentWindow;
};
#endif