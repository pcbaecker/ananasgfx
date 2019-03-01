#ifndef GFX_SHADER_H
#define GFX_SHADER_H

#include <glm/glm.hpp>
#include <string>

namespace gfx {

    /**
     * @brief Defines the different available predefined shader types.
     */
    enum ShaderType {SimpleColor = 0, TextureGrayscaleShader = 1, TextureGrayAlphaShader = 2 , TextureRgbaShader = 3};

    /**
     * @brief Controls a shader uniform.
     */
    class ShaderUniform {
    public:
        /**
         * @brief Binds a glm 4x4 matrix.
         *
         * @param matrix The 4x4 matrix to bind.
         */
        virtual void bind(glm::mat4* matrix) noexcept = 0;

        /**
         * @brief Binds a glm 4 elements vector.
         *
         * @param vector The vector to bind.
         */
        virtual void bind(glm::vec4* vector) noexcept = 0;
    };

    /**
     * @brief Controls all shader stuff.
     */
    class Shader {
    public:
        /**
         * @brief Informs the renderer that we want to use this shader now.
         */
        virtual void use() noexcept = 0;

        /**
         * @brief Tries to get a shader uniform.
         *
         * @throws ee::Exception
         * @param name The name of the shader uniform.
         * @return Pointer to the ShaderUniform.
         */
        virtual ShaderUniform* getUniform(const std::string& name) = 0;
    };

}

#endif