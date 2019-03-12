#ifndef D2_LABEL_H
#define D2_LABEL_H

#include <ananasgfx/gfx/Defines.hpp>
#include <ananasgfx/font/Font.hpp>

#include "Sprite.hpp"

namespace d2 {

    /**
     * @brief Creates a label that can display text on the screen.
     */
    class Label : public Sprite {
    public:
        /**
         * @brief Initializes this object.
         *
         * @return True if initialization was successful.
         */
        bool init() noexcept override;

        /**
         * @brief Sets the text to display.
         *
         * @param text A string that represents the text to be displayed.
         */
        void setText(std::string text) noexcept;

        /**
         * @brief Returns the text that is currently being displayed.
         *
         * @return A string reference.
         */
        const std::string& getText() const noexcept;

        /**
         * @brief Sets the horizontal alignment.
         *
         * @param align The horizontal alignment.
         */
        void setHorizontalAlign(gfx::HorizontalAlign align) noexcept;

        /**
         * @brief Returns the current horizontal alignment.
         *
         * @return The current horizontal alignment.
         */
        gfx::HorizontalAlign getHorizontalAlign() const noexcept;

        /**
         * @brief Sets the vertical alignment.
         *
         * @param align The vertical alignment.
         */
        void setVerticalAlign(gfx::VerticalAlign align) noexcept;

        /**
         * @brief Returns the vertical alignment.
         *
         * @return The vertical alignment.
         */
        gfx::VerticalAlign getVerticalAlign() const noexcept;

        /**
         * @brief Sets the font to be used.
         *
         * This method tries to find the requested font family. But it is possible that the attempt fails,
         * in that that case false is returned and nothing will change on this label.
         * @param fontFamily The name of the font family.
         * @param fontSubFamily The name of the font sub family.
         * @return True if the font is found and registered for this label.
         */
        bool setFont(const std::string& fontFamily, const std::string& fontSubFamily) noexcept;

        /**
         * @brief Returns a pointer to the font currently used.
         *
         * @return Pointer to the font currently used.
         */
        font::Font* getFont() const noexcept;

        /**
         * @brief Sets the size of this label.
         *
         * Overrides the base method to inform this label to redraw the text with the changed size.
         * @param x The new width of this label.
         * @param y The new height of this label.
         */
        void setSize(float x, float y) noexcept override;

        /**
         * @brief Defines that the internal bitmap auto resizes depending on the needed space to render.
         *
         * @param value True if we want autoresize.
         */
        void setAutoResize(bool value) noexcept;

        /**
         * @brief Sets the font size.
         *
         * @param size The new font size.
         */
        void setFontSize(font::size_t size) noexcept;

    private:
        /**
         * @brief Renders the text to a bitmap and uses that as texture to display.
         */
        void renderText() noexcept;

        /**
         * @brief Creates a new bitmap.
         */
        void createBitmap() noexcept;

    private:
        /**
         * @brief The text that should be displayed.
         */
        std::string mText;

        /**
         * @brief The font that should be used.
         */
        font::Font* pFont = nullptr;

        /**
         * @brief The font size.
         */
        font::size_t mFontSize = 12;

        /**
         * @brief The vertical align.
         */
        gfx::VerticalAlign mVerticalAlign = gfx::VerticalAlign::Middle;

        /**
         * @brief The horizontal align.
         */
        gfx::HorizontalAlign mHorizontalAlign = gfx::HorizontalAlign::Center;

        /**
         * @brief The texture.
         */
        std::shared_ptr<gfx::Texture> mTexture;

        /**
         * @brief The bitmap.
         */
        std::unique_ptr<gfx::Bitmap> mBitmap;

        /**
         * @brief Defines that the bitmap should auto resize depending on the needed space of the font renderer.
         */
        bool mBitmapAutoResize = false;
    };

}

#endif