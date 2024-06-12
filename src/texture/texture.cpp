#include "texture/texture.h"

TextureParam::TextureParam(GLenum paramName, GLenum value)
{
    this->paramName = paramName;
    this->value = value;
}

TextureParam::TextureParam(std::tuple<GLenum, GLenum> pair)
{
    this->paramName = std::get<0>(pair);
    this->value = std::get<1>(pair);
}

Texture::Texture(GLenum texture_target_type, const std::vector<TextureParam> &params, const std::string &texture_path, GLenum texture_unit)
{
    // generate a texture object in OpenGL
    unsigned int id;
    glGenTextures(1, &id);
    this->texture_ID = id;

    // bind it (using the explicit texture type)
    this->textureTargetType = texture_target_type;
    glBindTexture(this->textureTargetType, this->texture_ID);

    // set the parameters (if any)
    for (const auto &param : params)
    {
        glTexParameteri(this->textureTargetType, param.paramName, param.value);
    }

    // load and apply the texture
    glm::vec2 dimensions = assignTexture(texture_path);
}

Texture::Texture(GLenum texture_target_type, const std::vector<TextureParam> &params, const std::string &texture_path)
    : Texture::Texture(textureTargetType, params, texture_path, GL_TEXTURE0)
{
}

glm::vec2 Texture::assignTexture(const std::string &texture_path)
{
    auto has_extension = [](const std::string &file_path, const std::string &extension) -> bool
    {
        return file_path.compare(file_path.length() - extension.length(), extension.length(), extension) == 0;
    };

    const std::string jpg_trail = ".jpg";
    const std::string png_trail = ".png";

    // determine underlying format of texture file
    GLenum format;
    if (has_extension(texture_path, jpg_trail)) // for jpgs we use rgb
        format = GL_RGB;

    else if (has_extension(texture_path, png_trail)) // for pngs we need rgba
        format = GL_RGBA;

    else
        std::cout << "ERROR::TEXTURE::INVALID_FILE_FORMAT_FOR_TEXTURE" << std::endl;

    // load texture
    int width, height, nrChannels;
    unsigned char *texture_data = stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);

    // apply loaded texture data to OpenGL texture object
    if (texture_data)
    {
        // bind the texture (should already be bound but just in case)
        glBindTexture(this->textureTargetType, this->texture_ID);
        // bind texture data to the currently bound texture object
        glTexImage2D(this->textureTargetType, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, texture_data);
        // generate mip maps for the texture (smaller textures for distant renders)
        glGenerateMipmap(this->textureTargetType);
    }
    else
    {
        std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD_TEXTURE_DATA" << std::endl;
    }

    stbi_image_free(texture_data);

    return glm::vec2(width, height);
}