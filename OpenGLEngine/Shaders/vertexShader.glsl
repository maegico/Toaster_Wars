#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 vecTexUV;
layout (location = 2) in vec3 vecNorm;

out vec2 fragTexUV;
out vec3 fragPos;
out vec3 fragNorm;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	gl_Position = viewMatrix * modelMatrix * vec4(position, 1);

	fragTexUV = vecTexUV;
	fragPos = gl_Position.xyz;
	fragNorm = normalize(vecNorm);
}