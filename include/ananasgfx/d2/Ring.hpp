#ifndef D2_RING_H
#define D2_RING_H

#include "VertexNode.hpp"

namespace d2 {

    /**
     * @brief Creates a ring.
     */
    class Ring : public d2::VertexNode {
    public:
        /**
         * @brief Sets the thickness of this ring.
         *
         * @param thickness The thickness of this ring.
         */
        void setThickness(float thickness) noexcept;

        /**
         * @brief Returns the thickness of this ring.
         *
         * @return The thickness of this ring.
         */
        float getThickness() const noexcept;

        /**
         * @brief Sets the end angle of this ring.
         *
         * @param angle The end angle of this ring.
         */
        void setAngle(float angle) noexcept;

        /**
         * @brief Returns the end angle of this ring.
         *
         * @return The end angle.
         */
        float getAngle() const noexcept;

        /**
         * @brief Sets the start angle of this ring.
         *
         * @param angle The start angle of this ring.
         */
        void setStartAngle(float angle) noexcept;

        /**
         * @brief Returns the start angle of this ring
         *
         * @return The start angle of this ring.
         */
        float getStartAngle() const noexcept;

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
         * @brief Returns the shader that should be used for this vertex node to draw.
         *
         * @return The shader that should be used.
         */
        gfx::Shader* shader() noexcept override;

    protected:
        /**
         * @brief The thickness of this ring.
         */
        float mThickness = 10.0f;

        /**
         * @brief The end angle of this ring.
         */
        float mAngle = 360.0f;

        /**
         * @brief The start angle of this ring.
         */
        float mStartAngle = 0.0f;

        /**
         * @brief The number of vertex pairs used to draw this ring.
         */
        unsigned short mNumberOfVertexPairs = 128;
    };

}

#endif