#include "camera.hpp"

Camera::Camera(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up) {
    _forward = glm::normalize(direction);
    _right = glm::normalize(glm::cross(_forward, up));
    _up = glm::cross(_right, _forward);
    _position = position;

    _view = glm::mat4(_right.x, _up.x, -_forward.x, 0.0f,
                      _right.y, _up.y, -_forward.y, 0.0f,
                      _right.z, _up.z, -_forward.z, 0.0f,
                      -glm::dot(_right, position), -glm::dot(_up, position), glm::dot(_forward, position), 1.0f);

    _projection = glm::mat4();
}

void Camera::calcTranslate() {
    _view[3][0] = -glm::dot(_right, _position);
    _view[3][1] = -glm::dot(_up, _position);
    _view[3][2] = glm::dot(_forward, _position);
}

void Camera::getAxisFromRotMat() {
    _right = glm::vec3(_view[0][0], _view[1][0], _view[2][0]);
    _up = glm::vec3(_view[0][1], _view[1][1], _view[2][1]);
    _forward = glm::vec3(-_view[0][2], -_view[1][2], -_view[2][2]);
}