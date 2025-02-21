#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION // stbi在本文件中编译
#include "stb_image.h"
#include <iostream>


Texture2D::Texture2D(const char *path) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(1); // 加载图片时翻转Y轴
    unsigned char *data = stbi_load(path, &width, &height, &channels,  0);
    if (data == nullptr) {
        std::cout << "Error: Failed to load texture: " << path << std::endl;
        return;
    }
    const GLint format = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
                 height, 0, format, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    // 如果纹理在使用中，出现了 采样超出范围、伸缩 等操作，但是没有设置相关参数，则opengl会拒绝渲染
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
}
