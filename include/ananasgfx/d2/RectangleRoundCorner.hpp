#ifndef D2_RECTANGLEROUNDCORNER_H
#define D2_RECTANGLEROUNDCORNER_H

#include "VertexNode.hpp"

namespace d2 {

    class RectangleRoundCorner : public VertexNode {
    public:
        void updateIndices() noexcept override;

        void updateVertices() noexcept override;

        gfx::Shader* shader() noexcept override;

    protected:
        unsigned short makeCornerVertices(
                gfx::VertexBuffer& position,
                const glm::vec3& center,
                unsigned short index,
                float startAngle,
                float rX,
                float rY) noexcept;

        void makeCornerIndices(
                unsigned short vertexIndex,
                unsigned short indexIndex
                ) noexcept;

    protected:
        float mRadius = 32.0f;
        unsigned short mTrianglesPerCorner = 32;
    };

}

#endif