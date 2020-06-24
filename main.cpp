//
// Created by nikwo on 02.06.2020.
//

#include "src/foo_engine.hpp"

using namespace foo_engine;

int main(int argc, char* argv[]){
    fooE engine = fooE();
    engine.init();
    engine.configure_window(1024, 720, "window");
    engine.construct_window(nullptr, nullptr);
    while(engine.main_cycle()){
        fooE::clear(glm::vec4(0.5f, 0.3f, 0.6f, 1.0f));
        engine.swap();
        glfwPollEvents();
    }
}
