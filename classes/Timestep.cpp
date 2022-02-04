#include "Timestep.h"
#include <GLFW/glfw3.h>

float Engine::Timestep::m_DeltaTime = 0.0f;
float Engine::Timestep::m_LastFrame = 0.0f;

void Engine::Timestep::onUpdate() 
{
	float currentFrame = glfwGetTime();
	m_DeltaTime = currentFrame - m_LastFrame;
	m_LastFrame = currentFrame;
}

float Engine::Timestep::Delta()
{
	return m_DeltaTime;
}
