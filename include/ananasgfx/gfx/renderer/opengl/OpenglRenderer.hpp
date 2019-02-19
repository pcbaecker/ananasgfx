#ifndef GFX_RENDERER_OPENGL_RENDERER_H
#define GFX_RENDERER_OPENGL_RENDERER_H

#include <ee/Exception.hpp>
#include <ananasgfx/gfx/Renderer.hpp>

#include "OpenGlShader.hpp"

namespace gfx::renderer::opengl {

    DEFINE_EXCEPTION(OpenGlRendererException);

    class OpenglRenderer : public ::gfx::Renderer {
    public:
        OpenglRenderer();

        void clearScreen() noexcept override;

        void setClearColor(float r, float g, float b, float a) noexcept override;

        std::string getVersion() noexcept override;

        bufferIndex_t createVertexBuffer() noexcept override;

        void deleteVertexBuffer(bufferIndex_t vertexBufferIndex) noexcept override;

        bufferIndex_t createIndicesBuffer() noexcept override;

        void deleteIndicesBuffer(bufferIndex_t bufferIndex) noexcept override;

        void bufferVertices(Vertices *vertices) noexcept override;

        void bindVertices(Vertices *vertices) noexcept override;

        void drawVertices(Vertices *vertices) noexcept override;

        textureName_t createTexture() noexcept override;

        void deleteTexture(textureName_t textureName) noexcept override;

        bool loadBitmap(Texture* pTexture, Bitmap *pBitmap) noexcept override;

        Shader* getShader(ShaderType shaderType) override;

        bufferIndex_t createFramebuffer() noexcept override;

        void deleteFramebuffer(bufferIndex_t bufferIndex) noexcept override;

        void bindFramebuffer(bufferIndex_t bufferIndex) noexcept override;

        bufferIndex_t createRenderbuffer() noexcept override;

        void deleteRenderbuffer(bufferIndex_t bufferIndex) noexcept override;

        void attachTextureToFramebuffer(textureName_t textureName, bufferIndex_t framebufferIndex) noexcept override;

        void loadEmptyTexture(textureName_t textureName, size_t width, size_t height) noexcept override;

        void bindTexture(textureName_t textureName) noexcept override;

        void setViewport(size_t width, size_t height) noexcept override;

        void readFramebuffer(void* pData, size_t width, size_t height) noexcept override;

        void beginStencilBufferFilling() noexcept override;

        void endStencilBufferFilling() noexcept override;

        void activateStencilBuffer(bool drawWhereStencil) noexcept override;

        void deactivateStencilBuffer() noexcept override;

    private:
        unsigned int mVertexAttribArray = 0;
        std::map<gfx::ShaderType,std::shared_ptr<OpenGlShader>> mShaderCache;
    };

}

#endif