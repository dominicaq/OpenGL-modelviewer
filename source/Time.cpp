#include "Time.h"
#include "GLFW/glfw3.h"

float Time::m_deltaTime;
float Time::m_lastFrame;

void Time::Update()
{
	// Delta time
	float currentFrame = glfwGetTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;
}

float Time::deltaTime()
{
	return m_deltaTime;
}