#ifndef GL_CAMERA_HPP
#define GL_CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    explicit Camera(const glm::vec3 &position = glm::vec3(0, 0, 4),
                    const glm::vec3 &direction = glm::vec3(0, 0, -1),
                    const glm::vec3 &up = glm::vec3(0, 1, 0));

    void setOrtho(const float width, const float height, const float near, const float far) {
        _projection = glm::ortho(-width / 2, width / 2, -height / 2, height / 2, near, far);
    }

    /*
     * fov: 视野(field of view, 单位: 角度)
     * aspect: 宽高比
     */
    void setPerspective(const float fov, const float aspect, const float near, const float far) {
        _projection = glm::perspective(glm::radians(fov), aspect, near, far);
    }

    glm::mat4 getMatrix() const {
        return _projection * _view;
    }

    void moveTo(const glm::vec3 &position) {
        _position = position;
        calcTranslate();
    }

    // radians
    void rotate(const glm::vec3 &axis, const float angle) {
        _view = glm::rotate(_view, angle, axis);
        getAxisFromRotMat();
        calcTranslate();
    }

    // (right, up, forward)
    void move(const glm::vec3 &offset) {
        moveTo(_position + offset.x * _right + offset.y * _up + offset.z * _forward);
    }

    void lookAt(const glm::vec3 &position, const glm::vec3 &up = glm::vec3(0, 1, 0)) {
        _view = glm::lookAt(_position, position, up);
        getAxisFromRotMat();
    }

private:
    // 从view矩阵的旋转部分中获取相机坐标轴
    void getAxisFromRotMat();

    // 由坐标轴和相机位置计算view的平移部分
    void calcTranslate();

    glm::vec3 _forward, _up, _right;
    glm::vec3 _position;
    glm::mat4 _view, _projection;
};

#endif //GL_CAMERA_HPP
