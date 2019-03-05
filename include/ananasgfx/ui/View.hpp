#ifndef UI_VIEW_H
#define UI_VIEW_H

#include "Node.hpp"

namespace ui {

    enum Orientation {Vertical = 0, Horizontal = 1};

    class View : public Node {
    public:


        const std::list<Node*>& getUiChildren() const noexcept;
    private:
        void onChildAdded(gfx::Node* pNode) noexcept override;

    private:
        std::list<Node*> mUiChildren;
    };

    class LinearLayout : public View {
    public:
        bool init() noexcept override;

    private:
        Orientation mOrientation = Horizontal;
    };
}

#endif