#include <ananasgfx/ui/PopUpView.hpp>

namespace ui {

    bool PopUpView::init() noexcept {
        auto parent = dynamic_cast<d2::Node*>(this->pParent);
        float widthAvailable = 0.0;
        if (parent) {
            widthAvailable = parent->getSize().x;
        }

        // Get the width
        auto minSize = this->getMinSize();
        float width = 0.0f, height = 0.0f;
        if (minSize.has_value()) {
            width = toHorizontalPixel(minSize->x);
            float availableWidth = widthAvailable - toHorizontalPixel(this->getMargin().getHorizontal());
            if (width > availableWidth) {
                width = availableWidth;
            }
        }

        // Get the height
        height = toVerticalPixel(this->getOptimalHeight(toHorizontalDp(width)));
        float minHeight = toVerticalPixel(minSize->y);
        if (minSize.has_value() && height < minHeight) {
            height = minHeight;
        }

        this->setSize(width, height);

        return Container::init();
    }

    void PopUpView::outsideTouched() noexcept {
        if (this->mOutsideTouchCallback) {
            this->mOutsideTouchCallback(this);
        }
    }

    void PopUpView::setOutsideTouchCallback(std::function<void(PopUpView *)> callback) {
        this->mOutsideTouchCallback = callback;
    }
}