#ifndef GL_CAMERA_HPP
#define GL_CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    explicit Camera(const glm::vec3 &position = glm::vec3(0, 0, 4),
                    const glm::vec3 &direction = glm::vec3(0, 0, -1),
                    const glm::vec3 &up = glm::vec3(0, 1, 0));

    void setOrthogonal(const float width, const float height, const float near, const float far) {
        projection_ = glm::ortho(-width / 2, width / 2, -height / 2, height / 2, near, far);
    }

    /*
     * fov: 视野(field of view, 单位: 角度)
     * aspect: 宽高比
     */
    void setPerspective(const float fov, const float aspect, const float near, const float far) {
        projection_ = glm::perspective(glm::radians(fov), aspect, near, far);
    }

    glm::mat4 getMatrix() const {
        return projection_ * view_;
    }

    void moveTo(const glm::vec3 &position);

    // radians
    void rotate(const glm::vec3 &axis, float angle);

    // (right, up, forward)
    void move(const glm::vec3 &offset);

    void lookAt(const glm::vec3 &position, const glm::vec3 &up = glm::vec3(0, 1, 0));

private:
    // 从view矩阵的旋转部分中获取相机坐标轴
    inline void getAxisFromRotMat();

    // 由坐标轴和相机位置计算view的平移部分
    inline void calcTranslate();

    glm::vec3 forward_, up_, right_;
    glm::vec3 position_;
    glm::mat4 view_, projection_;
};

#endif //GL_CAMERA_HPP
