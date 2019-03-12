#include <ananasgfx/ui/Node.hpp>
#include <ananasgfx/gfx/Window.hpp>

namespace ui {

    Node::Node() noexcept {
        this->mZIndex = 128;
    }

    densityPixel_t Node::toHorizontalDp(float pixel) const noexcept {
        return static_cast<densityPixel_t>((160.0f * pixel) / this->pWindow->getHorizontalDpi());
    }

    densityPixel_t Node::toVerticalDp(float pixel) const noexcept {
        return static_cast<densityPixel_t>((160.0f * pixel) / this->pWindow->getVerticalDpi());
    }

    glm::vec2 Node::toPixel(const vec2 &dp) const noexcept {
        return glm::vec2(
                this->toHorizontalPixel(dp.x),
                this->toVerticalPixel(dp.y)
                );
    }

    float Node::toHorizontalPixel(densityPixel_t dp) const noexcept {
        return (dp * this->pWindow->getHorizontalDpi()) / 160.0f;
    }

    float Node::toVerticalPixel(densityPixel_t dp) const noexcept {
        return (dp * this->pWindow->getVerticalDpi()) / 160.0f;
    }

    std::optional<vec2> Node::getFixedSize() const noexcept {
        return this->mFixedSize;
    }

    void Node::setFixedSize(vec2 fixSize) noexcept {
        this->mFixedSize = fixSize;
    }

    std::optional<vec2> Node::getMinSize() const noexcept {
        return this->mMinSize;
    }

    void Node::setMinSize(vec2 minSize) noexcept {
        this->mMinSize = minSize;
    }

    std::optional<vec2> Node::getMaxSize() const noexcept {
        return this->mMaxSize;
    }

    void Node::setMaxSize(vec2 maxSize) noexcept {
        this->mMaxSize = maxSize;
    }

    Margin &Node::getMargin() noexcept {
        return this->mMargin;
    }
}