#ifndef D2_CIRCLE_H
#define D2_CIRCLE_H

#include "VertexNode.hpp"

namespace d2 {

    class Circle : public d2::VertexNode {
    public:
        void updateIndices() noexcept override;

        void updateVertices() noexcept override;

        gfx::Shader* shader() noexcept override;

    protected:
        size_t mNumberOfTriangles = 128;
    };

}

#endif