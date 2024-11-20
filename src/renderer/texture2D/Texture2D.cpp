//
// Created by iljap on 11/20/2024.
//

#include "Texture2D.h"

Renderer::Texture2D::Texture2D(const int width,const int height, const unsigned char *data, const unsigned int channels,
                               const GLint filter, const GLint wrapMode): m_width(width), m_height(height) {
    if(channels == 4){
        m_mode = GL_RGBA;
    }

    glGenTextures(1, &m_ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Renderer::Texture2D::Texture2D(Renderer::Texture2D &&texture2D) noexcept {
    m_ID = texture2D.m_ID;

    texture2D.m_ID = 0;

    m_mode = texture2D.m_mode;
    m_width = texture2D.m_width;
    m_height = texture2D.m_height;
}

Renderer::Texture2D::~Texture2D() {
    glDeleteTextures(1, &m_ID);
}

Renderer::Texture2D &Renderer::Texture2D::operator=(Renderer::Texture2D &&texture2D) {
    glDeleteTextures(1, &m_ID);
    m_ID = texture2D.m_ID;

    texture2D.m_ID = 0;

    m_mode = texture2D.m_mode;
    m_width = texture2D.m_width;
    m_height = texture2D.m_height;

    return *this;
}

void Renderer::Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, m_ID);
}
