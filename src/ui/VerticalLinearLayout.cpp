#include <ananasgfx/ui/VerticalLinearLayout.hpp>

namespace ui {

    densityPixel_t VerticalLinearLayout::getFullSpace() noexcept {
        return this->toVerticalDp(this->mSize.y);
    }

    densityPixel_t VerticalLinearLayout::getFixedSpace(Node *pNode) noexcept {
        return pNode->getFixedSize()->y + pNode->getMargin().getVertical();
    }

    densityPixel_t VerticalLinearLayout::getMinSpace(Node *pNode) noexcept {
        return pNode->getMinSize()->y + pNode->getMargin().getVertical();
    }

    densityPixel_t VerticalLinearLayout::getMaxSpace(Node *pNode) noexcept {
        return pNode->getMaxSize()->y + pNode->getMargin().getVertical();
    }

    void VerticalLinearLayout::distribute(const std::unordered_map<Node *, densityPixel_t> &children) noexcept {
        float offset = 0.0f;
        for (auto& child : getUiChildren()) {
            if (children.count(child)) {
                auto height = children.at(child);
                child->setSize(
                        this->mSize.x - toHorizontalPixel(child->getMargin().getHorizontal()),
                        toVerticalPixel(height - child->getMargin().getVertical()));
                child->setPosition(
                        toHorizontalPixel(child->getMargin().getLeft()),
                        offset + toVerticalPixel(child->getMargin().getTop()));
                offset += child->getSize().y + toVerticalPixel(child->getMargin().getVertical());
            }

        }
    }
}
