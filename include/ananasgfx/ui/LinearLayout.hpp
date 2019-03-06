#ifndef UI_LINEARLAYOUT_H
#define UI_LINEARLAYOUT_H

#include "Container.hpp"
#include <unordered_map>

namespace ui {

    class LinearLayout : public Container {
    public:
        bool init() noexcept override;

        bool arrangeChildren() noexcept;

        virtual densityPixel_t getFullSpace() noexcept = 0;
        virtual densityPixel_t getFixedSpace(Node* pNode) noexcept = 0;
        virtual densityPixel_t getMinSpace(Node* pNode) noexcept = 0;
        virtual densityPixel_t getMaxSpace(Node* pNode) noexcept = 0;
        virtual void distribute(const std::unordered_map<Node*,densityPixel_t>& children) noexcept = 0;

    };

}

#endif