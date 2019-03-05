#ifndef UI_NODE_H
#define UI_NODE_H

#include <ananasgfx/d2/Node.hpp>

#include "Margin.hpp"

namespace ui {

    class Node : public d2::Node {
    public:
        virtual vec2 getOptimalSize(const vec2& constraint) noexcept;

        std::optional<vec2> getFixedSize() const noexcept;

        std::optional<vec2> getMinSize() const noexcept;

        void setMinSize(vec2 minSize) noexcept;

        std::optional<vec2> getMaxSize() const noexcept;

        void setMaxSize(vec2 maxSize) noexcept;

        float toHorizontalPixel(densityPixel_t dp) const noexcept;

        float toVerticalPixel(densityPixel_t dp) const noexcept;

        densityPixel_t toHorizontalDp(float pixel) const noexcept;

        densityPixel_t toVerticalDp(float pixel) const noexcept;

        glm::vec2 toPixel(const vec2& dp) const noexcept;

        Margin& getMargin() noexcept;

    protected:
        Margin mMargin;
        std::optional<vec2> mFixedSize;
        std::optional<vec2> mMinSize;
        std::optional<vec2> mMaxSize;
    };

}

#endif