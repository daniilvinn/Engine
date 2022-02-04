#include "Camera.h"
#include <Timestep.h>

#define DEFAULT_CAMERA_MOVEMENT_SPEED 300.0f;

glm::vec2 Engine::Camera::m_Position = glm::vec2(0.0f, 0.0f);
float Engine::Camera::m_CameraMovementSpeed = DEFAULT_CAMERA_MOVEMENT_SPEED;

glm::mat4 Engine::Camera::GetProjectionViewMatrix()
{
	static glm::mat4 projectionMatrix = glm::ortho(
		-1920.0f / 2,
		 1920.0f / 2,
		-1080.0f / 2,
		 1080.0f / 2,
		 1.0f,
		-1.0f
	);

	glm::mat4 CameraMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 0.0f));

	return projectionMatrix * CameraMatrix;
}

void Engine::Camera::ProcessKeyboard(EnumCameraDirection direction)
{
	switch (direction)
	{
	case UP:
		m_Position.y -= 1.0f * Engine::Timestep::Delta() * m_CameraMovementSpeed;
		break;
	case DOWN:
		if (m_Position.y < 0.0f) { m_Position.y += 1.0f * Engine::Timestep::Delta() * m_CameraMovementSpeed; };
		break;
	case LEFT:
		m_Position.x += 1.0f * Engine::Timestep::Delta() * m_CameraMovementSpeed;
		break;
	case RIGHT:
		m_Position.x -= 1.0f * Engine::Timestep::Delta() * m_CameraMovementSpeed;
		break;
	default:
		break;
	}
	
}

glm::mat4 Engine::Camera::GetViewMatrix()
{
	return glm::mat4();
}

glm::vec2 Engine::Camera::GetPosition()
{
	return m_Position;
}

void Engine::Camera::SetPosition(const glm::vec2& position)
{
	m_Position = position;
}

float Engine::Camera::GetCameraMovementSpeed()
{
	return m_CameraMovementSpeed;
}

void Engine::Camera::SetCameraMovementSpeed(float speed)
{
	m_CameraMovementSpeed = speed;
}
