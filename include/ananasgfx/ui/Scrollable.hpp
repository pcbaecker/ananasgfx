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

        /**
         * @brief Called when a touch begins.
         *
         * @param x The X-Coordinate in parent space.
         * @param y The Y-Coordinate in parent space.
         * @param touch The touch object.
         */
        void onTouchBegan(float x, float y, const gfx::Touch& touch) noexcept override;

        /**
         * @brief Called when a touch moves.
         *
         * @param x The X-Coordinate in parent space.
         * @param y The Y-Coordinate in parent space.
         * @param touch The touch object.
         */
        void onTouchMoved(float x, float y, const gfx::Touch& touch) noexcept override;

        /**
         * @brief Called when a touch ends.
         *
         * @param x The X-Coordinate in parent space.
         * @param y The Y-Coordinate in parent space.
         * @param touch The touch object.
         */
        void onTouchEnded(float x, float y,const gfx::Touch& touch) noexcept override;

    private:
        gfx::ClippingNode* pClippingNode = nullptr;
        ui::Node* pScrollnode = nullptr;
        float mLastTouchY = 0.0f;
    };

}

#endif