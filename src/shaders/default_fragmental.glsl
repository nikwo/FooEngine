#version 330 core

struct material {
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    float shininess;
};


struct light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec2 _uv;
in vec3 fragment_pos;
in vec3 _normal;

uniform vec3 view_pos;
uniform material mat;
uniform light l;

out vec4 result_color;

void main(){
    vec3 ambient = l.ambient + texture(mat.texture_diffuse, _uv).rgb;

    vec3 norm = normalize(_normal);
    vec3 light_dir = normalize(l.position - fragment_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = l.diffuse * diff * texture(mat.texture_diffuse, _uv).rgb;

    vec3 viewDir = normalize(view_pos - fragment_pos);
    vec3 reflectDir = reflect(-light_dir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
    vec3 specular = l.specular * spec * texture(mat.texture_specular, _uv).rgb;
    result_color = vec4(ambient + diffuse + specular, 1.0);
}