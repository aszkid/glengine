#version 150

uniform mat4 viewProjMat;

in vec3 vertex;
in vec2 _tex_coord;
in vec4 _color;

out vec2 tex_coord;
out vec4 color;

void main()
{
	tex_coord = _tex_coord;
	color = _color;
	gl_Position = viewProjMat * vec4(vertex,1.0);
}
