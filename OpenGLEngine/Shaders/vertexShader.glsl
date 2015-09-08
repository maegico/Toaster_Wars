#version 430

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;

out vec4 vertColor;

void main()
{
    gl_Position = vec4(position, 0, 1);
	vertColor = vec4(color, 1);
}