#include <ananasgfx/ui/Button.hpp>
#include <ananasgfx/d2/Rectangle.hpp>

namespace ui {

    Button::Button() noexcept {
        this->mMinSize = vec2(16,16);
    }

    void Button::setSize(float x, float y) noexcept {
        Node::setSize(x, y);

        if (this->pBackground) {
            this->pBackground->setSize(x,y);
        }
    }

    void Button::setColor(glm::vec4 color) noexcept {
        this->mColor = color;
    }

    bool Button::init() noexcept {
        auto rect = this->createChild<d2::Rectangle>();
        rect->setColor(this->mColor);
        this->pBackground = rect;
        this->pBackground->setSize(this->mSize);

        return Node::init();
    }

}