#ifndef GFX_RENDERTEXTURE_H
#define GFX_RENDERTEXTURE_H

#include "Vertices.hpp"
#include "Texture.hpp"
#include "Bitmap.hpp"

namespace gfx {

    class Window;

    /**
     * @brief Specialization of the basic gfx::Texture with the possibility to draw content into it.
     */
    class RenderTexture : public Texture {
    public:
        /**
         * @brief Constructor.
         *
         * @param pWindow Pointer to the window.
         * @param width The desired width.
         * @param height The desired height.
         */
        explicit RenderTexture(Window* pWindow, size_t width, size_t height) noexcept;

        /**
         * @brief The destructor.
         */
        ~RenderTexture() noexcept override;

        /**
         * @brief Begins drawing onto the RenderTexture.
         */
        void begin() noexcept;

        /**
         * @brief Ends the drawing onto the RenderTexture.
         */
        void end() noexcept;

        /**
         * @brief Tries to convert the RenderTexture to a bitmap.
         *
         * @return Optional that can contain the bitmap.
         */
        std::optional<std::shared_ptr<Bitmap>> toBitmap() noexcept;

    protected:
        /**
         * @brief Pointer to the window.
         */
        Window* pWindow = nullptr;

        /**
         * @brief The framebuffer.
         */
        bufferIndex_t mFramebuffer = 0;

        /**
         * @brief The renderbuffer.
         */
        bufferIndex_t mRenderbuffer = 0;

        /**
         * @brief Stores the state when we draw into this RenderTexture.
         */
        bool mActive = false;
    };
}

#endif