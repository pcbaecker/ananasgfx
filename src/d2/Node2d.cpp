#include <ananasgfx/d2/Node.hpp>

#include <iostream>

namespace d2 {

    bool Node::init() noexcept {
        // Update parent position and rotation offset of our children
        this->updateChildrenPositionOffset();
        this->updateChildrenRotationOffset();

        return gfx::Node::init();
    }

    void Node::setPosition(float x, float y) noexcept {
        this->mPosition.x = x;
        this->mPosition.y = y;

        if (isInitialized()) {
            // Update parent position offset of our children
            this->updateChildrenPositionOffset();
        }
    }

    void Node::setPosition(const glm::vec2 &position) noexcept {
        this->setPosition(position.x, position.y);
    }

    const glm::vec2 &Node::getPosition() const noexcept {
        return this->mPosition;
    }

    void Node::setScale(float x, float y) noexcept {
        this->mScale.x = x;
        this->mScale.y = y;
    }

    void Node::setScale(float scale) noexcept {
        this->setScale(scale, scale);
    }

    void Node::setScale(const glm::vec2 &scale) noexcept {
        this->setScale(scale.x, scale.y);
    }

    const glm::vec2 &Node::getScale() const noexcept {
        return this->mScale;
    }

    void Node::setRotation(float rotation) noexcept {
        this->mRotation = rotation;

        if (isInitialized()) {
            // Update children rotation
            this->updateChildrenRotationOffset();
        }
    }

    float Node::getRotation() const noexcept {
        return this->mRotation;
    }

    void Node::setSize(float x, float y) noexcept {
        this->mSize.x = x;
        this->mSize.y = y;

        if (isInitialized()) {
            // Update parent position offset of our children
            this->updateChildrenPositionOffset();
        }
    }

    void Node::setSize(const glm::vec2 &size) noexcept {
        this->setSize(size.x, size.y);
    }

    const glm::vec2 &Node::getSize() const noexcept {
        return this->mSize;
    }

    void Node::setAnchorPoint(float x, float y) noexcept {
        this->mAnchorPoint.x = x;
        this->mAnchorPoint.y = y;

        if (isInitialized()) {
            // Update parent position offset of our children
            this->updateChildrenPositionOffset();
        }
    }

    void Node::setAnchorPoint(const glm::vec2 &anchorPoint) noexcept {
        this->setAnchorPoint(anchorPoint.x, anchorPoint.y);
    }

    const glm::vec2 &Node::getAnchorPoint() const noexcept {
        return this->mAnchorPoint;
    }

    void Node::setParentPositionOffset(float x, float y) noexcept {
        this->mParentPositionOffset.x = x;
        this->mParentPositionOffset.y = y;

        if (isInitialized()) {
            // Update parent position offset of our children
            this->updateChildrenPositionOffset();
        }
    }

    void Node::setParentPositionOffset(const glm::vec2 &offset) noexcept {
        this->setParentPositionOffset(offset.x, offset.y);
    }

    const glm::vec2 &Node::getParentPositionOffset() const noexcept {
        return this->mParentPositionOffset;
    }

    void Node::onChildAdded(gfx::Node *pNode) noexcept {
        // Try to cast the added node as a 2d node
        auto* p2dNode = dynamic_cast<d2::Node*>(pNode);

        // Check if the added child is a 2d one
        if (p2dNode != nullptr) {
            // Add the child to the list of 2d children
            this->mChildren2d.push_back(p2dNode);

            // If this node is already initialized, we have to initialize the newly added child node
            if (isInitialized()) {
                this->updateChildrenPositionOffset(p2dNode);
                this->updateChildrenRotationOffset(p2dNode);

            }
        }
    }

    glm::vec2 Node::getScreenPosition() const noexcept {
        return glm::vec2(
                this->mParentPositionOffset.x + this->mPosition.x,
                this->mParentPositionOffset.y + this->mPosition.y
                );
    }

    void Node::setParentRotationOffset(float rotation) noexcept {
        this->mParentRotationOffset = rotation;

        if (isInitialized()) {
            // Update children rotation
            this->updateChildrenRotationOffset();
        }
    }

    float Node::getParentRotationOffset() const noexcept {
        return this->mParentRotationOffset;
    }

    void Node::updateChildrenPositionOffset(d2::Node* pNode) const noexcept {
        // Calculate the offset
        auto offset = this->getScreenPosition();
        offset.x -= this->mAnchorPoint.x * this->mSize.x;
        offset.y -= this->mAnchorPoint.y * this->mSize.y;

        // Check if a node is given
        if (pNode != nullptr) {
            // A special node is given, we only update this one
            pNode->setParentPositionOffset(offset);
        } else {
            // No node given, that means we want to update all children
            for (auto& child : this->mChildren2d) {
                child->setParentPositionOffset(offset);
            }
        }
    }

    void Node::updateChildrenRotationOffset(d2::Node *pNode) const noexcept {
        // Calculate offset
        float offset = this->mParentRotationOffset + this->mRotation;

        // Check if a node is given
        if (pNode != nullptr) {
            // A special node is given, we only update this one
            pNode->setParentRotationOffset(offset);
        } else {
            // No node given, that means we want to update all children
            for (auto& child : this->mChildren2d) {
                child->setParentRotationOffset(offset);
            }
        }
    }

    void Node::setZIndex(uint8_t zindex) noexcept {
        this->mZIndex = zindex;
    }
}