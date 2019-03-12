#ifndef UI_LAYOUT_LINEAR_H
#define UI_LAYOUT_LINEAR_H

#include <unordered_map>
#include <ananasgfx/ui/Node.hpp>
#include "Layout.hpp"

namespace ui::layout {

    class Linear : public Layout {
    public:
        bool arrangeChildren(ui::Container* container) noexcept override;

        virtual densityPixel_t getFullSpace(ui::Container* container) noexcept = 0;
        virtual densityPixel_t getFixedSpace(Node* pNode) noexcept = 0;
        virtual densityPixel_t getMinSpace(Node* pNode) noexcept = 0;
        virtual densityPixel_t getMaxSpace(Node* pNode) noexcept = 0;
        virtual void distribute(ui::Container* container, const std::unordered_map<Node*,densityPixel_t>& children) noexcept = 0;
    };

}

#endif