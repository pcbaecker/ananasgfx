#ifndef UI_CONTAINER_H
#define UI_CONTAINER_H

#include "Node.hpp"
#include "layout/Layout.hpp"

namespace ui {

    class Container : public Node {
    public:
        bool init() noexcept override;
        const std::list<Node*>& getUiChildren() const noexcept;
        void setBackground(d2::Node* pNode) noexcept;

        void setSize(float x, float y) noexcept override;

        template <class T> T* createLayout() noexcept {
            static_assert(std::is_base_of<layout::Layout, T>::value, "Must derive from ui::layout::Layout");

            this->mLayout = std::make_unique<T>();
            return dynamic_cast<T*>(this->mLayout.get());
        }

    private:
        void onChildAdded(gfx::Node* pNode) noexcept override;

    private:
        std::unique_ptr<layout::Layout> mLayout;
        std::list<Node*> mUiChildren;
        std::optional<d2::Node*> mBackground;
    };
}

#endif