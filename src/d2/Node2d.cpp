#include <ananasgfx/d2/Node.hpp>
#include <ananasgfx/gfx/Window.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    void Node::onChildRemoved(gfx::Node *node) noexcept {
        // Try to cast the added node as a 2d node
        auto* p2dNode = dynamic_cast<d2::Node*>(node);

        // Check if the added child is a 2d one
        if (p2dNode != nullptr) {
            this->mChildren2d.remove(p2dNode);
        }
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

        if (this->pParent) {
            this->pParent->resortChildren();
        }
    }

    gfx::nodePriority_t Node::getPriority() const noexcept {
        return static_cast<gfx::nodePriority_t>(1024 + this->mZIndex);
    }

    std::shared_ptr<gfx::RenderTexture> Node::asRenderTexture() noexcept {
        // Store the original position and anchor point and set it for this method to zero
        auto originalPos = this->getPosition();
        auto originalAnchor = this->getAnchorPoint();
        this->setPosition(0.0f, 0.0f);
        this->setAnchorPoint(0.0f, 0.0f);

        // Set the viewport to the size of this node
        this->pWindow->getRenderer()->setViewport(static_cast<size_t>(this->getSize().x), static_cast<size_t>(this->getSize().y));
        this->pWindow->setTemporaryProjection2dMatrix(glm::ortho(0.0f, this->getSize().x, this->getSize().y, 0.0f));

        // Create a RenderTexture
        auto rendertexture = std::make_shared<gfx::RenderTexture>(
                this->pWindow, this->getSize().x, this->getSize().y);

        // Begin drawing into the rendertexture
        rendertexture->begin();
        this->pWindow->getRenderer()->clearScreen();

        // Draw this node and all children
        this->draw();

        // Finish drawing
        rendertexture->end();

        // Restore AnchorPoint and Position
        this->setPosition(originalPos);
        this->setAnchorPoint(originalAnchor);

        // Restore viewport
        this->pWindow->getRenderer()->setViewport(this->pWindow->getWidth(), this->pWindow->getHeight());
        this->pWindow->removeTemporaryProjection2dMatrix();

        return rendertexture;
    }

    uint8_t Node::getZIndex() const noexcept {
        return this->mZIndex;
    }

    void Node::onTouchBegan(gfx::Touch &touch) noexcept {
        auto pos = touch.getLocalLast(this);

        for (auto& child : this->mChildren2d) {
            if (child->contains(pos.x, pos.y)) {
                child->onTouchBegan(touch);
            }
        }

        //this->onTouchBegan(static_cast<float>(touch.getLastX()), static_cast<float>(touch.getLastY()), touch);
    }

    void Node::onTouchMoved(gfx::Touch &touch) noexcept {
        auto pos = touch.getLocalLast(this);

        for (auto& child : this->mChildren2d) {
            if (child->contains(pos.x, pos.y)) {
                child->onTouchMoved(touch);
            }
        }

        //this->onTouchMoved(static_cast<float>(touch.getLastX()), static_cast<float>(touch.getLastY()), touch);
    }

    void Node::onTouchEnded(gfx::Touch &touch) noexcept {
        auto pos = touch.getLocalLast(this);

        for (auto& child : this->mChildren2d) {
            if (child->contains(pos.x, pos.y)) {
                child->onTouchEnded(touch);
            }
        }

        //this->onTouchEnded(static_cast<float>(touch.getLastX()), static_cast<float>(touch.getLastY()), touch);
    }
/*
    void Node::onTouchBegan(const float x, const float y, const gfx::Touch &touch) noexcept {
        for (auto& child : this->mChildren2d) {
            if (child->contains(x,y)) {
                child->onTouchBegan(
                        x - child->getPosition().x + child->getAnchorPoint().x * child->getSize().x,
                        y - child->getPosition().y + child->getAnchorPoint().y * child->getSize().y,
                        touch);
            }
        }
    }

    void Node::onTouchMoved(const float x, const float y, const gfx::Touch &touch) noexcept {
        for (auto& child : this->mChildren2d) {
            if (child->contains(x,y)) {
                child->onTouchMoved(
                        x - child->getPosition().x + child->getAnchorPoint().x * child->getSize().x,
                        y - child->getPosition().y + child->getAnchorPoint().y * child->getSize().y,
                        touch);
            }
        }
    }

    void Node::onTouchEnded(const float x, const float y, const gfx::Touch &touch) noexcept {
        for (auto& child : this->mChildren2d) {
            if (child->contains(x,y)) {
                child->onTouchEnded(
                        x - child->getPosition().x + child->getAnchorPoint().x * child->getSize().x,
                        y - child->getPosition().y + child->getAnchorPoint().y * child->getSize().y,
                        touch);
            }
        }
    }
*/
    bool Node::contains(float x, float y) noexcept {
        float beginX = this->mPosition.x - this->mAnchorPoint.x * this->mSize.x;
        float beginY = this->mPosition.y - this->mAnchorPoint.y * this->mSize.y;
        return beginX <= x && beginX + this->mSize.x > x
            && beginY <= y && beginY + this->mSize.y > y;
    }
}