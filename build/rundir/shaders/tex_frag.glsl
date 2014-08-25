#version 150

in vec2 texCoord;

out vec4 outCol;

uniform sampler2D tex;

void main() {
	outCol = texture(tex, texCoord);
	//outCol = vec4(texCoord.x, texCoord.y, 0, 1);
}
