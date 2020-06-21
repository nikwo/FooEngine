#version 330 core

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

in vec3 position;
in vec2 uv;
in vec4 color;

out vec2 _uv;
out vec4 _color;

void main(){
    _uv = uv;
    _color = color;
    gl_Position = projection * view * model * vec4(position, 1.0);
}