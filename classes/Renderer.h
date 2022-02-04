#pragma once

#define ASSERT(call) if(!(call)) __debugbreak();
#define GLCall(call) GLClearErrorBuffer();	\
		call;								\
		ASSERT(GLLogCall(#call, __FILE__, __LINE__))

#include <iostream>
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <Graphics.h>
#include <vector>

void GLClearErrorBuffer(); 
bool GLLogCall(const char* function, const char* file, int line);

namespace Engine {

	static struct RenderData {
		float m_Positions[8] = {
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f,
			-1.0f,  1.0f
		};
	};
	class Renderer {
	private:
		RenderData s_Data;
	public:
		static void Draw(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader);
		static void Clear();
		static void SetBackgroundTexture();
		static void DrawQuad();
	};

}