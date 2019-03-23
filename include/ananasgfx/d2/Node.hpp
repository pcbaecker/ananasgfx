#ifndef D2_NODE_H
#define D2_NODE_H

#include <list>
#include <glm/glm.hpp>
#include <ananasgfx/gfx/Node.hpp>

namespace d2 {

    /**
     * @brief The basis 2d node class that does not draw anything but provides basic 2d methods.
     */
    class Node : public ::gfx::Node {
    public:
        /**
         * @brief Initializes the object.
         */
        bool init() noexcept override;

        /**
         * @brief Sets the position of this 2d node.
         *
         * @param x The X-Coordinate of the position.
         * @param y The Y-Coordinate of the position.
         */
        virtual void setPosition(float x, float y) noexcept;

        /**
         * @brief Sets the position of this 2d node.
         *
         * @param position The 2d vector position.
         */
        void setPosition(const glm::vec2& position) noexcept;

        /**
         * @brief Returns the current position of this node.
         *
         * @return Reference to the current position of this node.
         */
        const glm::vec2& getPosition() const noexcept;

        /**
         * @brief Sets the scale of this node.
         *
         * @param x The X-Scale of this node.
         * @param y The Y-Scale of this node.
         */
        virtual void setScale(float x, float y) noexcept;

        /**
         * @brief Sets the scale for both axis.
         *
         * @param scale The scale value that will be applied to the X- and Y-Axis.
         */
        void setScale(float scale) noexcept;

        /**
         * @brief Sets the scale for both axis by a 2d vector.
         *
         * @param scale A 2d vector.
         */
        void setScale(const glm::vec2& scale) noexcept;

        /**
         * @brief Returns a 2d vector that holds the scale for X- and Y-Axis.
         *
         * @return Reference to the 2d vector containing the scale for X- and Y-Axis.
         */
        const glm::vec2& getScale() const noexcept;

        /**
         * @brief Sets the size of this node.
         *
         * @param x The width of this node.
         * @param y The height of this node.
         */
        virtual void setSize(float x, float y) noexcept;

        /**
         * @brief Sets the size of this node.
         *
         * @param size 2d vector containing the width and height of this node.
         */
        void setSize(const glm::vec2& size) noexcept;

        /**
         * @brief Returns the current size of this node.
         *
         * @return Reference to the current size of this node.
         */
        const glm::vec2& getSize() const noexcept;

        /**
         * @brief Sets the anchor point of this node.
         *
         * @param x The x value for the anchor point.
         * @param y The y value for the anchor point.
         */
        virtual void setAnchorPoint(float x, float y) noexcept;

        /**
         * @brief Sets the anchor point of this node.
         *
         * @param anchorPoint 2d vector contining the anchor point.
         */
        void setAnchorPoint(const glm::vec2& anchorPoint) noexcept;

        /**
         * @brief Returns the current anchor point.
         *
         * @return Reference to the anchor point.
         */
        const glm::vec2& getAnchorPoint() const noexcept;

        /**
         * @brief Sets the rotation of this 2d node.
         *
         * @param rotation The rotation for this 2d node.
         */
        virtual void setRotation(float rotation) noexcept;

        /**
         * @brief Returns the rotation of this 2d node.
         *
         * @return The rotation of this node.
         */
        float getRotation() const noexcept;

        /**
         * @brief Sets the parent position offset.
         *
         * @param x The x offset.
         * @param y The y offset.
         */
        virtual void setParentPositionOffset(float x, float y) noexcept;

        /**
         * @brief Sets the parent position offset.
         *
         * @param offset The offset vector containing x and y.
         */
        void setParentPositionOffset(const glm::vec2& offset) noexcept;

        /**
         * @brief Returns the parent position offset.
         *
         * @return Reference to the current parent position offset.
         */
        const glm::vec2& getParentPositionOffset() const noexcept;

        /**
         * @brief This method calculates the current screen position.
         *
         * @return 2d vector containing the screen position.
         */
        glm::vec2 getScreenPosition() const noexcept;

