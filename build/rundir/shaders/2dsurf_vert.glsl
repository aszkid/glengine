#version 150

in vec2 position;

uniform mat4 viewProjMatrix;

void main()
{
	gl_Position = viewProjMatrix * vec4(position, 0.0, 1.0);
}
