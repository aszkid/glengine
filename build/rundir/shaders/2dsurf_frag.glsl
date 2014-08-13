#version 150

out vec4 outColor;
uniform vec4 surfColor;

void main()
{
	outColor = vec4(surfColor);
}
