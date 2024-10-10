#version 330 core

in vec3 vecColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(vecColor, 1.0f);
}