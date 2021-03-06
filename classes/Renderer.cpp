#pragma once

#include "Renderer.h"
#include <iostream>

void GLClearErrorBuffer() 
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) 
{
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): ";
		std::cout << function << "\n " << file << ": " << line << std::endl;
		return false;
	}
	return true;
}

namespace Engine {
	void Renderer::Draw(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader)
	{
		shader.Bind();
		VAO.Bind();
		IBO.Bind();

		glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Engine::Renderer::DrawQuad()
	{
		
	}
}