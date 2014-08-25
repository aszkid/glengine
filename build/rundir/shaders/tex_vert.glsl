#version 150

in vec2 pos;
in vec2 _texCoord;

out vec2 texCoord;

layout(location = 1) uniform mat4 viewProjMat;

void main() {
	texCoord = _texCoord;
	gl_Position = viewProjMat * vec4(pos, 0.0, 1.0);
}
