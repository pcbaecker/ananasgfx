#ifndef __UNITTEST__
#ifndef __ANDROID__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#else
#include <GLES3/gl3.h>
#endif

#include <ananasgfx/gfx/renderer/opengl/OpenGlShader.hpp>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <ee/Log.hpp>

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
        ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "Initializing shader", {});
        GLuint vertexShaderId = compile(GL_VERTEX_SHADER, getGlslVersion() + this->vertexShader());
        GLuint fragmentShaderId = compile(GL_FRAGMENT_SHADER, getGlslVersion() + this->fragmentShader());
        if (vertexShaderId == 0 || fragmentShaderId == 0) { return; }

        // Link program
        this->mProgamId = glCreateProgram();
        if (this->mProgamId == 0) {
            return ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "glCreateProgram() returned error", {
                ee::Note("glGetError()", glGetError())
            });
        }

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
        ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "Compiling single shader", {
            ee::Note("Shader", source)
        });

        // Create shader id
        GLuint shaderId = glCreateShader(shaderType);
        if (shaderId == 0) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "glCreateShader() returned error", {
                    ee::Note("glGetError()", glGetError()),
                    ee::Note("ShaderType", shaderType)
            });
            return 0;
        }

        // Provide source
        auto str = source.c_str();
        auto strLen = static_cast<GLint>(source.size());
        glShaderSource(shaderId, 1, &str, &strLen);

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