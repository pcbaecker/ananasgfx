#ifndef D2_RECTANGLE_H
#define D2_RECTANGLE_H

#include <ananasgfx/d2/VertexNode.hpp>

namespace d2 {

    class Rectangle : public VertexNode {
    public:

    protected:
        void updateIndices() noexcept override;
        void updateVertices() noexcept override;

    private:
        gfx::Shader *shader() noexcept override;
    };

}

#endif