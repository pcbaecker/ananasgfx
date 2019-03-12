#include <ananasgfx/ui/ListItem.hpp>
#include <ee/Log.hpp>

namespace ui {

    bool ListItem::init() noexcept {
        /*this->pLayout = this->createLayout();
        if (this->pLayout == nullptr) {
            WARN("Layout container must not be nullptr", {});
            return false;
        }
        this->pLayout->setSize(this->mSize.x, this->mSize.y);
*/
        if (!_init(this->mSize)) {
            return false;
        }

        return ui::Container::init();
    }

    void ListItem::onTouchBegan(float x, float y, const gfx::Touch &touch) noexcept {
        ui::Container::onTouchBegan(x, y, touch);

        Touchable::touchBegins(touch);
    }

    void ListItem::onTouchEnded(float x, float y, const gfx::Touch &touch) noexcept {
        ui::Container::onTouchEnded(x, y, touch);

        Touchable::touchEnds();
    }

}