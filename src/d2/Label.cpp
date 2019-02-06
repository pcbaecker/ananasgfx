#include <ananasgfx/d2/Label.hpp>
#include <ananasgfx/font/FontRenderer.hpp>

namespace d2 {

    bool Label::init() noexcept {



        //font::FontRenderer::render(this->mText, );

//        this->setTexture();

        return Sprite::init();
    }

    void Label::setText(std::string text) noexcept {
        this->mText = std::move(text);
    }

    const std::string &Label::getText() const noexcept {
        return this->mText;
    }

}