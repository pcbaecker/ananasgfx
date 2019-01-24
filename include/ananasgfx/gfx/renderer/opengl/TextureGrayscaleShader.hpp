#ifndef GFX_RENDERER_OPENGL_TEXTUREGRAYSCALESHADER_H
#define GFX_RENDERER_OPENGL_TEXTUREGRAYSCALESHADER_H

#include <ananasgfx/gfx/renderer/opengl/OpenGlShader.hpp>

namespace gfx::renderer::opengl {

    class TextureGrayscaleShader : public ::gfx::renderer::opengl::OpenGlShader {
    public:
        std::string vertexShader() const noexcept override;

        std::string fragmentShader() const noexcept override;
    };

}

#endif