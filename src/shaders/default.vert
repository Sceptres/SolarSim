#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vecColorIn;

out vec3 vecColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool isDebug;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    if(!isDebug) {
        vecColor = vecColorIn;
    } else {
        vecColor = vec3(0.0, 0.0, 0.0);
    }
}