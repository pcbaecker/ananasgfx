#include <ananasgfx/d2/Label.hpp>
#include <ananasgfx/font/FontRenderer.hpp>
#include <ananasgfx/gfx/Window.hpp>

namespace d2 {

    bool Label::init() noexcept {

        auto font = this->pWindow->getFontManager().get("Roboto", "Bold");
        if (!font.has_value()) {
            std::cerr << "Font get fail" << std::endl;
            return false;
        }

        unsigned short w = this->mSize.x;
        unsigned short h = this->mSize.y;
        gfx::Bitmap bitmap(malloc(w*h), w, h, 1);
        bitmap.clear();
        font::FontRenderer::render(this->mText, *font, 24, bitmap, gfx::HorizontalAlign::Center, gfx::VerticalAlign::Middle);
        std::cout << bitmap.getWidth() << std::endl;

        auto texture = gfx::Texture::create(this->pWindow->getRenderer(), bitmap);
        if (!texture.has_value()) {
            std::cerr << "Texture get fail" << std::endl;
            return false;
        }
        this->mTexture = *texture;

        this->setTexture(this->mTexture.get());

        return Sprite::init();
    }

    void Label::setText(std::string text) noexcept {
        this->mText = std::move(text);
    }

    const std::string &Label::getText() const noexcept {
        return this->mText;
    }

}