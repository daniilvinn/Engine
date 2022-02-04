#pragma once
#include <stb_image.h>

using TexID = unsigned int; // definition of texture id

class Texture {
private:
	TexID textureID;
	int width;
	int height;
	int channels;
	unsigned char* imageData;
	GLenum target;
public:
	Texture(GLenum target, GLenum type, const char* filepath) {
		this->target = target;
		imageData = stbi_load(filepath, &width, &height, &channels, 0);
		glGenTextures(1, &textureID);
		glBindTexture(target, textureID);
		glTexImage2D(target, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(target);
		STBI_FREE(imageData);
	}
	TexID getID() const {
		return textureID;
	}
	void bind() const {
		glBindTexture(target, textureID);
	};
	void unbind() const {
		glBindTexture(target, 0);
	};
};