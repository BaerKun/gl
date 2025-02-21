#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texpos;

out vec2 _texpos;

void main(){
    gl_Position = vec4(pos, 1.0);
    _texpos = texpos;
}