#ifndef D2_NODE_H
#define D2_NODE_H

#include <glm/glm.hpp>
#include <ananasgfx/gfx/Node.hpp>

namespace d2 {

    class Node : public ::gfx::Node {
    public:
        bool init() noexcept override;

        virtual void setPosition(float x, float y) noexcept;
        void setPosition(const glm::vec2& position) noexcept;
        const glm::vec2& getPosition() const noexcept;

        virtual void setScale(float x, float y) noexcept;
        void setScale(float scale) noexcept;
        void setScale(const glm::vec2& scale) noexcept;
        const glm::vec2& getScale() const noexcept;

        virtual void setSize(float x, float y) noexcept;
        void setSize(const glm::vec2& size) noexcept;
        const glm::vec2& getSize() const noexcept;

        virtual void setAnchorPoint(float x, float y) noexcept;
        void setAnchorPoint(const glm::vec2& anchorPoint) noexcept;
        const glm::vec2& getAnchorPoint() const noexcept;

        virtual void setRotation(float rotation) noexcept;
        float getRotation() const noexcept;

        virtual void setParentPositionOffset(float x, float y) noexcept;
        void setParentPositionOffset(const glm::vec2& offset) noexcept;
        const glm::vec2& getParentPositionOffset() const noexcept;

        glm::vec2 getScreenPosition() const noexcept;

        virtual void setParentRotationOffset(float rotation) noexcept;
        float getParentRotationOffset() const noexcept;

        virtual void setZIndex(uint8_t zindex) noexcept;

    protected:
        void onChildAdded(gfx::Node* pNode) noexcept override;
        void updateChildrenPositionOffset(d2::Node* pNode = nullptr) const noexcept;
        void updateChildrenRotationOffset(d2::Node* pNode = nullptr) const noexcept;

    protected:
        std::list<d2::Node*> mChildren2d;
        glm::vec2 mPosition = glm::vec2(0.0f, 0.0f);
        glm::vec2 mParentPositionOffset = glm::vec2(0.0f, 0.0f);
        glm::vec2 mAnchorPoint = glm::vec2(0.0f, 0.0f);
        glm::vec2 mScale = glm::vec2(1.0f, 1.0f);
        glm::vec2 mSize = glm::vec2(0.0f, 0.0f);
        float mRotation = 0.0f;
        float mParentRotationOffset = 0.0f;
        uint8_t mZIndex = 0;
    };

}

#endif