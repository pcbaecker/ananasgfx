#include <ananasgfx/ui/Container.hpp>
#include <ananasgfx/ui/PopUpView.hpp>
#include <ananasgfx/d2/Rectangle.hpp>
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

        // Try to cast the child to a ui::PopUpView
        auto popUpView = dynamic_cast<PopUpView*>(pNode);
        if (popUpView != nullptr) {
            this->mPopUpViews.push_back(popUpView);
            this->showPopUpView();
        }
    }

    void Container::onChildRemoved(gfx::Node *pNode) noexcept {
        Node::onChildRemoved(pNode);

        // Try to cast the child to a ui node
        auto node = dynamic_cast<Node*>(pNode);
        if (node != nullptr) {
            this->mUiChildren.remove(node);
        }

        // Try to cast the child to a ui::PopUpView
        auto popUpView = dynamic_cast<PopUpView*>(pNode);
        if (popUpView != nullptr) {
            this->mPopUpViews.remove(popUpView);

            // Hide overlay
            if (this->mOverlay.has_value()) {
                (*this->mOverlay)->setVisible(false);
            }
        }
    }

    void Container::showPopUpView() noexcept {
        // Make sure that there is at least one PopUpView to display
        if (this->mPopUpViews.empty()) {
            WARN("There is no ui::PopUpView to display", {});
            return;
        }

        // Create overlay
        if (!this->mOverlay.has_value()) {
            auto overlay = createChild<d2::Rectangle>();
            overlay->setColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.75f));
            overlay->setZIndex(128);
            overlay->setSize(this->mSize.x, this->mSize.y);
            this->mOverlay = overlay;
        }
        (*this->mOverlay)->setVisible(true);

        // Get the pop up view to show
        auto* pPopUpView = *this->mPopUpViews.begin();
        pPopUpView->setZIndex(132);
        pPopUpView->setPosition(this->mSize.x * 0.5f, this->mSize.y * 0.5f);
        pPopUpView->setAnchorPoint(0.5f, 0.5f);

    }

    densityPixel_t Container::getOptimalHeight(densityPixel_t width) noexcept {
        densityPixel_t height = 0.0f;
        for (auto& child : this->mUiChildren) {
            height += child->getOptimalHeight(width);
        }
        return height;
    }

    densityPixel_t Container::getOptimalWidth(densityPixel_t height) noexcept {
        densityPixel_t width = 0.0f;
        for (auto& child : this->mUiChildren) {
            width += child->getOptimalWidth(height);
        }
        return width;
    }

    bool Container::hasPopUpView() const noexcept {
        return !this->mPopUpViews.empty();
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

    void Container::onTouchBegan(gfx::Touch &touch) noexcept {
        if (this->hasPopUpView()) {
            auto pos = touch.getLocalLast(this);
            auto popUpView = *this->mPopUpViews.begin();
            if (popUpView->contains(pos.x, pos.y)) {
                popUpView->onTouchBegan(touch);
            } else {
                // The touch is inside the container but outside of the PopUpView
                touch.registerHandler(gfx::Touch::Type::End, [this](gfx::Touch& t) {
                    if (this->hasPopUpView()) {
                        auto pos = t.getLocalLast(this);
                        auto popUpView = *this->mPopUpViews.begin();

                        if (!popUpView->contains(pos.x, pos.y)) {
                            popUpView->outsideTouched();
                        }
                    }
                });
            }
        } else {
            Node::onTouchBegan(touch);
        }
    }

    void Container::onTouchMoved(gfx::Touch &touch) noexcept {
        if (this->hasPopUpView()) {
            auto pos = touch.getLocalLast(this);
            auto popUpView = *this->mPopUpViews.begin();
            if (popUpView->contains(pos.x, pos.y)) {
                popUpView->onTouchMoved(touch);
            }
        } else {
            Node::onTouchMoved(touch);
        }
    }

    void Container::onTouchEnded(gfx::Touch &touch) noexcept {
        if (this->hasPopUpView()) {
            auto popUpView = *this->mPopUpViews.begin();
            auto pos = touch.getLocalLast(this);
            if (popUpView->contains(pos.x, pos.y)) {
                popUpView->onTouchEnded(touch);
            }
        } else {
            Node::onTouchEnded(touch);
        }
    }

}
