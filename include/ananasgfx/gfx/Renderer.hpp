#ifndef GFX_RENDERER_H
#define GFX_RENDERER_H

#include <map>
#include <memory>
#include <string>

#include "Vertex.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace gfx {

    class Renderer {
    public:
        static std::shared_ptr<Renderer> create();
        virtual void clearScreen() noexcept = 0;
        virtual void setClearColor(float r, float g, float b, float a) noexcept = 0;
        virtual std::string getVersion() noexcept = 0;

        virtual bufferIndex_t createVertexBuffer() noexcept = 0;
        virtual void deleteVertexBuffer(bufferIndex_t vertexBufferIndex) noexcept = 0;

        virtual bufferIndex_t createIndicesBuffer() noexcept = 0;
        virtual void deleteIndicesBuffer(bufferIndex_t bufferIndex) noexcept = 0;

        virtual bufferIndex_t createFramebuffer() noexcept = 0;
        virtual void deleteFramebuffer(bufferIndex_t bufferIndex) noexcept = 0;
        virtual void bindFramebuffer(bufferIndex_t bufferIndex) noexcept = 0;

        virtual bufferIndex_t createRenderbuffer() noexcept = 0;
        virtual void deleteRenderbuffer(bufferIndex_t bufferIndex) noexcept = 0;

        virtual void bufferVertices(Vertices* vertices) noexcept = 0;
        virtual void bindVertices(Vertices* vertices) noexcept = 0;
        virtual void drawVertices(Vertices* vertices) noexcept = 0;

        virtual textureName_t createTexture() noexcept = 0;
        virtual void deleteTexture(textureName_t textureName) noexcept = 0;
        virtual bool loadBitmap(Texture* pTexture, Bitmap* pBitmap) noexcept = 0;
        virtual void loadEmptyTexture(textureName_t textureName, size_t width, size_t height) noexcept = 0;
        virtual void attachTextureToFramebuffer(textureName_t textureName, bufferIndex_t framebufferIndex) noexcept = 0;
        virtual void bindTexture(textureName_t textureName) noexcept = 0;

        virtual void setViewport(size_t width, size_t height) noexcept = 0;
        virtual void readFramebuffer(void* pData, size_t width, size_t height) noexcept = 0;

        virtual Shader* getShader(ShaderType shader) = 0;

        virtual void beginStencilBufferFilling() noexcept = 0;
        virtual void endStencilBufferFilling() noexcept = 0;
        virtual void activateStencilBuffer(bool drawWhereStencil) noexcept = 0;
        virtual void deactivateStencilBuffer() noexcept = 0;
    };

}

#endif