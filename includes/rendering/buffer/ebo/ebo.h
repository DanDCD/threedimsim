#pragma once
#include "rendering/buffer/buffer/buffer.h"
#include <glad/glad.h>

/// @brief manages Index data inside OpenGL
class EBO : public Buffer
{
public:
    EBO();

    EBO(EBO &&other);

    EBO &operator=(EBO &&other) noexcept;
};