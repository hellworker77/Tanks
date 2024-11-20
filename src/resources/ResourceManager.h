//
// Created by iljap on 11/19/2024.
//
#pragma once
#ifndef BATTLECITY_RESOURCEMANAGER_H
#define BATTLECITY_RESOURCEMANAGER_H

#include <string>
#include <memory>
#include <map>
#include "../Logger/Logger.h"

namespace Renderer{
    class ShaderProgram;
    class Texture2D;
}


class ResourceManager {
public:
    explicit ResourceManager(const std::string& executablePath);
    ~ResourceManager() = default;


    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName,
                                                         const std::string& vertexPath,
                                                         const std::string& fragmentPath);

    std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);

    std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& relativePath);
    std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);

private:
    [[nodiscard]] std::string readFromFile(const std::string& relativePath) const;

    Logger& m_logger = Logger::getInstance();
    std::string m_resPath;

    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
    ShaderProgramMap m_shaderPrograms;

    typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
    TexturesMap m_textures;

};


#endif //BATTLECITY_RESOURCEMANAGER_H
