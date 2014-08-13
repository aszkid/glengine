#version 150

in vec2 position;
in vec4 surfColor;

flat out vec4 color;

uniform mat4 viewProjMatrix;

void main()
{
	color = surfColor;
	gl_Position = viewProjMatrix * vec4(position, 0.0, 1.0);
}
