#include <ananasgfx/gfx/Texture.hpp>
#include <ananasgfx/gfx/Renderer.hpp>
#include <ananasgfx/gfx/Bitmap.hpp>

namespace gfx {

    std::optional<std::shared_ptr<Texture>> Texture::create(Renderer* pRenderer, const std::string &filename) noexcept {
        // Try to load the bitmap
        auto bitmap = Bitmap::read(filename);
        if (!bitmap.has_value()) {
            return std::nullopt;
        }

        // Create the texture from the bitmap
        return create(pRenderer, **bitmap);
    }

    std::optional<std::shared_ptr<Texture>> Texture::create(Renderer *pRenderer, Bitmap &bitmap) noexcept {
        // Create a texture object
        std::shared_ptr<Texture> texture = std::make_shared<Texture>(pRenderer);

        // Try to read the bitmap into the texture
        if (!pRenderer->loadBitmap(texture.get(), &bitmap)) {
            return std::nullopt;
        }

        // Texture is initialized
        texture->mTextureFormat = static_cast<TextureFormat>(bitmap.getChannels());
        texture->mWidth = bitmap.getWidth();
        texture->mHeight = bitmap.getHeight();
        return texture;
    }

    Texture::Texture(Renderer *pRenderer) noexcept : pRenderer(pRenderer) {
        this->mTextureName = this->pRenderer->createTexture();
    }

    Texture::~Texture() noexcept {
        this->pRenderer->deleteTexture(this->mTextureName);
    }

    textureName_t Texture::getName() const noexcept {
        return this->mTextureName;
    }

    TextureFormat Texture::getFormat() const noexcept {
        return this->mTextureFormat;
    }

    size_t Texture::getWidth() const noexcept {
        return this->mWidth;
    }

    size_t Texture::getHeight() const noexcept {
        return this->mHeight;
    }

    ShaderType Texture::getShaderType() const noexcept {
        switch (this->mTextureFormat) {
            default:
            case RGB:
            case RGBA:
                return ShaderType::TextureRgbaShader;

            case Grayscale:
                return ShaderType::TextureGrayscaleShader;

            case GrayAlpha:
                return ShaderType ::TextureGrayAlphaShader;
        }
    }

}