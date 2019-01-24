#ifndef __UNITTEST__

#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#ifndef __ANDROID__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#else
#include <GLES3/gl3.h>
#endif

#include <ananasgfx/gfx/renderer/opengl/OpenGlShader.hpp>

namespace gfx::renderer::opengl {

    OpenGlShaderUniform::OpenGlShaderUniform(unsigned int uniformLocation) noexcept :
    mUniformLocation(uniformLocation) {

    }

    void OpenGlShaderUniform::bind(glm::mat4* matrix) noexcept {
        glUniformMatrix4fv(this->mUniformLocation, 1, GL_FALSE, glm::value_ptr(*matrix));
    }

    void OpenGlShaderUniform::bind(glm::vec4 *vector) noexcept {
        glUniform4fv(this->mUniformLocation, 1, glm::value_ptr(*vector));
    }

    std::string OpenGlShader::getGlslVersion() noexcept {
#if defined(__EMSCRIPTEN__) || defined(__ANDROID__)
        return "#version 300 es\n";
#else
        return "#version 330\n";
#endif
    }

    void OpenGlShader::init() {
        GLuint vertexShaderId = compile(GL_VERTEX_SHADER, getGlslVersion() + this->vertexShader());
        GLuint fragmentShaderId = compile(GL_FRAGMENT_SHADER, getGlslVersion() + this->fragmentShader());

        // Link program
        this->mProgamId = glCreateProgram();
        glAttachShader(this->mProgamId, vertexShaderId);
        glAttachShader(this->mProgamId, fragmentShaderId);
        glLinkProgram(this->mProgamId);

        // Check the program
        GLint result = GL_FALSE;
        int infoLogLength;
        glGetProgramiv(this->mProgamId, GL_LINK_STATUS, &result);
        glGetProgramiv(this->mProgamId, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (result == GL_FALSE && infoLogLength > 0) {
            std::vector<char> errorMessage(static_cast<unsigned long>(infoLogLength + 1));
            glGetProgramInfoLog(this->mProgamId, infoLogLength, nullptr, &errorMessage[0]);
            throw OpenGlShaderException(__PRETTY_FUNCTION__, "Could not link shader", {
                ee::Note("VertexShader", this->vertexShader(), __PRETTY_FUNCTION__),
                ee::Note("FragmentShader", this->fragmentShader(), __PRETTY_FUNCTION__)
            });
        }

        // Remove the compiled shader resources that are now linked into the final shader program
        glDetachShader(this->mProgamId, vertexShaderId);
        glDetachShader(this->mProgamId, fragmentShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
    }

    unsigned int OpenGlShader::compile(unsigned int shaderType, const std::string& source) {
        // Create shader id
        GLuint shaderId = glCreateShader(shaderType);

        // Provide source
        auto str = source.c_str();
        glShaderSource(shaderId, 1, &str, nullptr);

        // Try to compile shader
        glCompileShader(shaderId);

        // Check the compilation result
        GLint result = GL_FALSE;
        int infoLogLength;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (result == GL_FALSE && infoLogLength > 0) {
            std::vector<char> errorMessage(static_cast<unsigned long>(infoLogLength + 1));
            glGetShaderInfoLog(shaderId, infoLogLength, nullptr, &errorMessage[0]);
            throw OpenGlShaderException(__PRETTY_FUNCTION__, "Could not compile shader", {
                ee::Note("ShaderType", shaderType, __PRETTY_FUNCTION__),
                ee::Note("Source", source, __PRETTY_FUNCTION__),
                ee::Note("Result", result, __PRETTY_FUNCTION__),
                ee::Note("InfoLogLength", infoLogLength, __PRETTY_FUNCTION__),
                ee::Note("ErrorMessage", std::string(&errorMessage[0], errorMessage.size()), __PRETTY_FUNCTION__)
            });
        }

        // Return the shader id
        return shaderId;
    }

    void OpenGlShader::use() noexcept {
        glUseProgram(this->mProgamId);
    }

    unsigned int OpenGlShader::getGlProgramHandle() const noexcept {
        return this->mProgamId;
    }

    ShaderUniform *OpenGlShader::getUniform(const std::string &name) {
        // Check if we already cached the uniform
        if (this->mUniforms.count(name)) {
            return this->mUniforms.at(name).get();
        }

        // We have to get the uniform location
        GLint uniformLocation = glGetUniformLocation(this->mProgamId, name.c_str());
        if (uniformLocation < 0
        || uniformLocation == GL_INVALID_VALUE
        || uniformLocation == GL_INVALID_OPERATION) {
            throw OpenGlShaderException(__PRETTY_FUNCTION__, "Could not get uniform location", {
                ee::Note("ReturnCode", uniformLocation, __PRETTY_FUNCTION__),
                ee::Note("Name", name, __PRETTY_FUNCTION__)
            });
        }

        // Cache the uniform
        this->mUniforms[name] = std::make_shared<OpenGlShaderUniform>(uniformLocation);
        return this->mUniforms.at(name).get();
    }
}

#endif