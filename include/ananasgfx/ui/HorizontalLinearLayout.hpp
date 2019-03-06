#ifndef UI_HORIZONTALLINEARLAYOUT_H
#define UI_HORIZONTALLINEARLAYOUT_H

#include "LinearLayout.hpp"

namespace ui {

    class HorizontalLinearLayout : public LinearLayout {
    public:

    private:
        densityPixel_t getFullSpace() noexcept override;

        densityPixel_t getFixedSpace(Node *pNode) noexcept override;

        densityPixel_t getMinSpace(Node *pNode) noexcept override;

        densityPixel_t getMaxSpace(Node* pNode) noexcept override;

        void distribute(const std::unordered_map<Node*,densityPixel_t>& children) noexcept override;
    };

}

#endif