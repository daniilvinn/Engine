#pragma once

#include <fstream>
#include <sstream>
#include <iostream>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
	unsigned int m_RendererID;
	ShaderProgramSource source;
	void ParseShaderFile(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	void CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
public:
	Shader(const std::string& filepath);
	unsigned int getID() const;
	void Bind() const;
	void Unbind() const;
	unsigned int getUniformLoc(const char* uniform) const;
	void setUniform1i(const char* uniform, int value);
	void setUniform1f(const char* uniform, float value);
	void setUniformMat4(const char* uniform, const float* value);
	void setUniformVec3(const char* uniform, const float* value);
};