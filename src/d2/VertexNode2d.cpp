#include <ananasgfx/d2/VertexNode.hpp>
#include <ananasgfx/gfx/Window.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) 640 / (float)480, 0.1f, 100.0f);
//glm::mat4 Projection = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f);
glm::mat4 View = glm::mat4(1.0f);

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
        // Call the normal draw command
        d2::Node::draw();

        // Use our shader
        this->pShader->use();

        // Bind our mvp matrix
        this->pMvpUniform->bind(&this->mModelViewProjectionMatrix);
        this->pColorUniform->bind(&this->mColor);

        // Bind our vertices
        this->pWindow->getRenderer()->bindVertices(&this->mVertices);

        // Draw
        this->pWindow->getRenderer()->drawVertices(&this->mVertices);
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
        glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(w, h, 0.0f));

        // Apply translation -> move to position
        auto pos = this->getScreenPosition();
        model = glm::translate(model, glm::vec3(pos.x / w, pos.y / h, 0.0f));

        // Apply rotation
        model = glm::rotate(model, this->mRotation + this->mParentRotationOffset, glm::vec3(0.0f, 0.0f, 1.0f));

        // Combine
        this->mModelViewProjectionMatrix = this->pWindow->getProjection2dMatrix() * View * model;



        /*
        // Apply translation
        this->mModelMatrix = glm::translate(glm::mat4(1.0f), this->mPosition.x, this->mPosition.y, 0);

        // Apply scale
        this->mModelMatrix = glm::scale(this->mModelMatrix, this->mScale);

        // Apply rotation x
        this->mModelMatrix = glm::rotate(this->mModelMatrix, this->mRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

        // Apply rotation y
        this->mModelMatrix = glm::rotate(this->mModelMatrix, this->mRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

        // Apply rotation z
        this->mModelMatrix = glm::rotate(this->mModelMatrix, this->mRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));*/
    }

    void VertexNode::setParentPositionOffset(float x, float y) noexcept {
        Node::setParentPositionOffset(x, y);

        this->updateModelMatrix();
    }

    void VertexNode::setParentRotationOffset(float rotation) noexcept {
        Node::setParentRotationOffset(rotation);

        this->updateModelMatrix();
    }

}