#include <glm/ext/scalar_constants.hpp>
#include <ananasgfx/d2/Circle.hpp>
#include <ananasgfx/gfx/Window.hpp>

namespace d2 {

    gfx::Shader *Circle::shader() noexcept {
        return this->pWindow->getRenderer()->getShader(gfx::ShaderType::SimpleColor);
    }

    void Circle::updateIndices() noexcept {
        this->mVertices.setNumberOfIndices(this->mNumberOfTriangles * 3);

        // Go round and index the triangles by connecting the center point with two outer points
        for (size_t i = 0; i < this->mNumberOfTriangles-1; i++) {
            this->mVertices.setIndices(i, 0, static_cast<unsigned short>(i + 1), static_cast<unsigned short>(i + 2));
        }

        // Last triangle must be treated extra, because it connects the last with the first point
        this->mVertices.setIndices(this->mNumberOfTriangles-1, 0, static_cast<unsigned short>(this->mNumberOfTriangles-1), 1);
    }

    void Circle::updateVertices() noexcept {
        // Calculate the number of vertices
        size_t numberOfVertices = this->mNumberOfTriangles + 1;

        // Create the vertex buffer for position
        this->mVertices.setSize(numberOfVertices);
        auto& position = this->mVertices.createBuffer(gfx::VertexType::Position, 3, 0);

        // Center depends on the anchor point
        position.set(0, 0.5f - this->mAnchorPoint.x, 0.5f - this->mAnchorPoint.y, 0.0f);

        // Go round and define outer vertices
        for (size_t i = 1; i < numberOfVertices; i++) {
            // Calculate the progress we made in going round the circle in radians
            float a = static_cast<float>(i-1) / static_cast<float>(numberOfVertices - 1) * 2 * glm::pi<float>();

            // Define the vertex for this outer point (radius is 0.5f)
            position.set(i, (0.5f - this->mAnchorPoint.x) - cosf(a) * 0.5f, (0.5f - this->mAnchorPoint.y) - sinf(a) * 0.5f, 0.0f);
        }
    }

}

