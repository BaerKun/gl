#ifndef GL_CAMERA_HPP
#define GL_CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    explicit Camera(const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
                    const glm::vec3 &direction = glm::vec3(0.0f, 0.0f, -1.0f),
                    const glm::vec3 &up = glm::vec3(0.0f, 1.0f, 0.0f));

    void use();

    void setProjection(float aspectRatio, float radiusOfView);

    glm::mat4 getMatrix(bool useProjection = true) const;

    void lookAt(const glm::vec3 &target);

    void move(float x, float y, float z);

    void moveTo(const glm::vec3 &target);

    void rotate(float pitch, float yaw, float roll);

private:
    glm::vec3 position;
    glm::vec3 front, right, up;
    glm::mat4 view, projection;
};

#endif //GL_CAMERA_HPP
