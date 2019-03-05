#include <ananasgfx/ui/View.hpp>
#include <map>

namespace ui {

    void View::onChildAdded(gfx::Node *pNode) noexcept {
        // Try to cast the child to a ui node
        auto node = dynamic_cast<Node*>(pNode);
        if (node != nullptr) {
            this->mUiChildren.push_back(node);
        }
    }

    const std::list<Node *> &View::getUiChildren() const noexcept {
        return this->mUiChildren;
    }

    bool LinearLayout::init() noexcept {
        if (this->mOrientation == Orientation::Horizontal) {

            std::map<Node*,densityPixel_t> children;
            densityPixel_t remainingWidth = this->toHorizontalDp(this->mSize.x);

            // Go through all children
            for (auto& child : this->getUiChildren()) {
                // Check if we have a fixed size
                if (child->getFixedSize().has_value()) {
                    auto fixedWidth = child->getFixedSize()->x + child->getMargin().getHorizontal();
                    children.emplace(child, fixedWidth);
                    remainingWidth -= fixedWidth;
                }
            }
            if (remainingWidth < 0) {
                return false;
            }

            // Find minSize collisions
            if (this->getUiChildren().size() - children.size() != 0) {
                densityPixel_t width = static_cast<densityPixel_t>(
                        remainingWidth / (this->getUiChildren().size() - children.size()));

                for (auto& child : this->getUiChildren()) {
                    if (children.count(child) == 0
                    && child->getMinSize().has_value()) {
                        auto minWidth = child->getMinSize()->x + child->getMargin().getHorizontal();
                        if (minWidth > width) {
                            children.emplace(child, minWidth);
                            remainingWidth -= minWidth;
                        }
                    }
                }
                if (remainingWidth < 0) {
                    return false;
                }
            }

            // Distribute the remaining width
            if (this->getUiChildren().size() - children.size() != 0) {
                densityPixel_t width = static_cast<densityPixel_t>(
                        remainingWidth / (this->getUiChildren().size() - children.size()));

                for (auto& child : this->getUiChildren()) {
                    if (children.count(child) == 0) {
                        children.emplace(child, width);
                        remainingWidth -= width;
                    }
                }
            }

            // Find maxSize collisions
            for (auto& child : children) {
                if (child.first->getMaxSize().has_value()) {
                    auto maxWidth = child.first->getMaxSize()->x + child.first->getMargin().getHorizontal();
                    if (maxWidth < child.second) {
                        remainingWidth += child.second - maxWidth;
                        child.second = maxWidth;
                    }
                }
            }

            // Distribute the rest
            if (remainingWidth > 0) {
                for (auto& child : children) {
                    if (!child.first->getFixedSize().has_value()) {
                        if (child.first->getMaxSize().has_value()) {
                            auto maxWidth = child.first->getMaxSize()->x + child.first->getMargin().getHorizontal();
                            auto addable = maxWidth - child.second;
                            if (addable > 0) {
                                child.second += addable;
                                remainingWidth -= addable;
                            }
                        } else {
                            child.second += remainingWidth;
                            remainingWidth = 0;
                        }
                    }

                    if (remainingWidth <= 0) {
                        break;
                    }
                }
            }

            // Apply the distributed widths to the ui::Nodes
            float offset = 0.0f;
            for (auto& child : children) {
                child.first->setSize(
                        toHorizontalPixel(child.second - child.first->getMargin().getHorizontal()),
                        this->mSize.y - toVerticalPixel(child.first->getMargin().getVertical()));
                child.first->setPosition(
                        offset + toHorizontalPixel(child.first->getMargin().getLeft()),
                        toVerticalPixel(child.first->getMargin().getTop()));
                offset += child.first->getSize().x + toHorizontalPixel(child.first->getMargin().getHorizontal());
            }

/*
            auto w = this->mSize.x / this->getUiChildren().size();
            float x = 0.0f;
            for (auto& child : this->getUiChildren()) {
                child->setSize(w, this->mSize.y);
                child->setPosition(x, 0.0f);
                x += w;
            }*/
        } else {

        }

        return View::init();
    }

}
