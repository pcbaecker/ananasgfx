#include <ananasgfx/ui/TextButton.hpp>
#include <ananasgfx/d2/Label.hpp>

namespace ui {

    bool TextButton::init() noexcept {
        // Try to get the label
        this->pLabel = this->getLabel();

        // Adjust the label
        if (this->pLabel) {
            this->pLabel->setText(this->mText);
            this->pLabel->setAnchorPoint(0.0f, 0.0f);
            this->pLabel->setPosition(0.0f, 0.0f);
            this->pLabel->setSize(this->mSize.x, this->mSize.y);
            this->pLabel->setZIndex(99);
        }

        return Button::init();
    }

    void TextButton::setSize(float x, float y) noexcept {
        Button::setSize(x, y);

        if (this->pLabel) {
            this->pLabel->setSize(x,y);
        }
    }

    void TextButton::setText(std::string text) noexcept {
        this->mText = std::move(text);
    }

    const std::string &TextButton::getText() const noexcept {
        return this->mText;
    }

}