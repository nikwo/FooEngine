//
// Created by nikwo on 02.06.2020.
//

#include <ext.hpp>
#include "src/foo_engine.hpp"
#include "src/models_loader/model.hpp"
#include "src/camera.hpp"

using namespace foo_engine;

int main(int argc, char* argv[]){
    fooE engine = fooE();
    engine.init();
    engine.configure_window(1024, 720, "window");
    engine.construct_window(nullptr, nullptr);
    shader s = shader("../src/shaders/default_vertical.glsl",
            "../src/shaders/default_fragmental.glsl");
    model m = model("/home/nikwo/Downloads/nanosuit/nanosuit.obj");
    camera cam = camera(glm::vec3(0,0,0));
// #TODO: убрать отладочный код
    while(engine.main_cycle()){
        fooE::clear(glm::vec4(0.5f, 0.3f, 0.6f, 1.0f));
        glm::mat4 projection = glm::perspective(glm::radians(cam.zoom), (float)1024 / (float)720, 0.1f, 100.0f);
        s.use();
        glm::mat4 view = cam.get_view_matrix();
        s.set_mat4("projection", projection);
        s.set_mat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.7f, -10.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));	// it's a bit too big for our scene, so scale it down
        model = glm::rotate(model, 3.14f * (float)glfwGetTime(), glm::vec3(0, 1.0f, 0));
        s.set_mat4("model", model);

        GLfloat light0_diffuse[] = {0.4, 0.7, 0.2};
        GLfloat light0_direction[] = {0.0, 0.0, 1.0, 0.0};
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);

        m.draw(s);
        engine.swap();
        glfwPollEvents();
    }
}
