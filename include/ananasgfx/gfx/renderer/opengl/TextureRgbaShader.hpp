#ifndef GFX_RENDERER_OPENGL_TEXTURERGBASHADER_H
#define GFX_RENDERER_OPENGL_TEXTURERGBASHADER_H

#include <ananasgfx/gfx/renderer/opengl/OpenGlShader.hpp>

namespace gfx::renderer::opengl {

    class TextureRgbaShader : public ::gfx::renderer::opengl::OpenGlShader {
    public:
        std::string vertexShader() const noexcept override;

        std::string fragmentShader() const noexcept override;
    };

}

#endif