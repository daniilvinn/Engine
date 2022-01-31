#pragma once
// TODO: all of below declared stuff
// more of TODO:
// Needed to create a comfortable creating character object
// DONE: simplify texture loading

#define VEenum GLenum

typedef bool VEint; // my own GL-like typedef :)) VE = Vinnik Engine :D
typedef unsigned int TEXid; // definition of texture id

class Texture {
private:
	TEXid textureID;
	int width;
	int height;
	int channels;
	unsigned char* imageData;
	GLenum target;
public:
	Texture(GLenum target, VEenum type, const char* filepath) {
		this->target = target;
		imageData = stbi_load(filepath, &width, &height, &channels, 0);
		glGenTextures(1, &textureID);
		glBindTexture(target, textureID);
		glTexImage2D(target, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(target);
		STBI_FREE(imageData);
	}
	TEXid getID() const {
		return textureID;
	}
	void bind() const {
		glBindTexture(target, textureID);
	};
	void unbind() const {
		glBindTexture(target, 0);
	};
};