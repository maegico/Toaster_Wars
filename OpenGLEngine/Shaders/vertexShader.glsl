#version 430

layout (location = 0) in vec3 position;
//layout (location = 1) in vec2 vecTexUV;
//layout (location = 2) in vec3 vecNorm;

//out vec2 fragTexUV;
//out vec3 fragPos;
//out vec3 fragNorm;

uniform mat4 worldMatrix;

void main()
{
	//fragTexUV = vecTexUV;
	//gl_Position = viewMatrix * worldMatrix * vec4(position, 1));
    gl_Position = worldMatrix * vec4(position, 1);
	//gl_Position = vec4(position, 1);
	//fragPos = glPosition.xyz;
			//what?
	//fragNorm = normalize(vecNorm); //*rotation
}