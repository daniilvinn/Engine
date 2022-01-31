#pragma once

class IndexBuffer{
private:
	unsigned int m_RendererID;
	unsigned short int m_Count;
public:
	// Constructor and Destructor
	IndexBuffer(const unsigned int* data, unsigned int count,GLenum usage);
	~IndexBuffer();

	// Other methods
	void Bind() const;
	void Unbind() const;
	unsigned short int GetCount() const; 
};