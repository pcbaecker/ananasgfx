#include <ananasgfx/ui/TextButton.hpp>

namespace ui {

    void TextButton::setText(std::string text) noexcept {
        this->mText = std::move(text);
    }

    const std::string &TextButton::getText() const noexcept {
        return this->mText;
    }

}