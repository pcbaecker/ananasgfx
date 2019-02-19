#ifndef D2_RING_H
#define D2_RING_H

#include "VertexNode.hpp"

namespace d2 {

    class Ring : public d2::VertexNode {
    public:
        void updateIndices() noexcept override;

        void updateVertices() noexcept override;

        gfx::Shader* shader() noexcept override;

    protected:
        float mThickness = 10.0f;
        float mAngle = 360.0f;
        float mStartAngle = 0.0f;
        unsigned short mNumberOfVertexPairs = 128;
    };

}

#endif