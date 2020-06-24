//
// Created by nikwo on 02.06.2020.
//

#ifndef FOO_ENGINE_HPP
#define FOO_ENGINE_HPP

#include <GL/glew.h>
#include "GLFW//glfw3.h"
#include <vector>
#include "window.hpp"
#include "renderer.hpp"

namespace foo_engine {
    class fooE {
        window win;
        renderer ren;
        double delta_time, time;
    public:
        void init();
        fooE();
        ~fooE() = default;
        void configure_window(unsigned int w, unsigned int h, const char *name);
        void construct_window(GLFWmonitor *monitor, GLFWwindow *share);
        void configure_flags();
        bool main_cycle();
        static void clear();
        static void clear(glm::vec4 clear_color);
        void swap();
        void draw(const std::string &layer);
        void add_to_queue(const std::string &layer, int vao_id);
        void pop_from_queue(const std::string &layer, int vao_id);
        double get_delta_time();
    };
}
#endif //FOO_ENGINE_HPP
