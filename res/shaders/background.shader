#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 modelMatrix;

out vec2 textureCoord;

void main() {
	textureCoord = texCoord;
	gl_Position = modelMatrix * vec4(position, 1.0f);
}

#shader fragment
#version 460 core

in vec2 textureCoord;
out vec4 fragmentColor;
uniform sampler2D u_Sampler2D;

void main() {
	fragmentColor = texture(u_Sampler2D, textureCoord);
}