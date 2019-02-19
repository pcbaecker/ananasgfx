#include <glm/ext/scalar_constants.hpp>
#include <ananasgfx/d2/Ring.hpp>
#include <ananasgfx/gfx/Window.hpp>

namespace d2 {

    gfx::Shader *Ring::shader() noexcept {
        return this->pWindow->getRenderer()->getShader(gfx::ShaderType::SimpleColor);
    }

    void Ring::updateIndices() noexcept {
        int numberOfIndices = this->mNumberOfVertexPairs * 6;
        this->mVertices.setNumberOfIndices(numberOfIndices);

        unsigned short v = 0;
        for (unsigned short i = 0; i < numberOfIndices / 3; i += 2, v += 2) {
            this->mVertices.setIndices(i, v, v + 2, v + 1);
            this->mVertices.setIndices(i + 1, v + 2, v + 3, v + 1);
        }
    }

    void Ring::updateVertices() noexcept {
        // Create the vertex buffer for position
        int numberOfVertices = this->mNumberOfVertexPairs * 2 + 2;
        this->mVertices.setSize(static_cast<size_t>(numberOfVertices));
        auto& position = this->mVertices.createBuffer(gfx::VertexType::Position, 3, 0);

        // Calculate the center point of the ring
        glm::vec3 center(0.5f - this->mAnchorPoint.x, 0.5f - this->mAnchorPoint.y, 0.0f);

        // Calculate the thickness of the ring (x- and y-axis can differ, we take the smaller one)
        float thickness = this->mThickness / this->mSize.x;
        if (this->mThickness / this->mSize.y < thickness) {
            thickness = this->mThickness / this->mSize.y;
        }

        // Inner radius is the outer radius minus the thickness
        float outerRadius = 0.5f;
        float innerRadius = outerRadius - thickness;

        // Calculate the we want to go round
        float angle = glm::pi<float>() + glm::radians<float>(this->mAngle);

        // Calculate the start angle, where the ring should start
        float startAngle = glm::pi<float>() * 1.5f + glm::radians<float>(this->mStartAngle);

        // Iterate through the vertex pairs
        for (unsigned short i = 0; i < numberOfVertices; i += 2) {
            float a = (static_cast<float>(i) / static_cast<float>(numberOfVertices - 2)) * angle + startAngle;
            float cx = cosf(a);
            float cy = sinf(a);

            // Inner vertex
            position.set(i, center.x + innerRadius * cx, center.y + innerRadius * cy, 0.0f);

            // Outer vertex
            position.set(i + 1, center.x + outerRadius * cx, center.y + outerRadius * cy, 0.0f);
        }
    }

}