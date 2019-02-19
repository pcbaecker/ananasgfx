#include <ananasgfx/d2/Rectangle.hpp>
#include <ananasgfx/gfx/Window.hpp>

namespace d2 {

    gfx::Shader *Rectangle::shader() noexcept {
        return this->pWindow->getRenderer()->getShader(gfx::ShaderType::SimpleColor);
    }

    void Rectangle::updateIndices() noexcept {
        this->mVertices.setNumberOfIndices(6);
        this->mVertices.setIndices(0, 0, 1, 2);
        this->mVertices.setIndices(1, 2, 3, 0);
    }

    void Rectangle::updateVertices() noexcept {
        this->mVertices.setSize(4);
        auto& position = this->mVertices.createBuffer(gfx::VertexType::Position, 3, 0);

        // Upper left
        position.set(0, -this->mAnchorPoint.x, -this->mAnchorPoint.y, 0.0f);

        // Upper right
        position.set(1, 1.0f - this->mAnchorPoint.x, -this->mAnchorPoint.y, 0.0f);

        // Lower right
        position.set(2, 1.0f - this->mAnchorPoint.x, 1.0f - this->mAnchorPoint.y, 0.0f);

        // Lower left
        position.set(3, -this->mAnchorPoint.x, 1.0f - this->mAnchorPoint.y, 0.0f);
    }
}