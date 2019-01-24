#ifndef __UNITTEST__

#include <ananasgfx/gfx/renderer/opengl/SimpleColorShader.hpp>

namespace gfx::renderer::opengl {

    std::string SimpleColorShader::vertexShader() const noexcept {
        return R"shader(

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 mvp;

out vec4 fragmentColor;

void main() {
    gl_Position =  mvp * vec4(vertexPosition_modelspace,1);
}
)shader";
    }

    std::string SimpleColorShader::fragmentShader() const noexcept {
        return R"shader(

uniform highp vec4 overallColor;

out highp vec4 color;

void main() {
    color = overallColor;
}
)shader";
    }

}

#endif