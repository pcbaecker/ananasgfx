#include <ananasgfx/ui/LinearLayout.hpp>

namespace ui {

    bool LinearLayout::init() noexcept {
        if (!arrangeChildren()) {
            return false;
        }

        return Container::init();
    }

    bool LinearLayout::arrangeChildren() noexcept {
        std::unordered_map<Node*,densityPixel_t> children;
        densityPixel_t remainingSpace = getFullSpace();

        // Go through all children
        for (auto& child : this->getUiChildren()) {
            // Check if we have a fixed size
            if (child->getFixedSize().has_value()) {
                auto fixedSpace = getFixedSpace(child);
                children.emplace(child, fixedSpace);
                remainingSpace -= fixedSpace;
            }
        }
        if (remainingSpace < 0) {
            return false;
        }

        // Find minSize collisions
        if (this->getUiChildren().size() - children.size() != 0) {
            densityPixel_t spacePerItem = static_cast<densityPixel_t>(
                    remainingSpace / (this->getUiChildren().size() - children.size()));

            for (auto& child : this->getUiChildren()) {
                if (children.count(child) == 0
                    && child->getMinSize().has_value()) {
                    auto minSpace = getMinSpace(child);
                    if (minSpace > spacePerItem) {
                        children.emplace(child, minSpace);
                        remainingSpace -= minSpace;
                    }
                }
            }
            if (remainingSpace < 0) {
                return false;
            }
        }

        // Distribute the remaining space
        if (this->getUiChildren().size() - children.size() != 0) {
            densityPixel_t space = static_cast<densityPixel_t>(
                    remainingSpace / (this->getUiChildren().size() - children.size()));

            for (auto& child : this->getUiChildren()) {
                    if (children.count(child) == 0) {
                    children.emplace(child, space);
                    remainingSpace -= space;
                }
            }
        }

        // Find maxSize collisions
        for (auto& child : children) {
            if (child.first->getMaxSize().has_value()) {
                auto maxSpace = getMaxSpace(child.first);
                if (maxSpace < child.second) {
                    remainingSpace += child.second - maxSpace;
                    child.second = maxSpace;
                }
            }
        }

        // Distribute the rest
        if (remainingSpace > 0) {
            for (auto& child : children) {
                if (!child.first->getFixedSize().has_value()) {
                    if (child.first->getMaxSize().has_value()) {
                        auto maxSpace = getMaxSpace(child.first);
                        auto addable = maxSpace - child.second;
                        if (addable > 0) {
                            child.second += addable;
                            remainingSpace -= addable;
                        }
                    } else {
                        child.second += remainingSpace;
                        remainingSpace = 0;
                    }
                }

                if (remainingSpace <= 0) {
                    break;
                }
            }
        }

        // Apply the distributed widths to the ui::Nodes
        distribute(children);
        return true;
    }
}