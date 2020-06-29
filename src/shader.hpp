//
// Created by nikwo on 24.06.2020.
//

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <GL/glew.h>
#include <glm.hpp>

namespace foo_engine {
    class shader {
    public:
        unsigned int id;
        shader(const char *vertexPath, const char *fragmentPath,  const char* geometryPath = nullptr);
        void use();
        void set_bool(const std::string &name, bool value) const;
        void set_integer(const std::string &name, int value) const;
        void set_float(const std::string &name, float value) const;
        void set_mat4(const std::string &name, const glm::mat4 &mat) const;
        void set_vec3(const std::string &name, const glm::vec3 &vec) const;
    private:
        void checkCompileErrors(GLuint shader, std::string type);
    };
}
#endif //FOOENGINE_SHADER_HPP
