#pragma once
#include <GLFW/glfw3.h>

class EngineCore {
public:
	static void onUpdate();
	static void handleEvents(GLFWwindow* window);
};