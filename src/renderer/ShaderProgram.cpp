//
// Created by iljap on 11/18/2024.
//

#include "ShaderProgram.h"

namespace Renderer{
    Renderer::ShaderProgram::ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader) {
        GLuint vertexShaderID;

        if(!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)){
            return;
        }

        GLuint fragmentShaderID;
        if(!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)){
            glDeleteShader(vertexShaderID);
            return;
        }

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShaderID);
        glAttachShader(m_ID, fragmentShaderID);
        glLinkProgram(m_ID);

        GLint success;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);

        if(!success){
            GLchar infoLog[1024];
            glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
            m_logger.warning(infoLog);
        }else{
            m_isCompiled = true;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

    }

    bool ShaderProgram::createShader(const std::string &source, const GLenum shaderType, GLuint &shaderID) {
        shaderID = glCreateShader(shaderType);
        const char* code = source.c_str();
        glShaderSource(shaderID, 1, &code, nullptr);
        glCompileShader(shaderID);

        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if(!success){
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            m_logger.warning(infoLog);

            return false;
        }

        return true;
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_ID);
    }

    void ShaderProgram::use() const {
        glUseProgram(m_ID);
    }

    ShaderProgram::ShaderProgram(ShaderProgram &&shaderProgram) noexcept{
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;
        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;
    }

    ShaderProgram &ShaderProgram::operator=(ShaderProgram &&shaderProgram) noexcept{
        glDeleteProgram(m_ID);
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;
        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;

        return *this;
    }

    void ShaderProgram::setInt(const std::string &name, const GLint value) const {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }
}
