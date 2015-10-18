#version 430

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 uniformColor;

out vec4 vertColor;
uniform mat4 worldMatrix;

void main()
{
    gl_Position = worldMatrix * vec4(position, 0, 1);
	vertColor = vec4(uniformColor, 1);
}