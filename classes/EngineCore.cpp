#include "EngineCore.h"

#include <Camera.h>

#include <Timestep.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

void EngineCore::onUpdate()
{
	Engine::Timestep::onUpdate();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void EngineCore::handleEvents(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Engine::Camera::ProcessKeyboard(UP);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Engine::Camera::ProcessKeyboard(LEFT);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Engine::Camera::ProcessKeyboard(DOWN);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Engine::Camera::ProcessKeyboard(RIGHT);
	}
}
