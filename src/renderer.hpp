//
// Created by nikwo on 02.06.2020.
//

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GLFW/glfw3.h>
#include "game_object.hpp"

namespace foo_engine{
    class renderer{
    public:
        renderer();
        ~renderer()=default;
        void clear();
        void draw();
    };
}

#endif //RENDERER_HPP
