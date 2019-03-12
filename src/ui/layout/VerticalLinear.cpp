#include <ananasgfx/ui/layout/VerticalLinear.hpp>
#include <ananasgfx/ui/Container.hpp>

namespace ui::layout {

    densityPixel_t VerticalLinear::getFullSpace(ui::Container* container) noexcept {
        return container->toVerticalDp(container->getSize().y);
    }

    densityPixel_t VerticalLinear::getFixedSpace(Node *pNode) noexcept {
        return pNode->getFixedSize()->y + pNode->getMargin().getVertical();
    }

    densityPixel_t VerticalLinear::getMinSpace(Node *pNode) noexcept {
        return pNode->getMinSize()->y + pNode->getMargin().getVertical();
    }

    densityPixel_t VerticalLinear::getMaxSpace(Node *pNode) noexcept {
        return pNode->getMaxSize()->y + pNode->getMargin().getVertical();
    }

    void VerticalLinear::distribute(ui::Container* container, const std::unordered_map<Node *, densityPixel_t> &children) noexcept {
        float offset = 0.0f;
        for (auto& child : container->getUiChildren()) {
            if (children.count(child)) {
                auto height = children.at(child);
                child->setSize(
                        container->getSize().x - container->toHorizontalPixel(child->getMargin().getHorizontal()),
                        container->toVerticalPixel(height - child->getMargin().getVertical()));
                child->setPosition(
                        container->toHorizontalPixel(child->getMargin().getLeft()),
                        offset + container->toVerticalPixel(child->getMargin().getTop()));
                offset += child->getSize().y + container->toVerticalPixel(child->getMargin().getVertical());
            }

        }
    }

}