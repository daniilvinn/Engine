#pragma once

#include "Shader.h"
#include "Renderer.h"

unsigned int Shader::getID() const {
	return m_RendererID;
}

void Shader::Bind() const {
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(NULL);
}

unsigned int Shader::getUniformLoc(const char* uniform) const {
	glUseProgram(m_RendererID);
	return glGetUniformLocation(m_RendererID, uniform);
}

void Shader::setUniform1i(const char* uniform, int value) {
	glUseProgram(m_RendererID);
	GLCall(glUniform1i(glGetUniformLocation(m_RendererID, uniform), value));
}

void Shader::setUniform1f(const char* uniform, float value) {
	glUseProgram(m_RendererID);
	GLCall(glUniform1f(glGetUniformLocation(m_RendererID, uniform), value));
}

void Shader::setUniformMat4(const char* uniform, const float* value) {
	glUseProgram(m_RendererID);
	GLCall(glUniformMatrix4fv(glGetUniformLocation(m_RendererID, uniform), 1, GL_FALSE, value));
};

void Shader::setUniformVec3(const char* uniform, const float* value) {
	glUseProgram(m_RendererID);
	GLCall(glUniform3fv(glGetUniformLocation(m_RendererID, uniform), 1, value));
}

void Shader::ParseShaderFile(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	ShaderType type = ShaderType::NONE;

	std::string line;
	std::stringstream ss[2];
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	source.VertexSource = ss[0].str();
	source.FragmentSource = ss[1].str();
}




// compiling and if needed logging errors while compiling
unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int validatingResult;
	glGetShaderiv(id, GL_COMPILE_STATUS, &validatingResult);
	if (validatingResult == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout <<
			"Failed to compile a " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

// making it all (vertex and fragment) together into one
void Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	m_RendererID = program;
}

Shader::Shader(const std::string& filepath) {
	ParseShaderFile(filepath);
	CreateShader(source.VertexSource, source.FragmentSource);
}