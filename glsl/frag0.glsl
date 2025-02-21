#version 330 core
in vec2 _texpos;

out vec4 color;

uniform sampler2D tex0;
uniform sampler2D tex1;

void main() {
    color = mix(texture(tex0, _texpos), texture(tex1, _texpos), 0.8);
}