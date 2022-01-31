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

void GLClearErrorBuffer(); 
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
	void Draw(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader) const;
};