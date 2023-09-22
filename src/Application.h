#ifndef APPLICATION_H
#define APPLICATION_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <memory>

#include "../gameobject/Camera.h"
#include "GameTime.h"
#include "Window.h"

class Application
{
public:
	Application();
	~Application();
	void run();
private:
	std::unique_ptr<Window> _currentWindow;
};
#endif