#ifndef GFX_RENDERER_OPENGL_OPENGLSHADER_H
#define GFX_RENDERER_OPENGL_OPENGLSHADER_H

#include <memory>
#include <ee/Exception.hpp>
#include <ananasgfx/gfx/Shader.hpp>

namespace gfx::renderer::opengl {

    DEFINE_EXCEPTION(OpenGlShaderException);

    class OpenGlShader;

    class OpenGlShaderUniform : public ::gfx::ShaderUniform {
        friend class OpenGlShader;
    public:
        OpenGlShaderUniform(unsigned int uniformLocation) noexcept;
        void bind(glm::mat4 *matrix) noexcept override;
        void bind(glm::vec4* vector) noexcept override;
    private:
        unsigned int mUniformLocation = 0;
    };

    class OpenGlShader : public ::gfx::Shader {
    public:
        static std::string getGlslVersion() noexcept;

        void init();
        void use() noexcept override;
        ShaderUniform *getUniform(const std::string &name) override;

    protected:
        unsigned int compile(unsigned int shaderType, const std::string& source);

        unsigned int getGlProgramHandle() const noexcept;

        virtual std::string vertexShader() const noexcept = 0;

        virtual std::string fragmentShader() const noexcept = 0;

    private:
        unsigned int mProgamId = 0;
        std::map<std::string,std::shared_ptr<OpenGlShaderUniform>> mUniforms;
    };

}

#endif