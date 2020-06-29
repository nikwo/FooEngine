#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec2 _uv;
out vec3 fragment_pos;
out vec3 _normal;

void main(){
    _uv = uv;
    _normal = mat3(transpose(inverse(model))) * normal;
    fragment_pos = vec3(model * vec4(position, 1.0));
    gl_Position = projection * view * vec4(fragment_pos, 1.0);
}