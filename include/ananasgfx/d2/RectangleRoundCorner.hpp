#ifndef D2_RECTANGLEROUNDCORNER_H
#define D2_RECTANGLEROUNDCORNER_H

#include "VertexNode.hpp"

namespace d2 {

    /**
     * @brief Creates a rectangle with rounded corners.
     */
    class RectangleRoundCorner : public VertexNode {
    public:
        /**
         * @brief Sets the radius of the rounded corners.
         *
         * @param radius The radius.
         */
        void setRadius(float radius) noexcept;

        /**
         * @brief Returns the radius of the rounded corners.
         *
         * @return The radius of the rounded corners.
         */
        float getRadius() const noexcept;

    protected:
        /**
         * @brief Updates the indices of this vertex node.
         */
        void updateIndices() noexcept override;

        /**
         * @brief Updates the vertices of this vertex node.
         */
        void updateVertices() noexcept override;

        /**
         * @brief Returns the shader that should be used to draw this vertex node.
         */
        gfx::Shader* shader() noexcept override;

    private:
        /**
         * @brief Makes the vertices for a corner.
         *
         * @param position The position vertex buffer.
         * @param center The center position.
         * @param index The current vertex buffer index.
         * @param startAngle The start angle of the corner.
         * @param rX The border radius x-axis.
         * @param rY The border radis y-axis.
         */
        unsigned short makeCornerVertices(
                gfx::VertexBuffer& position,
                const glm::vec3& center,
                unsigned short index,
                float startAngle,
                float rX,
                float rY) noexcept;

        /**
         * @brief Makes the corner indices for a corner.
         *
         * @param vertexIndex The start vertex index.
         * @param indexIndex The start index index.
         */
        void makeCornerIndices(
                unsigned short vertexIndex,
                unsigned short indexIndex
                ) noexcept;

    protected:
        /**
         * @brief The current radius of the corners.
         */
        float mRadius = 8.0f;

        /**
         * @brief The number of triangles that should be used per corner.
         */
        unsigned short mTrianglesPerCorner = 32;
    };

}

#endif