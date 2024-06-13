#pragma once

#include <vector>
#include <tuple>
#include <glad/glad.h>
#include <string>
#include <glm/vec2.hpp>
#include <iostream>
#include <stb/stb_image.h>

struct TextureParam
{
public:
    /// @brief
    GLenum paramName;

    /// @brief
    GLenum value;

    /// @brief
    /// @param paramName
    /// @param value
    TextureParam(GLenum paramName, GLenum value);

    /// @brief
    /// @param pair
    TextureParam(std::tuple<GLenum, GLenum> pair);
};

class Texture
{
public:
    /// @brief
    /// @param textureTargetType
    /// @param params
    /// @param texture_path
    /// @param texture_unit
    Texture(GLenum texture_target_type, const std::vector<TextureParam> &params, const std::string &texture_path, GLenum texture_unit);

    /// @brief
    /// @param textureTargetType
    /// @param params
    /// @param texture_path
    Texture(GLenum texture_target_type, const std::vector<TextureParam> &params, const std::string &texture_path);

    /// @brief 
    void bind();

private:
    /// @brief
    unsigned int texture_ID;

    /// @brief 
    GLenum textureTargetType;

    /// @brief 
    GLenum textureUnit;

    /// @brief 
    glm::vec2 dimensions;

    /// @brief 
    /// @param texture_path 
    void assignTexture(const std::string &texture_path);
};