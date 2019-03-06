#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "Node.hpp"

namespace d2 {
    class Node;
}

namespace ui {

    class Button : public Node {
    public:
        Button() noexcept;

        bool init() noexcept override;

        void setSize(float x, float y) noexcept override;

        void setColor(glm::vec4 color) noexcept;

        void onTouchBegan(const float x, const float y, const gfx::Touch &touch) noexcept override;

    private:
        d2::Node* pBackground = nullptr;
        glm::vec4 mColor;
    };

}

#endif