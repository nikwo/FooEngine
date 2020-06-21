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
    public:
        void init();
        fooE();
        ~fooE() = default;
        void configure_window(unsigned int w, unsigned int h, const char *name);
        void construct_window(GLFWmonitor *monitor, GLFWwindow *share);
        void configure_flags();
        bool main_cycle();
        static void clear();
        void swap();
        void draw(const std::string &layer);
    };
}
#endif //FOO_ENGINE_HPP
