#include <ananasgfx/d3/RenderTexture.hpp>

namespace d3 {

    bool Node::init() noexcept {
        return ::gfx::Node::init();
    }

    void Node::setPosition(float x, float y, float z) noexcept {
        this->mPosition.x = x;
        this->mPosition.y = y;
        this->mPosition.z = z;
    }

    void Node::setRotation(float x, float y, float z) noexcept {
        this->mRotation.x = x;
        this->mRotation.y = y;
        this->mRotation.z = z;
    }

    void Node::setScale(float x, float y, float z) noexcept {
        this->mScale.x = x;
        this->mScale.y = y;
        this->mScale.z = z;
    }

    const glm::vec3 &Node::getPosition() const noexcept {
        return this->mPosition;
    }

    const glm::vec3 &Node::getRotation() const noexcept {
        return this->mRotation;
    }

    const glm::vec3 &Node::getScale() const noexcept {
        return this->mScale;
    }

}