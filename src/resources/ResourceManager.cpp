//
// Created by iljap on 11/19/2024.
//

#include "ResourceManager.h"
#include "../renderer/ShaderProgram.h"
#include "../renderer/texture2D/Texture2D.h"
#include <sstream>
#include <fstream>


#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"


ResourceManager::ResourceManager(const std::string &executablePath) {
    size_t last = executablePath.find_last_of("/\\");
    m_resPath = executablePath.substr(0, last);
}

std::string ResourceManager::readFromFile(const std::string &relativePath) const {
    std::ifstream file;
    file.open(m_resPath + "/" + relativePath, std::ios::binary);

    if(!file.is_open())
    {
        m_logger.warning("Failed to open file: " + relativePath);
        return std::string {};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram>
ResourceManager::loadShaders(const std::string &shaderName,
                             const std::string &vertexPath,
                             const std::string &fragmentPath) {
    std::string vertexString = readFromFile(vertexPath);

    if(vertexPath.empty()){
        m_logger.warning("No vertex shader!");
        return nullptr;
    }

    m_logger.info("Vertex shader loaded");

    std::string fragmentString = readFromFile(fragmentPath);

    if(fragmentPath.empty()){
        m_logger.warning("No fragment shader!");
        return nullptr;
    }

    m_logger.info("Fragment shader loaded");

    std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderPrograms
            .emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString))
            .first->second;

    if(!newShader->getIsCompiled()){
        m_logger.warning("Can't load shader program.");
        return nullptr;
    }

    return newShader;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string &shaderName) {
    auto it = m_shaderPrograms.find(shaderName);

    if(it != m_shaderPrograms.end()){
        return it->second;
    }

    m_logger.warning("Can't find shader program: " + shaderName);
    return nullptr;
}

std::shared_ptr<Renderer::Texture2D>
ResourceManager::loadTexture(const std::string &textureName, const std::string &relativePath) {
    int channels = 0;
    int width = 0;
    int height = 0;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* pixels = stbi_load(std::string(m_resPath+ "/" + relativePath).c_str(), &width, &height, &channels, 0);

    if(!pixels){
        m_logger.warning("Can't load texture");
        return nullptr;
    }

    std::shared_ptr<Renderer::Texture2D> newTexture = m_textures
            .emplace(textureName, std::make_shared<Renderer::Texture2D>(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE))
            .first->second;

    stbi_image_free(pixels);

    return newTexture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::getTexture(const std::string &textureName) {
    auto it = m_textures.find(textureName);

    if(it != m_textures.end()){
        return it->second;
    }

    m_logger.warning("Can't find texture : " + textureName);
    return nullptr;
}
