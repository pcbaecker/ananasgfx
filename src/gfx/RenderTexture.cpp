#include <ananasgfx/gfx/RenderTexture.hpp>
#include <ananasgfx/gfx/Window.hpp>
#include <ee/Log.hpp>

namespace gfx {

    RenderTexture::RenderTexture(Window* pWindow, size_t width, size_t height) noexcept :
    Texture(pWindow->getRenderer()), pWindow(pWindow) {
        this->mFramebuffer = this->pRenderer->createFramebuffer();
        this->mRenderbuffer = this->pRenderer->createRenderbuffer();
        this->mTextureFormat = TextureFormat::RGBA;
        this->mWidth = width;
        this->mHeight = height;

        // Create an empty texture
        this->pRenderer->loadEmptyTexture(this->mTextureName, width, height);

        // Attach that texture to our framebuffer
        this->pRenderer->attachTextureToFramebuffer(this->mTextureName, this->mFramebuffer);
    }

    RenderTexture::~RenderTexture() noexcept {
        this->pRenderer->deleteFramebuffer(this->mFramebuffer);
        this->pRenderer->deleteRenderbuffer(this->mRenderbuffer);
    }

    void RenderTexture::begin() noexcept {
        // Bind our framebuffer
        this->pRenderer->bindFramebuffer(this->mFramebuffer);

        // Because the render texture has a different size that the window, we have to adjust the viewport
        this->pRenderer->setViewport(this->mWidth, this->mHeight);

        // Remember that this render texture is currently active
        this->mActive = true;
    }

    void RenderTexture::end() noexcept {
        // By binding framebuffer with index = 0 we set the default framebuffer back again
        // (maybe not working on different renderers than OpenGL)
        this->pRenderer->bindFramebuffer(0);

        // Restore the window viewport
        this->pRenderer->setViewport(this->pWindow->getWidth(), this->pWindow->getHeight());

        // Remember that we are done now
        this->mActive = false;
    }

    std::optional<std::shared_ptr<Bitmap>> RenderTexture::toBitmap() noexcept {
        // Allocate space for the bitmap
        void* pData = malloc(this->mWidth * this->mHeight * 4);
        if (pData == nullptr) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not allocate memory",
                    {}, ee::Stacktrace::create());
            return std::nullopt;
        }

        // Make sure that this render texture is active while reading pixels
        bool closeAtTheEnd = false;
        if (!this->mActive) {
            this->begin();
            closeAtTheEnd = true;
        }

        // Read the data from the framebuffer into our allocated space
        this->pRenderer->readFramebuffer(pData, this->mWidth, this->mHeight);

        // If we activated this render texture just for reading the pixels, we have to close it before returning
        if (closeAtTheEnd) {
            this->end();
        }

        // Create and return a bitmap containing a copy of the render texture
        return std::make_shared<Bitmap>(pData, this->mWidth, this->mHeight, 4);
    }

}