#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddVertexBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) const;

	void Bind() const;
	void Unbind() const;
};