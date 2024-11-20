//
// Created by iljap on 11/20/2024.
//

#pragma once
#ifndef BATTLECITY_TEXTURE2D_H
#define BATTLECITY_TEXTURE2D_H


#include "glad/glad.h"

namespace Renderer{
    class Texture2D {
    public:
        Texture2D(int width,
                  int height,
                  const unsigned char* data,
                  unsigned channels = 4,
                  const GLint filter = GL_NEAREST,
                  const GLint wrapMode = GL_CLAMP_TO_EDGE);

        Texture2D(Texture2D&& texture2D) noexcept;
        Texture2D& operator=(Texture2D&& texture2D);

        ~Texture2D();

        void bind() const;
    private:
        GLuint m_ID;
        GLint m_mode = GL_RGB;
        int m_width;
        int m_height;
    public:
        Texture2D() = delete;
        Texture2D(Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;
    };

}

#endif //BATTLECITY_TEXTURE2D_H
