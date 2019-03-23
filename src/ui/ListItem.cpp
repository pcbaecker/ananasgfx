#include <ananasgfx/ui/ListItem.hpp>
#include <ee/Log.hpp>

namespace ui {

    bool ListItem::init() noexcept {
        if (!_init(this->mSize)) {
            return false;
        }

        return ui::Container::init();
    }

    void ListItem::onTouchBegan(gfx::Touch &touch) noexcept {
        ui::Container::onTouchBegan(touch);

        Touchable::touchBegins();

        touch.registerHandler(gfx::Touch::Type::End, [this](gfx::Touch&t) {
            auto pos = t.getLocalLast(this);

            Touchable::touchEnds(0.0f < pos.x && pos.x < this->mSize.x
                                 && 0.0f < pos.y && pos.y < this->mSize.y);
        });
    }
}