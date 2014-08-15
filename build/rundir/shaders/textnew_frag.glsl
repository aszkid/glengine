#version 150

uniform sampler2D _tex;

in vec2 tex_coord;
in vec4 color;

void main()
{
    float a = texture(_tex, tex_coord.xy).r;
    gl_FragColor = vec4(color.rgb, color.a*a);
}
