#include <ananasgfx/ui/Container.hpp>
#include <map>
#include <ee/Log.hpp>
#include <ananasgfx/ui/layout/VerticalLinear.hpp>

namespace ui {

    bool Container::init() noexcept {
        if (!this->mLayout) {
            createLayout<ui::layout::VerticalLinear>();
        }
        this->mLayout->arrangeChildren(this);

        if (this->mBackground) {
            (*this->mBackground)->setSize(this->mSize);
        }
        return Node::init();
    }

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

    void Container::setBackground(d2::Node *pNode) noexcept {
        // Make sure background is a child of this node
        if (std::find(this->mChildren2d.begin(), this->mChildren2d.end(), pNode) == this->mChildren2d.end()) {
            // The given background is not a child of this node
            WARN("The given background is not a child of this node", {});
            return;
        }

        // Store the given background node
        this->mBackground = pNode;
    }

    void Container::setSize(float x, float y) noexcept {
        Node::setSize(x, y);

        // Propagate the new size to the background
        if (this->mBackground) {
            (*this->mBackground)->setSize(x,y);
        }
    }


}
