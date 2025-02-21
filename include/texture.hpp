#ifndef OPENGL_TEXTURE_HPP
#define OPENGL_TEXTURE_HPP

#include "glad/glad.h"

// 对纹理的设置作用于当前绑定的纹理，而非全局或当前纹理单元(sampler)
class Texture2D {
public:
    /*
     * default: GL_REPEAT
     * GL_
     *    REPEAT            重复      01|01|01
     *    MIRRORED_REPEAT   镜像      10|01|10
     *    CLAMP_TO_EDGE     拉伸      00|01|11
     *    CLAMP_TO_BORDER   填充      00|01|00
     */
    void setWrap(const GLint wrapX, const GLint wrapY, const GLfloat borderColor[4]) const {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapX);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapY);
        if ((wrapX == GL_CLAMP_TO_BORDER || wrapY == GL_CLAMP_TO_BORDER) && borderColor != nullptr)
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }

    /*
     * default: GL_NEAREST[_MIPMAP_NEAREST]
     * default: 开启多级渐远纹理（Mipmap）
     * GL_
     *    NEAREST                   邻近取样
     *    LINEAR                    线性取样
     *           _MIPMAP_           非必须；只对缩小(minify)有效，勿设置放大(magnify)
     *                   NEAREST    选用最接近的mipmap级别
     *                   LINEAR     在两个mipmap之间进行线性插值
     */
    void setFilter(const GLint minFilter, const GLint magFilter) const {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    }

    explicit Texture2D(const char *path);

    void bind(const GLuint sampler) const {
        // glActiveTexture只是声明了之后要绑定的纹理单元，只有调用glBindTexture后才真正生效
        glActiveTexture(GL_TEXTURE0 + sampler);
        glBindTexture(GL_TEXTURE_2D, id);
    }

    ~Texture2D() {
        glDeleteTextures(1, &id);
    }

private:
    GLuint id{};
};

#endif //OPENGL_TEXTURE_HPP
