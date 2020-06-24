//
// Created by nikwo on 24.06.2020.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vec3.hpp>

#define YAW -90.0f
#define PITCH 0.0f
#define SPEED 2.5f
#define SENSITIVITY 0.1f
#define ZOOM 45.0f

namespace foo_engine{
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };
    class camera{
    public:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 world_up;

        float yaw;
        float pitch;

        float movement_speed;
        float mouse_sensitivity;
        float zoom;
        explicit camera(glm::vec3 position);
        glm::mat4 get_view_matrix();
    private:
        void update_camera_vectors();
    };
}

#endif //FOOENGINE_CAMERA_HPP
