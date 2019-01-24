#ifndef GFX_SHADER_H
#define GFX_SHADER_H

#include <glm/glm.hpp>
#include <string>

namespace gfx {

    enum ShaderType {SimpleColor = 0, TextureGrayscaleShader = 1, TextureGrayAlphaShader = 2 , TextureRgbaShader = 3};

    class ShaderUniform {
    public:
        virtual void bind(glm::mat4* matrix) noexcept = 0;
        virtual void bind(glm::vec4* vector) noexcept = 0;
    };

    class Shader {
    public:
        virtual void use() noexcept = 0;
        virtual ShaderUniform* getUniform(const std::string& name) = 0;
    };

}

#endif