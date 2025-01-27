//
// Created by nikwo on 02.06.2020.
//

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "game_object.hpp"
#include <string>
#include <vector>

namespace foo_engine{
    class layer{
    public:
        std::string name;
        std::vector<int> vaos;
        explicit layer(const std::string &n){
            name = n;
        }
    };

    class renderer{
    public:
        renderer();
        ~renderer()=default;
        std::vector<layer> render_queue;
    };
}

#endif //RENDERER_HPP
