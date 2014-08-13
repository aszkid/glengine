#version 150

out vec4 outColor;

flat in vec4 color;

void main()
{
	outColor = vec4(color);
}
