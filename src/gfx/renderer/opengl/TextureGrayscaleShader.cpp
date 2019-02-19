#ifndef __UNITTEST__

#include <ananasgfx/gfx/renderer/opengl/TextureGrayscaleShader.hpp>

namespace gfx::renderer::opengl {

    std::string TextureGrayscaleShader::vertexShader() const noexcept {
        return R"shader(

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

uniform mat4 mvp;

out highp vec2 texCoords;

void main() {
    gl_Position =  mvp * vec4(vertexPosition_modelspace,1);
    texCoords = vertexUV;
}
)shader";
    }

    std::string TextureGrayscaleShader::fragmentShader() const noexcept {
        return R"shader(

uniform sampler2D textureSampler;
uniform highp vec4 overallColor;

in highp vec2 texCoords;

out highp vec4 color;

void main() {
    color = vec4(overallColor.r, overallColor.g, overallColor.b, texture(textureSampler, texCoords).r * overallColor.a);
}
)shader";
    }

}

#endif