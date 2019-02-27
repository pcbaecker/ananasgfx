#ifndef D2_CIRCLE_H
#define D2_CIRCLE_H

#include "VertexNode.hpp"

namespace d2 {

    /**
     * @brief Creates a circle or ellipse.
     */
    class Circle : public d2::VertexNode {
    protected:
        /**
         * @brief Updates the indices of the circle.
         */
        void updateIndices() noexcept override;

        /**
         * @brief Updates the vertices of the circle.
         */
        void updateVertices() noexcept override;

        /**
         * @brief Returns the shader that should be used to render this circle.
         *
         * @return Shader to be used.
         */
        gfx::Shader* shader() noexcept override;

    protected:
        /**
         * @brief Defines the number of triangles to be used to render this circle.
         */
        size_t mNumberOfTriangles = 128;
    };

}

#endif