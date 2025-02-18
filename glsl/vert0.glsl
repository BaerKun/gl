#version 330 core
layout (location = 0) in vec3 pos;
out vec4 color;

uniform vec3 color_;

void main(){
    gl_Position = vec4(pos, 1.0);
    color = vec4(color_, 1.0);
}