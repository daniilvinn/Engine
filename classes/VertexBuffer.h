#pragma once

#include <GL/glew.h>

class VertexBuffer{
private:
	unsigned int m_RendererID;
public:
	// Constructor and Destructor
	VertexBuffer(const void* data, unsigned int size, GLenum usage);
	~VertexBuffer();

	// Other methods
	void Bind() const;
	void Unbind() const;
};