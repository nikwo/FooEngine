//
// Created by nikwo on 24.06.2020.
//

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

namespace foo_engine {
    class shader {
    public:
        unsigned int id;
        shader(const char *vertexPath, const char *fragmentPath);
        void use();
        void set_bool(const std::string &name, bool value) const;
        void set_integer(const std::string &name, int value) const;
        void set_float(const std::string &name, float value) const;
    };
}
#endif //FOOENGINE_SHADER_HPP
