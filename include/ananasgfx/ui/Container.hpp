#ifndef UI_CONTAINER_H
#define UI_CONTAINER_H

#include "Node.hpp"

namespace ui {

    //enum Orientation {Vertical = 0, Horizontal = 1};

    class Container : public Node {
    public:
        const std::list<Node*>& getUiChildren() const noexcept;
    private:
        void onChildAdded(gfx::Node* pNode) noexcept override;

    private:
        std::list<Node*> mUiChildren;
    };


}

#endif