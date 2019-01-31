#ifndef __UNITTEST__

#include <ananasgfx/gfx/renderer/opengl/OpenglRenderer.hpp>
#include <ananasgfx/gfx/renderer/opengl/SimpleColorShader.hpp>
#include <ananasgfx/gfx/renderer/opengl/TextureGrayscaleShader.hpp>
#include <ananasgfx/gfx/renderer/opengl/TextureGrayAlphaShader.hpp>
#include <ananasgfx/gfx/renderer/opengl/TextureRgbaShader.hpp>

#ifndef __ANDROID__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ee/Log.hpp>

#else
#include <GLES3/gl3.h>
#endif

namespace gfx::renderer::opengl {

    OpenglRenderer::OpenglRenderer() {
        // Print the version we are using for rendering
        ee::Log::log(ee::LogLevel::Info, "", __PRETTY_FUNCTION__, "Creating renderer", {
            ee::Note("Version", getVersion())
        });

        try {
            ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "Creating shaders", {});
            this->mShaderCache[gfx::ShaderType::SimpleColor] = std::make_shared<SimpleColorShader>();
            this->mShaderCache[gfx::ShaderType::TextureGrayscaleShader] = std::make_shared<TextureGrayscaleShader>();
            this->mShaderCache[gfx::ShaderType::TextureGrayAlphaShader] = std::make_shared<TextureGrayAlphaShader>();
            this->mShaderCache[gfx::ShaderType::TextureRgbaShader] = std::make_shared<TextureRgbaShader>();

            // Initialize all shader
            ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "Initializing shaders", {});
            for (auto& shader : this->mShaderCache) {
                shader.second->init();
            }

