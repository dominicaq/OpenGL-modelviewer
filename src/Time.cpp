#include "GameTime.h"
#include "GLFW/glfw3.h"

float GameTime::m_deltaTime;
float GameTime::m_lastFrame;

void GameTime::Update()
{
	// Delta time
	float currentFrame = glfwGetTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;
}

float GameTime::deltaTime()
{
	return m_deltaTime;
}