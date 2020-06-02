//
// Created by nikit on 02.06.2020.
//

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <string>
#include "GLFW/glfw3.h"

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
    };
}

#endif //WINDOW_HPP
