#include <ananasgfx/ui/Button.hpp>
#include <ananasgfx/d2/Rectangle.hpp>

namespace ui {

    Button::Button() noexcept {
        this->mMinSize = vec2(16,16);
    }

    void Button::setSize(float x, float y) noexcept {
        Node::setSize(x, y);
        _setSize(x,y);
    }

    bool Button::init() noexcept {
        if (!_init(this->mSize)) {
            return false;
        }
        return Node::init();
    }

    void Button::onTouchBegan(gfx::Touch &touch) noexcept {
        Touchable::touchBegins();

        touch.registerHandler(gfx::Touch::Type::End, [this](gfx::Touch&t) {
            auto pos = t.getLocalLast(this);

            Touchable::touchEnds(0.0f < pos.x && pos.x < this->mSize.x
                                 && 0.0f < pos.y && pos.y < this->mSize.y);
        });
    }
}