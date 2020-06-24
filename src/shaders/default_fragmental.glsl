#version 330 core

uniform sampler2D texture2D;

in vec2 _uv;

out vec4 result_color;

void main(){
    result_color = texture(texture2D, _uv);
}