#ifndef GFX_RENDERER_OPENGL_SIMPLECOLORSHADER_H
#define GFX_RENDERER_OPENGL_SIMPLECOLORSHADER_H

#include <ananasgfx/gfx/renderer/opengl/OpenGlShader.hpp>

namespace gfx::renderer::opengl {

    class SimpleColorShader : public ::gfx::renderer::opengl::OpenGlShader {
    public:
        std::string vertexShader() const noexcept override;

        std::string fragmentShader() const noexcept override;
    };

}

#endif