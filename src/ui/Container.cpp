#include <ananasgfx/ui/Container.hpp>
#include <map>

namespace ui {

    void Container::onChildAdded(gfx::Node *pNode) noexcept {
        ui::Node::onChildAdded(pNode);

        // Try to cast the child to a ui node
        auto node = dynamic_cast<Node*>(pNode);
        if (node != nullptr) {
            this->mUiChildren.push_back(node);
        }
    }

    const std::list<Node *> &Container::getUiChildren() const noexcept {
        return this->mUiChildren;
    }



}
