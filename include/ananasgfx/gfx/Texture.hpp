#ifndef GFX_TEXTURE_H
#define GFX_TEXTURE_H

#include <optional>
#include <memory>

#include "Bitmap.hpp"
#include "Shader.hpp"

namespace gfx {

    typedef unsigned int textureName_t;

    /**
     * @brief Defines the different available texture types.
     */
    enum TextureFormat {Grayscale = 1, GrayAlpha = 2, RGB = 3, RGBA = 4};

    class Renderer;

    /**
     * @brief Handles all texture stuff.
     */
    class Texture {
    public:
        /**
         * @brief Creates a texture from an imagefile.
         *
         * @param pRenderer Pointer to the render.
         * @param filename The filename and path to the source image file.
         * @return Optional that can contain the created texture.
         */
        static std::optional<std::shared_ptr<Texture>> create(Renderer* pRenderer, const std::string& filename) noexcept;

        /**
         * @brief Creates a texture from the given bitmap.
         *
         * @param pRenderer The renderer.
         * @param bitmap The source bitmap.
         * @return Optional that can contain the created texture.
         */
        static std::optional<std::shared_ptr<Texture>> create(Renderer* pRenderer, Bitmap& bitmap) noexcept;

        /**
         * @brief Constructor.
         *
         * @param pRenderer The renderer.
         */
        explicit Texture(Renderer* pRenderer) noexcept;

        /**
         * @brief Destructor.
         */
        virtual ~Texture() noexcept;

        /**
         * @brief Returns the texture name.
         *
         * @return The name of the texture.
         */
        textureName_t getName() const noexcept;

        /**
         * @brief Returns the texture format.
         *
         * @return The texture format.
         */
        TextureFormat getFormat() const noexcept;

        /**
         * @brief Returns the width of the texture.
         *
         * @return The width of the texture.
         */
        size_t getWidth() const noexcept;

        /**
         * @brief Returns the height of the texture.
         *
         * @return The height of the texture.
         */
        size_t getHeight() const noexcept;

        /**
         * @brief Returns the shader type that should be used for this texture.
         *
         * @return The shader type that should be used for this texture.
         */
        ShaderType getShaderType() const noexcept;

    protected:
        /**
         * @brief The renderer.
         */
        Renderer* pRenderer = nullptr;

        /**
         * @brief The texture name.
         */
        textureName_t mTextureName = 0;

        /**
         * @brief The texture format.
         */
        TextureFormat mTextureFormat = Grayscale;

        /**
         * @brief The width of the texture.
         */
        size_t mWidth = 0;

        /**
         * @brief The height of the texture.
         */
        size_t mHeight = 0;
    };
}

#endif