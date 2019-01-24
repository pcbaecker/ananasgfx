#ifndef D3_CUBE_H
#define D3_CUBE_H

#include <memory>

#include "VertexNode.hpp"

namespace d3 {

class Cube : public VertexNode {
    public:

        bool init() noexcept override;

    void update(float dt) noexcept override;

    void updateIndices() noexcept override;

    void updateVertices() noexcept override;

    ::gfx::Shader* shader() noexcept override;

private:

    };

}

#endif