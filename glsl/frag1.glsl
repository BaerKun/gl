#version 330 core
out vec4 fragColor;

uniform vec3 ambientLight;

void main() {
    vec3 objectColor = vec3(1.0, 0.0, 0.0);
    fragColor = vec4(objectColor * ambientLight, 1.0);
}