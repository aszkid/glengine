#version 150

in vec4 bg_color;
in vec2 position;
uniform mat4 viewProjMatrix;

out vec4 _color;

void main()
{
	_color = bg_color;
	gl_Position = viewProjMatrix * vec4(position, 0.0, 1.0);
}
