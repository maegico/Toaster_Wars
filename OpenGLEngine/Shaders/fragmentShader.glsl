#version 430

uniform vec4 uniformColor;
in vec4 vertColor;

void main()
{
	gl_FragColor = vec4(uniformColor * vertColor);
}