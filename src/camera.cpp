#include "camera.hpp"

Camera::Camera(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up) {
    forward_ = glm::normalize(direction);
    right_ = glm::normalize(glm::cross(forward_, up));
    up_ = glm::cross(right_, forward_);
    position_ = position;

    view_ = glm::mat4(right_.x, up_.x, -forward_.x, 0.0f,
                      right_.y, up_.y, -forward_.y, 0.0f,
                      right_.z, up_.z, -forward_.z, 0.0f,
                      -glm::dot(right_, position), -glm::dot(up_, position), glm::dot(forward_, position), 1.0f);

    projection_ = glm::mat4();
}

inline void Camera::calcTranslate() {
    view_[3][0] = -glm::dot(right_, position_);
    view_[3][1] = -glm::dot(up_, position_);
    view_[3][2] = glm::dot(forward_, position_);
}

inline void Camera::getAxisFromRotMat() {
    right_ = glm::vec3(view_[0][0], view_[1][0], view_[2][0]);
    up_ = glm::vec3(view_[0][1], view_[1][1], view_[2][1]);
    forward_ = glm::vec3(-view_[0][2], -view_[1][2], -view_[2][2]);
}

void Camera::moveTo(const glm::vec3 &position) {
    position_ = position;
    calcTranslate();
}

// radians
void Camera::rotate(const glm::vec3 &axis, const float angle) {
    view_ = glm::rotate(view_, angle, axis);
    getAxisFromRotMat();
    calcTranslate();
}

// (right, up, forward)
void Camera::move(const glm::vec3 &offset) {
    moveTo(position_ + offset.x * right_ + offset.y * up_ + offset.z * forward_);
}

void Camera::lookAt(const glm::vec3 &position, const glm::vec3 &up) {
    view_ = glm::lookAt(position_, position, up);
    getAxisFromRotMat();
}