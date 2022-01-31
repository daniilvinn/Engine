#pragma once

#include "Renderer.h"
#include "IndexBuffer.h"


// Changed param, it doesn't take "count" param anymore
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count, GLenum usage)
	: m_Count(count)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage));
}

IndexBuffer::~IndexBuffer() 
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned short int IndexBuffer::GetCount() const {
	return m_Count;
}