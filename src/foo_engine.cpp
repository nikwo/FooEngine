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
    glEnable(GL_DEPTH_TEST);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void foo_engine::fooE::swap() {
    glfwSwapBuffers(win.get_window());
}

void foo_engine::fooE::draw(const std::string &layer) {
    if(layer.find("all")){
        for(auto it = ren.render_queue.begin(); it <= ren.render_queue.end(); ++it){
            for(auto vao : it->vaos){
                glBindVertexArray(vao);
                // здесь меняем матрицы модели и вида
                // затем отрисовываем
                glBindVertexArray(0);
            }
        }
    }
    else if(layer.find("UI")){
        for(auto it = ren.render_queue.begin(); it <= ren.render_queue.end(); ++it){
            if(it->name.find("UI")){
                for(auto vao : it->vaos){
                    glBindVertexArray(vao);
                    // здесь меняем матрицы модели и вида
                    // затем отрисовываем только пользовательский интерфейс
                    glBindVertexArray(0);
                }
                break;
                //выход из цикла по итератору
            }
        }
    }
}

void foo_engine::fooE::add_to_queue(const std::string &layer, int vao_id) {
    for(auto it = ren.render_queue.begin(); it <= ren.render_queue.end(); ++it){
        if(it->name.find(layer)){
            bool unique_vao = true;
            for(auto vao : it->vaos){
                if(vao == vao_id) {
                    unique_vao = false;
                    break;
                }
            }
            if(!unique_vao)
                break;
            else it->vaos.push_back(vao_id);
            break;
        }
    }
}

void foo_engine::fooE::pop_from_queue(const std::string &layer, int vao_id) {
    for(auto it = ren.render_queue.begin(); it <= ren.render_queue.end(); ++it){
        if(it->name.find(layer)){
            for(auto vao_it = it->vaos.begin(); vao_it <= it->vaos.end(); ++vao_it) {
                if (*vao_it == vao_id) {
                    it->vaos.erase(vao_it);
                }
                break;
            }
        }
    }
}
