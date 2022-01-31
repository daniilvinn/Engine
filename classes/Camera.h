#pragma once
static const float DEFAULT_YAW = -90.0f;
static const float DEFAULT_PITCH = 0.0f;
static const float DEFAULT_SPEED = 2.5f;
static const float DEFAULT_SENSIVITY = 0.1f;


enum VE_CAMERA_PHYSICAL_DIRECTION {
	FORWARD,
	BACKWARD, 
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera {
private:
	glm::vec3 Position;
	glm::vec3 FrontDirection;
	glm::vec3 RightDirection;
	glm::vec3 UpDirection;
	float yaw;
	float pitch;
	float MovementSpeed;
	float MouseSensitivity;
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float YAW = DEFAULT_YAW, float PITCH = DEFAULT_PITCH);
	glm::mat4 getViewMatrix() const;
	void processKeyboard(VE_CAMERA_PHYSICAL_DIRECTION direction, float deltaTime);
	void processMouseCallback(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void setMouseSensivity(float value);
	void setCameraMovementSpeed(float value);
	glm::vec3 getPosition() const;
private:
	void updateVectors();
};

Camera::Camera(glm::vec3 position_p, float yaw_p, float pitch_p) {
	Position = position_p;
	yaw = yaw_p;
	pitch = pitch_p;
	MovementSpeed = DEFAULT_SPEED;
	MouseSensitivity = DEFAULT_SENSIVITY;
	updateVectors();
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(Position, Position + FrontDirection, UpDirection);
}

void Camera::updateVectors() {
	glm::vec3 temporaryFrontVector;
	temporaryFrontVector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	temporaryFrontVector.y = sin(glm::radians(pitch));
	temporaryFrontVector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	FrontDirection = glm::normalize(temporaryFrontVector);
	RightDirection = glm::normalize(glm::cross(FrontDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
	UpDirection = glm::normalize(glm::cross(RightDirection, FrontDirection));
}

void Camera::processKeyboard(VE_CAMERA_PHYSICAL_DIRECTION direction, float deltaTime){
	float velocity = MovementSpeed * deltaTime;
	float tempY = FrontDirection.y;
	FrontDirection.y = 0.0f;
	if (direction == FORWARD) {
		Position += glm::normalize(FrontDirection) * velocity;
	}
	if (direction == BACKWARD) {
		Position -= glm::normalize(FrontDirection) * velocity;
	}
	if (direction == LEFT) {
		Position -= glm::normalize(RightDirection) * velocity;
	}
	if (direction == RIGHT) {
		Position += glm::normalize(RightDirection) * velocity;
	}
	if (direction == UP) {
		Position.y += velocity;
	}
	if (direction == DOWN) {
		Position.y -= velocity;
	}
	FrontDirection.y = tempY;
}

void Camera::processMouseCallback(float xoffset, float yoffset, GLboolean constrainPitch) {
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;
	yaw += xoffset;
	pitch += yoffset;
	if (constrainPitch) {
		if (pitch > 89.0f) pitch = 89.0f;
		if (pitch < -89.0f) pitch = -89.0f;
	}

	updateVectors();
}

void Camera::setMouseSensivity(float value) {
	MouseSensitivity = value;
}

void Camera::setCameraMovementSpeed(float value) {
	MovementSpeed = value;
}

glm::vec3 Camera::getPosition() const {
	return Position;
};