#ifndef D2_RECTANGLE_H
#define D2_RECTANGLE_H

#include <ananasgfx/d2/VertexNode.hpp>

namespace d2 {

    /**
     * @brief Creates a simple rectangle.
     */
    class Rectangle : public VertexNode {
    protected:
        /**
         * @brief Updates the indicies of this vertex node.
         */
        void updateIndices() noexcept override;

        /**
         * @brief Updates the indices of this vertex node.
         */
        void updateVertices() noexcept override;

        /**
         * @brief Returns the shader that should be used for this vertex node.
         *
         * @return Pointer to the shader that should be used for this vertex node.
         */
        gfx::Shader *shader() noexcept override;
    };

}

#endif