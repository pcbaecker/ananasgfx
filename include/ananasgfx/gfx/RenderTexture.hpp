#ifndef GFX_RENDERTEXTURE_H
#define GFX_RENDERTEXTURE_H

#include "Vertex.hpp"
#include "Texture.hpp"
#include "Bitmap.hpp"

namespace gfx {

    class Window;

    class RenderTexture : public Texture {
    public:
        explicit RenderTexture(Window* pWindow, size_t width, size_t height) noexcept;
        ~RenderTexture() noexcept override;

        void begin() noexcept;
        void end() noexcept;

        std::optional<std::shared_ptr<Bitmap>> toBitmap() noexcept;

    protected:
        Window* pWindow = nullptr;
        bufferIndex_t mFramebuffer = 0;
        bufferIndex_t mRenderbuffer = 0;
        bool mActive = false;
    };

}

#endif