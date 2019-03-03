#ifndef D2_VERTEXNODE_H
#define D2_VERTEXNODE_H

#include <ananasgfx/gfx/Vertices.hpp>
#include <ananasgfx/gfx/Shader.hpp>
#include "Node.hpp"

namespace d2 {

    /**
     * @brief Is the base for all nodes that use vertices.
     *
     * Not intended to be used without inheritance.
     */
    class VertexNode : public Node {
    public:
        /**
         * @brief Initializes the VertexNode.
         *
         * @return True on sucess.
         */
        bool init() noexcept override;

        /**
         * @brief Draws this VertexNode.
         */
        void draw() noexcept override;

        /**
         * @brief Sets the position of this node.
         *
         * @param x The X-Coordinate of the position.
         * @param y The Y-Coordinate of the position.
         */
        void setPosition(float x, float y) noexcept override;

        /**
         * @brief Sets the rotation of this node.
         *
         * @param rotation The rotation of this node.
         */
        void setRotation(float rotation) noexcept override;

        /**
         * @brief Sets the scale of this node.
         *
         * @param x The x scale.
         * @param y The y scale.
         */
        void setScale(float x , float y) noexcept override;

        /**
         * @brief Sets the size of this node.
         *
         * @param x The width of this node.
         * @param y The height of this node.
         */
        void setSize(float x, float y) noexcept override;

        /**
         * @brief Sets the anchor point of this node.
         *
         * @param x The x part of the anchor point.
         * @param y The y part of the anchor point.
         */
        void setAnchorPoint(float x, float y) noexcept override;

        /**
         * @brief Sets the parent position offset.
         *
         * @param x The X-Coordinate of the parent position offset.
         * @param y The Y-Coordinate of the parent position offset.
         */
        void setParentPositionOffset(float x, float y) noexcept override;

        /**
         * @brief Sets the parent rotation offset.
         *
         * @param rotation The rotation of the parent rotation offset.
         */
        void setParentRotationOffset(float rotation) noexcept override;

        /**
         * @brief Sets the z-index.
         *
         * @param zindex The z-index
         */
        void setZIndex(uint8_t zindex) noexcept override;

        /**
         * @brief Sets the color of this vertex node.
         *
         * @param color The color of this vertex node.
         */
        void setColor(const glm::vec4& color) noexcept;

        /**
         * @brief Returns the color of this vertex node.
         *
         * @return The color of this vertex node.
         */
        const glm::vec4& getColor() const noexcept;

        /**
         * @brief Returns a reference to the internal vertices object.
         *
         * @return Reference to the internal vertices object.
         */
        const gfx::Vertices& getVertices() const noexcept;

    protected:
        /**
         * @brief Updates the mode matrix of this vertex node.
         */
        void updateModelMatrix() noexcept;

        /**
         * @brief Returns a pointer to the shader that should be used to render this vertex node.
         *
         * @return Pointer to the shader that should be used to render this vertex node.
         */
        virtual ::gfx::Shader* shader() noexcept = 0;

        /**
         * @brief Updates the indices of this vertex node.
         */
        virtual void updateIndices() noexcept = 0;

        /**
         * @brief Updates the vertices of this vertex node.
         */
        virtual void updateVertices() noexcept = 0;

    protected:
        /**
         * @brief The model matrix of this vertex node.
         */
        glm::mat4 mModelMatrix = glm::mat4(1.0f);

        /**
         * @brief Pointer to the shader of this vertex node.
         */
        ::gfx::Shader* pShader = nullptr;

        /**
         * @brief Pointer to the shader uniform MVP.
         */
        ::gfx::ShaderUniform* pMvpUniform = nullptr;

        /**
         * @brief Pointer to the shader uniform Color.
         */
        ::gfx::ShaderUniform* pColorUniform = nullptr;

        /**
         * @brief The vertices buffer.
         */
        ::gfx::Vertices mVertices;

        /**
         * @brief The color of this vertex node.
         */
        glm::vec4 mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    };

}

#endif