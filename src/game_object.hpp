//
// Created by nikwo on 02.06.2020.
//

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "models_loader/model.hpp"

namespace foo_engine{
    class game_object{
    protected:
        glm::vec3 position;
        glm::vec3 rotation_direction;
        glm::vec3 scale;
        model *model_3d;
    public:
        game_object();
        ~game_object() = default;
        glm::mat4 translate();
        glm::mat4 rotate(GLfloat angle);
        void set_position(glm::vec3 _position);
        void set_rotation_direction(glm::vec3 _rotation_direction);
        void load_model(const std::string &path);
        void send_data_to_gpu();
    };
}



#endif //GAME_OBJECT_HPP
