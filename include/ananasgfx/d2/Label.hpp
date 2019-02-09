#ifndef D2_LABEL_H
#define D2_LABEL_H

#include <ananasgfx/gfx/Defines.hpp>
#include <ananasgfx/font/Font.hpp>

#include "Sprite.hpp"

namespace d2 {

    class Label : public Sprite {
    public:
        bool init() noexcept override;

        void setText(std::string text) noexcept;
        const std::string& getText() const noexcept;

        void setHorizontalAlign(gfx::HorizontalAlign align) noexcept;
        gfx::HorizontalAlign getHorizontalAlign() const noexcept;

        void setVerticalAlign(gfx::VerticalAlign align) noexcept;
        gfx::VerticalAlign getVerticalAlign() const noexcept;

        bool setFont(const std::string& fontFamily, const std::string& fontSubFamily) noexcept;
        font::Font* getFont() const noexcept;

        void setSize(float x, float y) noexcept override;

    private:
        void renderText() noexcept;
        void createBitmap() noexcept;

    private:
        std::string mText;
        font::Font* pFont = nullptr;
        font::size_t mFontSize = 12;
        gfx::VerticalAlign mVerticalAlign = gfx::VerticalAlign::Middle;
        gfx::HorizontalAlign mHorizontalAlign = gfx::HorizontalAlign::Center;
        std::shared_ptr<gfx::Texture> mTexture;
        std::unique_ptr<gfx::Bitmap> mBitmap;
    };

}

#endif