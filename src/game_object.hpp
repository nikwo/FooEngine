//
// Created by nikwo on 02.06.2020.
//

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "glm.hpp"

namespace foo_engine{
    class game_object{
    protected:
        glm::vec3 position;
        GLint vao;
    public:
        game_object();
        ~game_object() = default;
        void translate();
        void rotate();

    };
}



#endif //GAME_OBJECT_HPP
