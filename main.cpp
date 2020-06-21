//
// Created by nikit on 02.06.2020.
//

#include "src/foo_engine.hpp"

using namespace foo_engine;

int main(int argc, char* argv[]){
    fooE engine = fooE();
    engine.init();
    engine.configure_window(1024, 720, "window");
    engine.construct_window(nullptr, nullptr);
    while(engine.main_cycle()){
        engine.clear();
        engine.swap();
        glfwPollEvents();
    }
}