            // Define some OpenGL things
            ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "Setting up opengl", {});
            glEnable(GL_DEPTH_TEST);

            // Must only be done once and is not used anymore?
            glGenVertexArrays(1, &this->mVertexAttribArray);
            glBindVertexArray(this->mVertexAttribArray);

            ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "Renderer successfully created", {});
        } catch (ee::Exception& e) {
            throw;
        }
    }

    void OpenglRenderer::clearScreen() noexcept {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenglRenderer::setClearColor(float r, float g, float b, float a) noexcept {
        glClearColor(r, g, b, a);
    }

    std::string OpenglRenderer::getVersion() noexcept {
        std::string version = (const char*)glGetString(GL_VERSION);
        version = "OpenGL " + version;
        return version;
    }

    ::gfx::Shader* OpenglRenderer::getShader(ShaderType shaderType) {
        if (!this->mShaderCache.count(shaderType)) {
            throw OpenGlRendererException(__PRETTY_FUNCTION__, "ShaderType not found", {
                ee::Note("ShaderType", shaderType, __PRETTY_FUNCTION__)
            });
        }

        return this->mShaderCache[shaderType].get();
    }

    bufferIndex_t OpenglRenderer::createVertexBuffer() noexcept {
        GLuint bufferIndex;

        // Create a single generic buffer
        glGenBuffers(1, &bufferIndex);

        return static_cast<bufferIndex_t>(bufferIndex);
    }

    void OpenglRenderer::deleteVertexBuffer(bufferIndex_t vertexBufferIndex) noexcept {
        glDeleteBuffers(1, &vertexBufferIndex);
    }

    void OpenglRenderer::bufferVertices(Vertices *vertices) noexcept {
        // Buffer the indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertices->getIndicesBufferIndex());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertices->getIndices().size() * sizeof(unsigned short), &vertices->getIndices()[0], GL_STATIC_DRAW);

        // Buffer the vertices
        for (auto& buffer : vertices->getBuffers()) {
            // Bind the buffer
            glBindBuffer(GL_ARRAY_BUFFER, buffer.second->getBufferIndex());

            // Transfer the data from the vertex to the buffer
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer.second->getData().size(), &buffer.second->getData()[0], GL_STATIC_DRAW);
        }
    }

    void OpenglRenderer::bindVertices(Vertices *vertices) noexcept {
        // Bind index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertices->getIndicesBufferIndex());

        // Bind vertices
        uint8_t index = 0;
        for (auto& buffer : vertices->getBuffers()) {
            // Enable the next vertex
            glEnableVertexAttribArray(index++);

            // Bind the buffer
            glBindBuffer(GL_ARRAY_BUFFER, buffer.second->getBufferIndex());

            // Connect buffer with shader
            glVertexAttribPointer(
                    buffer.second->getShaderLocation(),                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    buffer.second->getAlignment(),                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    nullptr            // array buffer offset
            );
        }
    }

    void OpenglRenderer::drawVertices(Vertices *vertices) noexcept {

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertices->getIndices().size()), GL_UNSIGNED_SHORT, nullptr);

        // Disable vertices
        uint8_t index = 0;
        for (auto& buffer : vertices->getBuffers()) {
            glDisableVertexAttribArray(index++);
        }
    }

    bufferIndex_t OpenglRenderer::createIndicesBuffer() noexcept {
        GLuint bufferIndex;

        // Create a single generic buffer
        glGenBuffers(1, &bufferIndex);

        return static_cast<bufferIndex_t>(bufferIndex);
    }

    void OpenglRenderer::deleteIndicesBuffer(bufferIndex_t bufferIndex) noexcept {
        glDeleteBuffers(1, &bufferIndex);
    }

    textureName_t OpenglRenderer::createTexture() noexcept {
        GLuint textureName;

        // Create a single texture
        glGenTextures(1, &textureName);

        return textureName;
    }

    void OpenglRenderer::deleteTexture(textureName_t textureName) noexcept {
        glDeleteTextures(1, &textureName);
    }

    bool OpenglRenderer::loadBitmap(Texture* pTexture, Bitmap *pBitmap) noexcept {
        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, pTexture->getName());

        // Define filter method for scaling the texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Read the bitmap into the texture, depending on the number of channels
        switch (pBitmap->getChannels()) {
            default:
                // Unsupported number of channels
                return false;

            case Grayscale: {
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                        static_cast<GLsizei>(pBitmap->getWidth()),
                        static_cast<GLsizei>(pBitmap->getHeight()),
                        0, GL_RED, GL_UNSIGNED_BYTE, pBitmap->getData());
            } return true;

            case GrayAlpha: {
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RG,
                        static_cast<GLsizei>(pBitmap->getWidth()),
                        static_cast<GLsizei>(pBitmap->getHeight()),
                        0, GL_RG, GL_UNSIGNED_BYTE, pBitmap->getData());
            } return true;

            case RGB: {
                glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                        static_cast<GLsizei>(pBitmap->getWidth()),
                        static_cast<GLsizei>(pBitmap->getHeight()),
                        0, GL_RGB, GL_UNSIGNED_BYTE, pBitmap->getData());
            } return true;

            case RGBA: {
                glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                        static_cast<GLsizei>(pBitmap->getWidth()),
                        static_cast<GLsizei>(pBitmap->getHeight()),
                        0, GL_RGBA, GL_UNSIGNED_BYTE, pBitmap->getData());
            } return true;
        }
    }

    bufferIndex_t OpenglRenderer::createFramebuffer() noexcept {
        GLuint FramebufferName = 0;
        glGenFramebuffers(1, &FramebufferName);
        return FramebufferName;
    }

    void OpenglRenderer::deleteFramebuffer(bufferIndex_t bufferIndex) noexcept {
        glDeleteFramebuffers(1, &bufferIndex);
    }

    bufferIndex_t OpenglRenderer::createRenderbuffer() noexcept {
        GLuint renderbuffer;
        glGenRenderbuffers(1, &renderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
        return renderbuffer;
    }

    void OpenglRenderer::deleteRenderbuffer(bufferIndex_t bufferIndex) noexcept {
        glDeleteRenderbuffers(1, &bufferIndex);
    }

    void OpenglRenderer::attachTextureToFramebuffer(textureName_t textureName, bufferIndex_t framebufferIndex) noexcept {
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferIndex);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureName, 0);

        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers);

        // Check
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "Framebuffer status invalid",
                    {}, ee::Stacktrace::create());
        }

        // Bind the original framebuffer back again
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenglRenderer::loadEmptyTexture(textureName_t textureName, size_t width, size_t height) noexcept {
        glBindTexture(GL_TEXTURE_2D, textureName);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int>(width), static_cast<int>(height), 0,GL_RGBA, GL_UNSIGNED_BYTE, 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    void OpenglRenderer::bindFramebuffer(bufferIndex_t bufferIndex) noexcept {
        glBindFramebuffer(GL_FRAMEBUFFER, bufferIndex);
    }

    void OpenglRenderer::bindTexture(textureName_t textureName) noexcept {
        glBindTexture(GL_TEXTURE_2D, textureName);
    }

    void OpenglRenderer::setViewport(size_t width, size_t height) noexcept {
        glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    }

    void OpenglRenderer::readFramebuffer(void *pData, size_t width, size_t height) noexcept {
        // We must define the correct pack alignment, otherwise the bitmap is unreadable
        glPixelStorei(GL_PACK_ALIGNMENT, 2);

        // Read the pixels from the framebuffer into our allocated memory
        glReadPixels(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height), GL_RGBA, GL_UNSIGNED_BYTE, pData);
    }

    void OpenglRenderer::beginStencilBufferFilling() noexcept {
        glEnable(GL_STENCIL_TEST);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_FALSE);
        glStencilFunc(GL_NEVER, 1, 0xFF);
        glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);

        // From now on draw() commands write into stencil buffer
        glStencilMask(0xFF);

        // Clear the stencil buffer
        glClear(GL_STENCIL_BUFFER_BIT);
    }

    void OpenglRenderer::endStencilBufferFilling() noexcept {
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask(GL_TRUE);

        // From now on draw() commands will not write into stencil buffer
        glStencilMask(0x00);
    }

    void OpenglRenderer::activateStencilBuffer(bool drawWhereStencil) noexcept {
        // Use the stencil buffer and compare the drawn area with it
        // Where stencil buffer is filled, we show drawn content
        glStencilFunc(GL_EQUAL, drawWhereStencil, 0xFF);
    }

    void OpenglRenderer::deactivateStencilBuffer() noexcept {
        glDisable(GL_STENCIL_TEST);
    }
}

#endif