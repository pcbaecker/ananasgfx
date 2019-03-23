#ifndef UI_SCROLLABLE_H
#define UI_SCROLLABLE_H

#include <ananasgfx/gfx/ClippingNode.hpp>

#include "Node.hpp"

namespace ui {

    class Scrollable : public Node {
    public:

        bool init() noexcept override;

        template <class T> T* createChild() noexcept {
            if (this->pClippingNode == nullptr) {
                this->pClippingNode = gfx::Node::createChild<gfx::ClippingNode>();
            }

            auto node = this->pClippingNode->createChild<T>();
            this->pScrollnode = node;
            return node;
        }

    private:
        gfx::ClippingNode* pClippingNode = nullptr;
        ui::Node* pScrollnode = nullptr;
        float mLastTouchY = 0.0f;
    };

}

#endif