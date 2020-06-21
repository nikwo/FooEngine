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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(1);
    }

    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    monitor_w = mode->width;
    monitor_h = mode->height;
    glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
}

bool window::working() {
    return !glfwWindowShouldClose(glfwWindow);
}

GLFWwindow *window::get_window() {
    return glfwWindow;
}
