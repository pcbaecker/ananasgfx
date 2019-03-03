#ifndef GFX_RENDERER_H
#define GFX_RENDERER_H

#include <map>
#include <memory>
#include <string>

#include "Vertices.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace gfx {

    /**
     * @brief This interface defines the basic render methods that must be implemented.
     */
    class Renderer {
    public:
        /**
         * @brief This static method creates a renderer.
         *
         * @throws ee::Exception
         * @return Pointer to the created renderer.
         */
        static std::shared_ptr<Renderer> create();

        /**
         * @brief Clears the screen.
         */
        virtual void clearScreen() noexcept = 0;

        /**
         * @brief Sets the clear screen color.
         *
         * @param r The red value.
         * @param g The green value.
         * @param b The blue value.
         * @param a The alpha value.
         */
        virtual void setClearColor(float r, float g, float b, float a) noexcept = 0;

        /**
         * @brief Returns the version of the renderer.
         *
         * @return String representing the version of the renderer.
         */
        virtual std::string getVersion() noexcept = 0;

        /**
         * @brief Creates a vertex buffer.
         *
         * @return The index of the createded buffer.
         */
        virtual bufferIndex_t createVertexBuffer() noexcept = 0;

        /**
         * @brief Deletes the vertex buffer with the given index.
         *
         * @param vertexBufferIndex The index of the vertex buffer.
         */
        virtual void deleteVertexBuffer(bufferIndex_t vertexBufferIndex) noexcept = 0;

        /**
         * @brief Creates an indices buffer.
         *
         * @return The index of the created buffer.
         */
        virtual bufferIndex_t createIndicesBuffer() noexcept = 0;

        /**
         * @brief Deletes the indicies buffer with the given index.
         *
         * @param bufferIndex The index of the buffer.
         */
        virtual void deleteIndicesBuffer(bufferIndex_t bufferIndex) noexcept = 0;

        /**
         * @brief Creates a framebuffer.
         *
         * @return The index of the createded framebuffer.
         */
        virtual bufferIndex_t createFramebuffer() noexcept = 0;

        /**
         * @brief Deletes the framebuffer with the given index.
         *
         * @param bufferIndex The index of the framebuffer.
         */
        virtual void deleteFramebuffer(bufferIndex_t bufferIndex) noexcept = 0;

        /**
         * @brief Binds the framebuffer with the given index.
         *
         * @param bufferIndex The index of the framebuffer that we want to bind.
         */
        virtual void bindFramebuffer(bufferIndex_t bufferIndex) noexcept = 0;

        /**
         * @brief Creates a new renderbuffer.
         *
         * @return The index of the new renderbuffer.
         */
        virtual bufferIndex_t createRenderbuffer() noexcept = 0;

        /**
         * @brief Deletes the renderbuffer with the given index.
         *
         * @param bufferIndex The index of the buffer.
         */
        virtual void deleteRenderbuffer(bufferIndex_t bufferIndex) noexcept = 0;

        /**
         * @brief Buffers the given vertices.
         *
         * @param vertices The vertices that we want to buffer.
         */
        virtual void bufferVertices(Vertices* vertices) noexcept = 0;

        /**
         * @brief Binds the given vertices.
         *
         * @param vertices The vertices that we want to bind.
         */
        virtual void bindVertices(Vertices* vertices) noexcept = 0;

        /**
         * @brief Draws the given vertices.
         *
         * @param vertices The vertices that we want to draw.
         */
        virtual void drawVertices(Vertices* vertices) noexcept = 0;

        /**
         * @brief Creates a new texture.
         *
         * @return The texturename.
         */
        virtual textureName_t createTexture() noexcept = 0;

        /**
         * @brief Deletes the texture with the given name.
         *
         * @param textureName The texture name.
         */
        virtual void deleteTexture(textureName_t textureName) noexcept = 0;

        /**
         * @brief Loads the given bitmap into the given texture.
         *
         * @param pTexture The target texture.
         * @param pBitmap The source bitmap.
         */
        virtual bool loadBitmap(Texture* pTexture, Bitmap* pBitmap) noexcept = 0;

        /**
         * @brief Loads an empty texture.
         *
         * @param textureName The name of the texture.
         * @param width The width of the texture.
         * @param height The height of the texture.
         */
        virtual void loadEmptyTexture(textureName_t textureName, size_t width, size_t height) noexcept = 0;

        /**
         * @brief Attaches the given texture to the given framebuffer.
         *
         * @param textureName The texture we want to attach.
         * @param framebufferIndex The framebufferindex.
         */
        virtual void attachTextureToFramebuffer(textureName_t textureName, bufferIndex_t framebufferIndex) noexcept = 0;

        /**
         * @brief Binds the given texture.
         *
         * @param textureName The name of the texture we want to bind.
         */
        virtual void bindTexture(textureName_t textureName) noexcept = 0;

        /**
         * @brief Sets the viewport.
         *
         * @param width The new width of the viewport.
         * @param height The new height of the viewport.
         */
        virtual void setViewport(size_t width, size_t height) noexcept = 0;

        /**
         * @brief Reads the current framebuffer into the given raw data pointer.
         *
         * The pointer must be allocated before.
         * @param pData The target raw data pointer.
         * @param width The width of the framebuffer.
         * @param height The height of the framebuffer.
         */
        virtual void readFramebuffer(void* pData, size_t width, size_t height) noexcept = 0;

        /**
         * @brief Returns the pointer to the shader of the requested type.
         *
         * @param shader The requested shader type.
         * @return The pointer to the requested shader type.
         */
        virtual Shader* getShader(ShaderType shader) = 0;

        /**
         * @brief Begins the filling of the stencil buffer.
         */
        virtual void beginStencilBufferFilling() noexcept = 0;

        /**
         * @brief Ends the filling of the stencil buffer.
         */
        virtual void endStencilBufferFilling() noexcept = 0;

        /**
         * @brief Activates the stencil buffer.
         *
         * @param drawWhereStencil If true we will see the drawn content where the stencils are on.
         */
        virtual void activateStencilBuffer(bool drawWhereStencil) noexcept = 0;

        /**
         * @brief Deactivates the stencil buffer.
         */
        virtual void deactivateStencilBuffer() noexcept = 0;
    };

}

#endif