        /**
         * @brief Sets the parent rotation offset.
         *
         * @param rotation The parent rotation offset.
         */
        virtual void setParentRotationOffset(float rotation) noexcept;

        /**
         * @brief Returns the parent rotation offset.
         *
         * @return The parent rotation offset.
         */
        float getParentRotationOffset() const noexcept;

        /**
         * @brief Sets the z-index for this 2d node.
         *
         * @param zindex The z-index.
         */
        virtual void setZIndex(uint8_t zindex) noexcept;

        /**
         * @brief Returns the current z-index of this 2d node.
         *
         * @return The current z-index of this 2d node.
         */
        uint8_t getZIndex() const noexcept;

        /**
         * @brief Returns the render priority of this node.
         *
         * @return The render priority.
         */
        gfx::nodePriority_t getPriority() const noexcept override;

        /**
         * @brief Renders this 2d node into a rendertexture.
         *
         * @return A shared pointer containing the generated render texture.
         */
        std::shared_ptr<gfx::RenderTexture> asRenderTexture() noexcept override;

        /**
         * @brief Checks if the given position is inside this 2d node.
         *
         * Checks inside the parent space and not screen space.
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         * @return True if given coordinates are inside this rect.
         */
        bool contains(float x, float y) noexcept;

        /**
         * @brief Called when a touch begins.
         *
         * @param touch The touch object.
         */
        void onTouchBegan(gfx::Touch& touch) noexcept override;

        /**
         * @brief Called when a touch moves.
         *
         * @param touch The touch object.
         */
        void onTouchMoved(gfx::Touch& touch) noexcept override;

        /**
         * @brief Called when a touch ends.
         *
         * @param touch The touch object.
         */
        void onTouchEnded(gfx::Touch& touch) noexcept override;

    protected:
        /**
         * @brief Is called when a new child is added.
         *
         * The purpose of this method is to filter 2d nodes to maintain a special list of 2d nodes.
         * @param pNode The newly added node.
         */
        void onChildAdded(gfx::Node* pNode) noexcept override;

        /**
         * @brief Is called when a child is removed.
         *
         * @param node The node that will be removed.
         */
        void onChildRemoved(gfx::Node* node) noexcept override;

        /**
         * @brief Updates all children or only the given child nodes parent position offset.
         *
         * @param pNode If this optional parameter is set, only this single node will be updated.
         */
        void updateChildrenPositionOffset(d2::Node* pNode = nullptr) const noexcept;

        /**
         * @brief Updates all children or only the given child nodes parent rotation offset.
         *
         * @param pNode If this optional paramater is set, only this single node will be updated.
         */
        void updateChildrenRotationOffset(d2::Node* pNode = nullptr) const noexcept;

    protected:
        /**
         * @brief A list containing all child 2d nodes.
         */
        std::list<d2::Node*> mChildren2d;

        /**
         * @brief 2d vector containing the nodes position.
         */
        glm::vec2 mPosition = glm::vec2(0.0f, 0.0f);

        /**
         * @brief 2d vector containing the parent position offset.
         */
        glm::vec2 mParentPositionOffset = glm::vec2(0.0f, 0.0f);

        /**
         * @brief 2d vector containing the anchor point.
         */
        glm::vec2 mAnchorPoint = glm::vec2(0.0f, 0.0f);

        /**
         * @brief 2d vector containing the scale.
         */
        glm::vec2 mScale = glm::vec2(1.0f, 1.0f);

        /**
         * @brief 2d vector containing the size.
         */
        glm::vec2 mSize = glm::vec2(0.0f, 0.0f);

        /**
         * @brief The rotation of this node.
         */
        float mRotation = 0.0f;

        /**
         * @brief The parent rotation offset.
         */
        float mParentRotationOffset = 0.0f;

        /**
         * @brief The z-index of this node.
         */
        uint8_t mZIndex = 64;
    };

}

#endif