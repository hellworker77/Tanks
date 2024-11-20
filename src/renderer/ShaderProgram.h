//
// Created by iljap on 11/18/2024.
//
#pragma once
#ifndef BATTLECITY_SHADERPROGRAM_H
#define BATTLECITY_SHADERPROGRAM_H
#include <string>
#include <glad/glad.h>
#include "../Logger/Logger.h"

namespace Renderer {
    class ShaderProgram {
    public:

        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
        ~ShaderProgram();
        [[nodiscard]] bool getIsCompiled() const {return m_isCompiled;}
        void use() const;
        void setInt(const std::string& name, const GLint value) const;

    private:

        bool createShader(const std::string& source, GLenum shaderType, GLuint& shaderID);
        bool m_isCompiled = false;
        GLuint m_ID = 0;
        Logger& m_logger = Logger::getInstance();

    public:
        ShaderProgram() = delete;
        ShaderProgram(ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
    };

}


#endif //BATTLECITY_SHADERPROGRAM_H
