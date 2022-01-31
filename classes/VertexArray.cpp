#pragma once

#include "VertexArray.h"
#include "Renderer.h"


VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddVertexBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) const
{
	Bind();
	vbo.Bind();
	const auto& attributes = layout.GetAttributes();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < attributes.size(); i++) {
		const auto& attrib = attributes[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalized, layout.GetStride(), (const void*)offset));
		offset += attrib.count * BufferLayoutAttribute::GetSizeOfType(attrib.type);
	}
	Unbind();
}

void VertexArray::Bind() const 
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}