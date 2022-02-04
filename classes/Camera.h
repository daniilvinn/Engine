#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum EnumCameraDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

namespace Engine {
	class Camera {
	private:
		static glm::vec2 m_Position;
		static float m_CameraMovementSpeed;
	public:
		static glm::mat4 GetProjectionViewMatrix();
		static glm::mat4 GetViewMatrix();
		static glm::vec2 GetPosition();
		static void SetPosition(const glm::vec2& position);
		static float GetCameraMovementSpeed();
		static void SetCameraMovementSpeed(float speed);
		static void ProcessKeyboard(EnumCameraDirection direction);
	};
}