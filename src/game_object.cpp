//
// Created by nikwo on 02.06.2020.
//

#include <ext.hpp>
#include <GL/glew.h>
#include "game_object.hpp"

foo_engine::game_object::game_object() {
    position = glm::vec3(0, 0, 0);
    rotation_direction = glm::vec3(0,0,0);
    model_3d = nullptr;
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

glm::mat4 foo_engine::game_object::translate() {
    glm::mat4 model;
    model = glm::translate(model, position);
    return model;
}

glm::mat4 foo_engine::game_object::rotate(GLfloat angle) {
    glm::mat4 model;
    model = glm::rotate(model, angle, rotation_direction);
}

void foo_engine::game_object::send_data_to_gpu() {

    // передача данных с матрицами модели, проекции, вида в обработку графическим процессором
    // так как положение вертексов самой модели не меняется, а меняется лишь их глобальное положение и поворот,
    // то vbo будет создаваться лишь один раз при инициализации объекта с учетом его потребностей(текстуры, нормали и тд)

}

void foo_engine::game_object::load_model(const std::string &path) {
    model_3d = new model(path);
}

