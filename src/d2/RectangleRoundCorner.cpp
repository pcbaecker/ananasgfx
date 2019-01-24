#include <glm/ext/scalar_constants.hpp>
#include <ananasgfx/d2/RectangleRoundCorner.hpp>
#include <ananasgfx/gfx/Window.hpp>

namespace d2 {

    gfx::Shader *RectangleRoundCorner::shader() noexcept {
        return this->pWindow->getRenderer()->getShader(gfx::ShaderType::SimpleColor);
    }

    void RectangleRoundCorner::updateIndices() noexcept {
        const int indicesPerCorner = this->mTrianglesPerCorner * 6;
        const int indicesPerRect = 6;
        const int numberOfIndices = indicesPerCorner * 4 + indicesPerRect * 2;
        this->mVertices.setNumberOfIndices(static_cast<size_t>(numberOfIndices));
        unsigned short vertexIndex = 0;
        unsigned short indexIndex = 0;

        // Upper left
        makeCornerIndices(vertexIndex, indexIndex);
        vertexIndex += this->mTrianglesPerCorner + 2;
        indexIndex += this->mTrianglesPerCorner;

        // Upper right
        makeCornerIndices(vertexIndex, indexIndex);
        vertexIndex += this->mTrianglesPerCorner + 2;
        indexIndex += this->mTrianglesPerCorner;

        // Lower right
        makeCornerIndices(vertexIndex, indexIndex);
        vertexIndex += this->mTrianglesPerCorner + 2;
        indexIndex += this->mTrianglesPerCorner;

        // Lower left
        makeCornerIndices(vertexIndex, indexIndex);
        vertexIndex += this->mTrianglesPerCorner + 2;
        indexIndex += this->mTrianglesPerCorner;

        // Vertical rect
        this->mVertices.setIndices(indexIndex++,
                vertexIndex,
                static_cast<unsigned short>(vertexIndex + 1),
                static_cast<unsigned short>(vertexIndex + 2));
        this->mVertices.setIndices(indexIndex++,
                vertexIndex,
                static_cast<unsigned short>(vertexIndex + 2),
                static_cast<unsigned short>(vertexIndex + 3));
        vertexIndex += 4;

        // Horizontal rect
        this->mVertices.setIndices(indexIndex++,
                vertexIndex,
                static_cast<unsigned short>(vertexIndex + 1),
                static_cast<unsigned short>(vertexIndex + 2));
        this->mVertices.setIndices(indexIndex,
                vertexIndex,
                static_cast<unsigned short>(vertexIndex + 2),
                static_cast<unsigned short>(vertexIndex + 3));
    }

    void RectangleRoundCorner::makeCornerIndices(unsigned short vertexIndex, unsigned short indexIndex) noexcept {
        for (unsigned short i = 0; i < this->mTrianglesPerCorner; i++) {
            this->mVertices.setIndices(indexIndex + i,
                    vertexIndex,
                    static_cast<unsigned short>(vertexIndex + i + 2),
                    static_cast<unsigned short>(vertexIndex + i + 1)
                    );
        }
    }

    void RectangleRoundCorner::updateVertices() noexcept {
        // Calculate the border radius in [0,1] range
        float rX = this->mRadius / (this->mSize.x * this->mScale.x);
        float rY = this->mRadius / (this->mSize.y * this->mScale.y);

        // Create position vertex buffer
        const int verticesPerCorner = this->mTrianglesPerCorner + 2;
        const int verticesPerRect = 4;
        const int numberOfVertices = verticesPerCorner * 4 + verticesPerRect * 2;
        this->mVertices.setSize(static_cast<size_t>(numberOfVertices));
        auto& position = this->mVertices.createBuffer(gfx::VertexType::Position, 3, 0);
        unsigned short index = 0;

        // Upper left
        index = makeCornerVertices(
                position,
                glm::vec3(-this->mAnchorPoint.x + rX, -this->mAnchorPoint.y + rY, 0.0f),
                index,
                glm::pi<float>(),
                rX,
                rY);

        // Upper right
        index = makeCornerVertices(
                position,
                glm::vec3((1.0f - this->mAnchorPoint.x) - rX, -this->mAnchorPoint.y + rY, 0.0f),
                index,
                glm::pi<float>() * 0.5f,
                rX,
                rY);

        // Lower right
        index = makeCornerVertices(
                position,
                glm::vec3((1.0f - this->mAnchorPoint.x) - rX, (1.0f - this->mAnchorPoint.y) - rY, 0.0f),
                index,
                0.0f,
                rX,
                rY);

        // Lower left
        index = makeCornerVertices(
                position,
                glm::vec3(-this->mAnchorPoint.x + rX, (1.0f - this->mAnchorPoint.y) - rY, 0.0f),
                index,
                glm::pi<float>() * 1.5f,
                rX,
                rY);

        // Vertical rect upper left
        position.set(index++, -this->mAnchorPoint.x + rX, -this->mAnchorPoint.y, 0.0f);

        // Vertical rect upper right
        position.set(index++, (1.0f - this->mAnchorPoint.x) - rX, -this->mAnchorPoint.y, 0.0f);

        // Vertical rect lower right
        position.set(index++, (1.0f - this->mAnchorPoint.x) - rX, 1.0f - this->mAnchorPoint.y, 0.0f);

        // Vertical rect lower left
        position.set(index++, -this->mAnchorPoint.x + rX, 1.0f - this->mAnchorPoint.y, 0.0f);

        // Horizontal rect upper left
        position.set(index++, -this->mAnchorPoint.x, -this->mAnchorPoint.y + rY);

        // Horizontal rect upper right
        position.set(index++, 1.0f - this->mAnchorPoint.x, -this->mAnchorPoint.y + rY);

        // Horizontal rect lower right
        position.set(index++, 1.0f - this->mAnchorPoint.x, (1.0f - this->mAnchorPoint.y) - rY, 0.0f);

        // Horizontal rect lower left
        position.set(index, -this->mAnchorPoint.x, (1.0f - this->mAnchorPoint.y) - rY, 0.0f);
    }

    unsigned short RectangleRoundCorner::makeCornerVertices(
            gfx::VertexBuffer& position,
            const glm::vec3 &center,
            unsigned short index,
            float startAngle,
            float rX,
            float rY) noexcept {
        // Set the center position
        position.set(index, center);

        // Define the outer vertices
        for (unsigned short i = 0; i < this->mTrianglesPerCorner + 1; i++) {
            // Calculate the progress angle
            float a = (static_cast<float>(i) / static_cast<float>(this->mTrianglesPerCorner)) * glm::pi<float>() * 0.5f;

            // Apply the start angle of this arc
            a += startAngle;

            // Define this vertex
            position.set(index + i + 1, center.x + sinf(a) * rX, center.y + cosf(a) * rY, 0.0f);
        }

        return static_cast<unsigned short>(index + this->mTrianglesPerCorner + 2);
    }


}