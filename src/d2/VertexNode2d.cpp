#include <ananasgfx/d2/VertexNode.hpp>
#include <ananasgfx/gfx/Window.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace d2 {

    bool VertexNode::init() noexcept {
        // Initialize the vertices container
        this->mVertices.setRenderer(this->pWindow->getRenderer());

        // Get the shader that should be used for this VertexNode
        this->pShader = this->shader();

        // Get the uniforms where we connect the data later
        this->pShader->use();
        this->pMvpUniform = this->pShader->getUniform("mvp");
        this->pColorUniform = this->pShader->getUniform("overallColor");

        // Initialize our vertices and indices
        this->updateVertices();
        this->updateIndices();
        this->pWindow->getRenderer()->bufferVertices(&this->mVertices);

        // Init the basic node
        return d2::Node::init();
    }

    void VertexNode::draw() noexcept {
        // Calculate the MVP matrix
        auto mvp = this->pWindow->getProjection2dMatrix() * this->mModelMatrix;

        // Use our shader
        this->pShader->use();

        // Bind our mvp matrix
        this->pMvpUniform->bind(&mvp);
        this->pColorUniform->bind(&this->mColor);

        // Bind our vertices
        this->pWindow->getRenderer()->bindVertices(&this->mVertices);

        // Draw
        this->pWindow->getRenderer()->drawVertices(&this->mVertices);

        // Draw all children after we drew this node
        d2::Node::draw();
    }

    void VertexNode::setPosition(float x, float y) noexcept {
        Node::setPosition(x, y);
        this->updateModelMatrix();
    }

    void VertexNode::setRotation(float rotation) noexcept {
        Node::setRotation(rotation);
        this->updateModelMatrix();
    }

    void VertexNode::setScale(float x, float y) noexcept {
        Node::setScale(x, y);
        this->updateModelMatrix();
    }

    void VertexNode::setSize(float x, float y) noexcept {
        Node::setSize(x, y);
        this->updateModelMatrix();
    }

    void VertexNode::setAnchorPoint(float x, float y) noexcept {
        Node::setAnchorPoint(x, y);

        // Update vertices only if we already initialized our vertex node
        if (this->mInitialized) {
            this->updateVertices();
            this->pWindow->getRenderer()->bufferVertices(&this->mVertices);
        }
    }

    void VertexNode::setColor(const glm::vec4& color) noexcept {
        this->mColor = color;
    }

    void VertexNode::updateModelMatrix() noexcept {
        // The actual width of the rectangle is the size multiplied by a scale factor
        float w = this->mScale.x * this->mSize.x;

        // The actual height of the rectangle is the size multiplied by a scale factor
        float h = this->mScale.y * this->mSize.y;

        // Scale the rectangle to the correct form
        this->mModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(w, h, 0.0f));

        // Apply translation -> move to position
        auto pos = this->getScreenPosition();
        this->mModelMatrix = glm::translate(this->mModelMatrix, glm::vec3(pos.x / w, pos.y / h, this->mZIndex));

        // Apply rotation
        this->mModelMatrix = glm::rotate(this->mModelMatrix, this->mRotation + this->mParentRotationOffset, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void VertexNode::setParentPositionOffset(float x, float y) noexcept {
        Node::setParentPositionOffset(x, y);

        this->updateModelMatrix();
    }

    void VertexNode::setParentRotationOffset(float rotation) noexcept {
        Node::setParentRotationOffset(rotation);

        this->updateModelMatrix();
    }

    void VertexNode::setZIndex(uint8_t zindex) noexcept {
        d2::Node::setZIndex(zindex);

        this->updateModelMatrix();
    }
}