//
// Created by nikit on 02.06.2020.
//

#include <iostream>
#include "window.hpp"

using namespace foo_engine;

window::window(unsigned int w, unsigned int h, const std::string &n) {
    width = w;
    height =h;
    name = n;
    glfwWindow = nullptr;
}

window::~window() {
    glfwDestroyWindow(glfwWindow);
}

void window::construct(GLFWmonitor *monitor, GLFWwindow *share) {
    glfwWindow = glfwCreateWindow(width, height, name.data(), monitor, share);
    if(!glfwWindow)
    {
        std::cerr << "Failed to open GLFW window\n";
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(glfwWindow);
}

bool window::working() {
    return !glfwWindowShouldClose(glfwWindow);
}
