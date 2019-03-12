#ifndef UI_LAYOUT_HORIZONTALLINEAR_H
#define UI_LAYOUT_HORIZONTALLINEAR_H

#include "Linear.hpp"

namespace ui::layout {

    class HorizontalLinear : public Linear {
    public:
        densityPixel_t getFullSpace(ui::Container* container) noexcept override;

        densityPixel_t getFixedSpace(Node *pNode) noexcept override;

        densityPixel_t getMinSpace(Node *pNode) noexcept override;

        densityPixel_t getMaxSpace(Node* pNode) noexcept override;

        void distribute(ui::Container* container, const std::unordered_map<Node*,densityPixel_t>& children) noexcept override;
    };

}

#endif