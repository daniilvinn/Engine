#pragma once

#include <GL/glew.h>
#include <vector>

struct BufferLayoutAttribute {
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned short GetSizeOfType(GLenum type) {
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}

		__debugbreak();

		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<BufferLayoutAttribute> m_Attributes;
	unsigned int m_Stride;
public:
	// Constructor and destructor
	VertexBufferLayout()
		: m_Stride(0) {}

	// push-back functions implementation
	template <typename T>
	void Push(unsigned int count) {
		static_assert(false);
	}

	template <>
	void Push<float>(unsigned int count) {
		m_Attributes.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += BufferLayoutAttribute::GetSizeOfType(GL_FLOAT) * count;
	}

	template <>
	void Push<unsigned int>(unsigned int count) {
		m_Attributes.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += BufferLayoutAttribute::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template <>
	void Push<char>(unsigned int count) {
		m_Attributes.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
		m_Stride += BufferLayoutAttribute::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<BufferLayoutAttribute>& GetAttributes() const {
		return m_Attributes;
	}

	inline unsigned int GetStride() const {
		return m_Stride;
	}
};

