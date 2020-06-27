#version 330 core

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

in vec2 _uv;

out vec4 result_color;

void main(){
    result_color = texture(texture_diffuse, _uv);
}