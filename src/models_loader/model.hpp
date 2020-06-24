//
// Created by nikwo on 24.06.2020.
//

#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <vector>
#include <assimp/material.h>
#include "../shader.hpp"
#include "mesh.hpp"
#include "assimp/scene.h"
#include "assimp/mesh.h"

namespace foo_engine{
    class model{
    public:
        model(const std::string &path);
        void draw(shader &shader_object);
    private:
        std::vector<mesh> meshes;
        std::string directory;
        std::vector<texture> textures_loaded;
        void load_model(const std::string &path);
        void process_node(aiNode *node, const aiScene *scene);
        mesh process_mesh(aiMesh *mesh_obj, const aiScene *scene);
        std::vector<texture> load_material_textures(aiMaterial *mat, aiTextureType type, std::string typeName);
    };
}

#endif //FOOENGINE_MODEL_HPP
