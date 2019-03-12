#include <ananasgfx/ui/Scrollable.hpp>
#include <ananasgfx/d2/Rectangle.hpp>

namespace ui {

    bool Scrollable::init() noexcept {
        if (this->pClippingNode) {
            auto rect = this->pClippingNode->createStencil<d2::Rectangle>();
            rect->setSize(this->mSize.x, this->mSize.y);
            auto pos = this->getScreenPosition();
            rect->setPosition(pos.x, pos.y);

            this->pScrollnode->setSize(this->mSize.x, this->mSize.y);
        }

        return Node::init();
    }

    void Scrollable::onTouchBegan(float x, float y, const gfx::Touch &touch) noexcept {
        if (this->pScrollnode) {
            this->pScrollnode->onTouchBegan(x,y,touch);
            this->mLastTouchY = y;
        }
    }

    void Scrollable::onTouchMoved(float x, float y, const gfx::Touch &touch) noexcept {
        if (this->pScrollnode) {
            this->pScrollnode->onTouchMoved(x,y,touch);

            float diff = -(this->mLastTouchY - y);
            this->mLastTouchY = y;
            this->pScrollnode->setPosition(
                    this->pScrollnode->getPosition().x,
                    this->pScrollnode->getPosition().y + diff);
        }
    }

    void Scrollable::onTouchEnded(float x, float y, const gfx::Touch &touch) noexcept {
        if (this->pScrollnode) {
            this->pScrollnode->onTouchEnded(x,y,touch);
        }
    }
}