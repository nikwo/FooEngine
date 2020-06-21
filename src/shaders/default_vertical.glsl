#version 330 core

uniform mat4 camera;

in vec3 position;
in vec2 uv;
in vec4 color;

out vec2 _uv;
out vec4 _color;

void main(){
    _uv = uv;
    _color = color;
    gl_Position = camera * vec4(position, 1);
}