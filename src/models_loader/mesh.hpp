//
// Created by nikwo on 24.06.2020.
//

#ifndef MESH_HPP
#define MESH_HPP

#include <glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include "../shader.hpp"

namespace foo_engine {
    struct vertex{
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texture_coords;
    };
    struct texture{
        GLuint id;
        std::string type;
    };
    class mesh {
    public:
        std::vector<vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<texture> textures;
        mesh(std::vector<vertex> _vertices, std::vector<GLuint> _indices, std::vector<texture> _textures);
        void draw(shader &shader_object);
    private:
        GLuint vao, vbo, ebo;
        void setup_mesh();
    };
}
#endif //FOOENGINE_MESH_HPP
