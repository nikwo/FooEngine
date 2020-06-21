//
// Created by nikwo on 02.06.2020.
//

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GLFW/glfw3.h>
#include "game_object.hpp"
#include <queue>
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
        std::queue<layer> render_queue;
    };
}

#endif //RENDERER_HPP
