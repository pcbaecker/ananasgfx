#ifndef GFX_TEXTURE_H
#define GFX_TEXTURE_H

#include <optional>
#include <memory>

#include "Bitmap.hpp"
#include "Shader.hpp"

namespace gfx {

    typedef unsigned int textureName_t;
    enum TextureFormat {Grayscale = 1, GrayAlpha = 2, RGB = 3, RGBA = 4};

    class Renderer;

    class Texture {
    public:
        static std::optional<std::shared_ptr<Texture>> create(Renderer* pRenderer, const std::string& filename) noexcept;
        static std::optional<std::shared_ptr<Texture>> create(Renderer* pRenderer, Bitmap& bitmap) noexcept;

        explicit Texture(Renderer* pRenderer) noexcept;
        virtual ~Texture() noexcept;

        textureName_t getName() const noexcept;

        TextureFormat getFormat() const noexcept;
        size_t getWidth() const noexcept;
        size_t getHeight() const noexcept;

        ShaderType getShaderType() const noexcept;

    protected:
        Renderer* pRenderer = nullptr;
        textureName_t mTextureName = 0;
        TextureFormat mTextureFormat = Grayscale;
        size_t mWidth = 0;
        size_t mHeight = 0;
    };

}

#endif