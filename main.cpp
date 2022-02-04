#include "includes.h"

#define WINDOW_WIDTH 1920.0f
#define WINDOW_HEIGHT 1080.0f

GLfloat vertex[] = {			// background mapping
	-960.0f, -545.0f,	0.0f,		0.0f, 0.0f,
	 960.0f, -545.0f,	0.0f,		1.0f, 0.0f,
	 960.0f,  545.0f,	0.0f,		1.0f, 1.0f,
	-960.0f,  545.0f,	0.0f,		0.0f, 1.0f
};

GLuint index[] = {
	0, 1, 2,
	2, 3, 0
};


GLfloat quadVertex[] = {	
	// square mapping
	-50.0f, -50.0f,	-1.0f,	
	 50.0f, -50.0f,	-1.0f, 
	 50.0f,  50.0f,	-1.0f,
	-50.0f,  50.0f,	-1.0f
};


int main() {

#pragma region SETUP
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "OpenGL", NULL, NULL);

	if (!window) {
		std::cout << "ERROR_GLFW: failed to create window!" << std::endl;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR_GLEW: failed to initialize GLEW!" << std::endl;
	};
#pragma endregion
	

	stbi_set_flip_vertically_on_load(true);
	Texture backgroundTexture(GL_TEXTURE_2D, GL_RGB, "res/textures/worldbackground.png");

	// VBO, IBO, VAO for Background Image
	VertexBuffer VBO(vertex, sizeof(vertex), GL_STATIC_DRAW);
	IndexBuffer IBO(index, 6, GL_STATIC_DRAW);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	VertexArray VAO;
	VAO.AddVertexBuffer(VBO, layout);

	// VBO, IBO, VAO for cube
	VertexBuffer quadVBO(quadVertex, sizeof(quadVertex), GL_STATIC_DRAW);
	IndexBuffer quadIBO(index, 6, GL_STATIC_DRAW);
	VertexBufferLayout quadLayout;
	quadLayout.Push<float>(3);
	VertexArray quadVAO;
	quadVAO.AddVertexBuffer(quadVBO, quadLayout);

	// Shaders to render objects
	Shader mainShader("res/shaders/main.shader");				// Main shader, accepts MVP matrix (currently only MP)
	Shader backgroundShader("res/shaders/background.shader");	// Accepts only projection matrix

	glm::mat4 projectionMatrix = glm::ortho(
		-WINDOW_WIDTH / 2.0f, 
		WINDOW_WIDTH / 2.0f, 
		-WINDOW_HEIGHT / 2.0f,
		WINDOW_HEIGHT / 2.0f, 
		1.0f, 
		-1.0f);
	
#pragma region imgui setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460 core");
#pragma endregion
	
	while (!glfwWindowShouldClose(window)) {
		Engine::Renderer::Clear();
		EngineCore::onUpdate();
		EngineCore::handleEvents(window);

		glm::mat4 modelMatrix = glm::mat4(1.0f);

		backgroundTexture.bind();
		backgroundShader.setUniformMat4("modelMatrix", glm::value_ptr(Engine::Camera::GetProjectionViewMatrix()));
		Engine::Renderer::Draw(VAO, IBO, backgroundShader); 
		backgroundTexture.unbind();
		
#pragma region imgui
		static float moveCoordX;
		static float moveCoordY;
		ImGui::Begin("Window");
			ImGui::SliderFloat("Move X position", &moveCoordX, -960.0f, 960.0f);
			ImGui::SliderFloat("Move Y position", &moveCoordY, -540.0f, 540.0f);
		ImGui::End();
#pragma endregion
		
		modelMatrix = glm::translate(modelMatrix, glm::vec3(moveCoordX, moveCoordY, 0.0f));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-Engine::Camera::GetPosition(), 0.0f));
		mainShader.setUniformMat4("modelMatrix", glm::value_ptr(modelMatrix));
		mainShader.setUniformMat4("projectionMatrix", glm::value_ptr(Engine::Camera::GetProjectionViewMatrix()));
		Engine::Renderer::Draw(quadVAO, quadIBO, mainShader);


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	glDeleteProgram(mainShader.getID());
	glDeleteProgram(backgroundShader.getID());
	glfwTerminate();
	return 0;
}