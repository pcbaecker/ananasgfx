#include <ananasgfx/ui/layout/HorizontalLinear.hpp>
#include <ananasgfx/ui/Container.hpp>

namespace ui::layout {

    densityPixel_t HorizontalLinear::getFullSpace(ui::Container* container) noexcept {
        return container->toHorizontalDp(container->getSize().x);
    }

    densityPixel_t HorizontalLinear::getFixedSpace(Node *pNode) noexcept {
        return pNode->getFixedSize()->x + pNode->getMargin().getHorizontal();
    }

    densityPixel_t HorizontalLinear::getMinSpace(Node *pNode) noexcept {
        return pNode->getMinSize()->x + pNode->getMargin().getHorizontal();
    }

    densityPixel_t HorizontalLinear::getMaxSpace(Node *pNode) noexcept {
        return pNode->getMaxSize()->x + pNode->getMargin().getHorizontal();
    }

    void HorizontalLinear::distribute(ui::Container* container, const std::unordered_map<Node *, densityPixel_t> &children) noexcept {
        float offset = 0.0f;
        for (auto& child : container->getUiChildren()) {
            if (children.count(child)) {
                auto width = children.at(child);
                child->setSize(
                        container->toHorizontalPixel(width - child->getMargin().getHorizontal()),
                        container->getSize().y - container->toVerticalPixel(child->getMargin().getVertical()));
                child->setPosition(
                        offset + container->toHorizontalPixel(child->getMargin().getLeft()),
                        container->toVerticalPixel(child->getMargin().getTop()));
                offset += child->getSize().x + container->toHorizontalPixel(child->getMargin().getHorizontal());
            }

        }
    }

}