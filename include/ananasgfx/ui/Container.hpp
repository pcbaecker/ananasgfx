#ifndef UI_CONTAINER_H
#define UI_CONTAINER_H

#include "Node.hpp"
#include "layout/Layout.hpp"

namespace d2 {
    class Rectangle;
}

namespace ui {

    class PopUpView;

    class Container : public Node {
    public:
        bool init() noexcept override;
        const std::list<Node*>& getUiChildren() const noexcept;
        void setBackground(d2::Node* pNode) noexcept;

        void setSize(float x, float y) noexcept override;

        bool hasPopUpView() const noexcept;

        template <class T> T* createLayout() noexcept {
            static_assert(std::is_base_of<layout::Layout, T>::value, "Must derive from ui::layout::Layout");

            this->mLayout = std::make_unique<T>();
            return dynamic_cast<T*>(this->mLayout.get());
        }

        densityPixel_t getOptimalHeight(densityPixel_t width) noexcept override;

        densityPixel_t getOptimalWidth(densityPixel_t height) noexcept override;

        /**
         * @brief Called when a touch begins.
         *
         * @param touch The touch object.
         */
        void onTouchBegan(gfx::Touch& touch) noexcept override;

        /**
         * @brief Called when a touch moves.
         *
         * @param touch The touch object.
         */
        void onTouchMoved(gfx::Touch& touch) noexcept override;

        /**
         * @brief Called when a touch ends.
         *
         * @param touch The touch object.
         */
        void onTouchEnded(gfx::Touch& touch) noexcept override;

    private:
        void onChildAdded(gfx::Node* pNode) noexcept override;

        void onChildRemoved(gfx::Node* node) noexcept override;


        void showPopUpView() noexcept;

    private:
        std::list<PopUpView*> mPopUpViews;
        std::unique_ptr<layout::Layout> mLayout;
        std::list<Node*> mUiChildren;
        std::optional<d2::Node*> mBackground;
        std::optional<d2::Rectangle*> mOverlay;
    };
}

#endif