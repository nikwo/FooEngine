//
// Created by nikwo on 02.06.2020.
//

#include <iostream>
#include "foo_engine.hpp"

foo_engine::fooE::fooE() {

}

void foo_engine::fooE::init() {
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void foo_engine::fooE::configure_window(unsigned int w, unsigned int h, const char *name) {
    win = window(w, h, name);
}

void foo_engine::fooE::construct_window(GLFWmonitor *monitor, GLFWwindow *share) {
    win.construct(monitor, share);
}

bool foo_engine::fooE::main_cycle() {
    return win.working();
}

void foo_engine::fooE::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void foo_engine::fooE::swap() {
    glfwSwapBuffers(win.get_window());
}
