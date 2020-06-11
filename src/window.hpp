//
// Created by nikit on 02.06.2020.
//

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include "GLFW/glfw3.h"
#include <GL/gl.h>

namespace foo_engine{
    class window{
        GLFWwindow *glfwWindow;
        std::string name;
        unsigned int width, height;
    public:
        window() = default;
        window(unsigned int w, unsigned int h, const std::string &name);
        ~window();
        void construct(GLFWmonitor *monitor, GLFWwindow *share);
        bool working();
        void swap();
        void clear();
    };
}

#endif //WINDOW_HPP
