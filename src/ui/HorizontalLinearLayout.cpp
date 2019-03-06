#include <ananasgfx/ui/HorizontalLinearLayout.hpp>

namespace ui {

    densityPixel_t HorizontalLinearLayout::getFullSpace() noexcept {
        return this->toHorizontalDp(this->mSize.x);
    }

    densityPixel_t HorizontalLinearLayout::getFixedSpace(Node *pNode) noexcept {
        return pNode->getFixedSize()->x + pNode->getMargin().getHorizontal();
    }

    densityPixel_t HorizontalLinearLayout::getMinSpace(Node *pNode) noexcept {
        return pNode->getMinSize()->x + pNode->getMargin().getHorizontal();
    }

    densityPixel_t HorizontalLinearLayout::getMaxSpace(Node *pNode) noexcept {
        return pNode->getMaxSize()->x + pNode->getMargin().getHorizontal();
    }

    void HorizontalLinearLayout::distribute(const std::unordered_map<Node *, densityPixel_t> &children) noexcept {
        float offset = 0.0f;
        for (auto& child : getUiChildren()) {
            if (children.count(child)) {
                auto width = children.at(child);
                child->setSize(
                        toHorizontalPixel(width - child->getMargin().getHorizontal()),
                        this->mSize.y - toVerticalPixel(child->getMargin().getVertical()));
                child->setPosition(
                        offset + toHorizontalPixel(child->getMargin().getLeft()),
                        toVerticalPixel(child->getMargin().getTop()));
                offset += child->getSize().x + toHorizontalPixel(child->getMargin().getHorizontal());
            }

        }
    }
}
