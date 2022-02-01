#shader vertex
#version 460 core

layout(location = 0) in vec3 position;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main() {
	gl_Position = projectionMatrix * modelMatrix *vec4(position, 1.0f);
}

#shader fragment
#version 460 core

out vec4 fragmentColor;

void main() {
	fragmentColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}