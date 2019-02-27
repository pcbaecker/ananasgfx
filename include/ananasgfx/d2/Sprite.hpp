#ifndef D2_SPRITE_H
#define D2_SPRITE_H

#include <ananasgfx/gfx/Texture.hpp>

#include "Rectangle.hpp"

namespace d2 {

    /**
     * @brief Creates a sprite.
     */
    class Sprite : public Rectangle {
    public:
        /**
         * @brief Initializes the sprite.
         *
         * @return True on success.
         */
        bool init() noexcept override;

        /**
         * @brief Sets the filename of the image to load into that sprite.
         *
         * @param filename The filename of the image to display with this sprite.
         */
        void setFilename(const std::string& filename) noexcept;

        /**
         * @brief Returns the filename of the image to be displayed in this sprite.
         *
         * @return The filename of the image to be displayed.
         */
        const std::string& getFilename() const noexcept;

        /**
         * @brief Sets the texture of this prite.
         *
         * @param pTexture The texture to display in this sprite.
         */
        void setTexture(gfx::Texture* pTexture) noexcept;

        /**
         * @brief Returns the texture that is used by this sprite.
         *
         * @return Pointer to the texture used by this sprite.
         */
        gfx::Texture* getTexture() const noexcept;

        /**
         * @brief Sets this sprite to vertical flipped.
         *
         * @param flip True if we want to flip this sprite vertically.
         */
        void setVerticalFlip(bool flip) noexcept;

        /**
         * @brief Returns true if this sprite is vertically flipped.
         *
         * @return Is vertically flipped.
         */
        bool isVerticallyFlipped() const noexcept;

        /**
         * @brief Draws this sprite onto into the current framebuffer.
         */
        void draw() noexcept override;

    protected:
        /**
         * @brief Updates the vertex nodes vertices.
         */
        void updateVertices() noexcept override;

        /**
         * @brief Returns the shader that should be used for this vertex node.
         *
         * @return The shader that should be used for this vertex node.
         */
        gfx::Shader *shader() noexcept override;

    protected:
        /**
         * @brief The filename of the image to be displayed with this sprite.
         */
        std::string mFilename;

        /**
         * @brief The texture of this sprite.
         */
        gfx::Texture* pTexture = nullptr;

        /**
         * @brief If true this sprite should be displayed vertically flipped.
         */
        bool mVerticalFlip = false;
    };

}

#endif