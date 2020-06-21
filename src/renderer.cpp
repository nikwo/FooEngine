//
// Created by nikwo on 02.06.2020.
//

#include "renderer.hpp"

foo_engine::renderer::renderer() {
    //default renderer layers
    render_queue.emplace_back(foo_engine::layer("world_space"));
    render_queue.emplace_back(foo_engine::layer("UI"));
}
