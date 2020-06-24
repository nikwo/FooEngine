//
// Created by nikwo on 24.06.2020.
//

#include <glm.hpp>
#include <ext.hpp>
#include "camera.hpp"

foo_engine::camera::camera(glm::vec3 _position) {
    position = _position;
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = YAW;
    pitch = PITCH;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    movement_speed = SPEED;
    world_up = up;
    mouse_sensitivity = SENSITIVITY;
    zoom = ZOOM;
    update_camera_vectors();
}

void foo_engine::camera::update_camera_vectors() {
    glm::vec3 _front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, world_up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up    = glm::normalize(glm::cross(right, front));
}

glm::mat4 foo_engine::camera::get_view_matrix() {
    return glm::lookAt(position, position + front, up);
}
