//
// Created by nikwo on 24.06.2020.
//

#include <iostream>
#include <stb_image_aug.h>
#include "model.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

foo_engine::model::model(const std::string &path) {
    load_model(path);
}

void foo_engine::model::draw(foo_engine::shader &shader_object) {
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw(shader_object);
}

void foo_engine::model::load_model(const std::string &path) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    process_node(scene->mRootNode, scene);
}

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

std::vector<foo_engine::texture>
foo_engine::model::load_material_textures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    std::vector<texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            texture _texture;
            _texture.id = TextureFromFile(str.C_Str(), this->directory, false);
            _texture.type = typeName;
            _texture.path = str.C_Str();
            textures.push_back(_texture);
            textures_loaded.push_back(_texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

foo_engine::mesh foo_engine::model::process_mesh(aiMesh *mesh_obj, const aiScene *scene) {
    std::vector<vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<texture> textures;

    for(unsigned int i = 0; i < mesh_obj->mNumVertices; i++)
    {
        vertex _vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh_obj->mVertices[i].x;
        vector.y = mesh_obj->mVertices[i].y;
        vector.z = mesh_obj->mVertices[i].z;
        _vertex.position = vector;
        // normals
        vector.x = mesh_obj->mNormals[i].x;
        vector.y = mesh_obj->mNormals[i].y;
        vector.z = mesh_obj->mNormals[i].z;
        _vertex.normal = vector;
        // texture coordinates
        if(mesh_obj->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh_obj->mTextureCoords[0][i].x;
            vec.y = mesh_obj->mTextureCoords[0][i].y;
            _vertex.texture_coords = vec;
        }
        else
            _vertex.texture_coords = glm::vec2(0.0f, 0.0f);
        // tangent
        vector.x = mesh_obj->mTangents[i].x;
        vector.y = mesh_obj->mTangents[i].y;
        vector.z = mesh_obj->mTangents[i].z;
        _vertex.tangent = vector;
        // bitangent
        vector.x = mesh_obj->mBitangents[i].x;
        vector.y = mesh_obj->mBitangents[i].y;
        vector.z = mesh_obj->mBitangents[i].z;
        _vertex.bitangent = vector;
        vertices.push_back(_vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh_obj->mNumFaces; i++)
    {
        aiFace face = mesh_obj->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh_obj->mMaterialIndex];

    // 1. diffuse maps
    std::vector<texture> diffuseMaps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<texture> specularMaps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<texture> normalMaps = load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<texture> heightMaps = load_material_textures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return mesh(vertices, indices, textures);
}

void foo_engine::model::process_node(aiNode *node, const aiScene *scene) {
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process_mesh(mesh, scene));
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        process_node(node->mChildren[i], scene);
    }
}
