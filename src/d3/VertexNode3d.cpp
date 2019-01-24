#include <glm/glm.hpp>
#include <ananasgfx/d3/VertexNode.hpp>
#include <ananasgfx/gfx/Window.hpp>

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
// TODO The projection and view matrix must come from outside, this is just for testing
glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) 640 / (float)480, 0.1f, 100.0f);
glm::mat4 View = glm::lookAt(
        glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
);*/
//glm::mat4 mvp = Projection * View * Model;

namespace d3 {

    bool VertexNode::init() noexcept {
        // Initialize the vertices container
        this->mVertices.setRenderer(this->pWindow->getRenderer());

        // Get the shader that should be used for this VertexNode
        this->pShader = this->shader();

        // Get the uniforms where we connect the matrices later
        this->pMvpUniform = this->pShader->getUniform("MVP");

        // Initialize our vertices and indices
        this->updateVertices();
        this->updateIndices();
        this->pWindow->getRenderer()->bufferVertices(&this->mVertices);

        // Init the basic node
        return d3::Node::init();
    }

    void VertexNode::draw() noexcept {
        d3::Node::draw();

        glm::mat4 mvp = this->pWindow->getCamera().getViewProjectionMatrix() * this->mModelMatrix;

        // Use our shader
        this->pShader->use();

        // Bind our mvp matrix
        this->pMvpUniform->bind(&mvp);

        // Bind our vertices
        this->pWindow->getRenderer()->bindVertices(&this->mVertices);

        // Draw
        this->pWindow->getRenderer()->drawVertices(&this->mVertices);
    }

    void VertexNode::setPosition(float x, float y, float z) noexcept {
        Node::setPosition(x, y, z);
        this->updateModelMatrix();
    }

    void VertexNode::setRotation(float x, float y, float z) noexcept {
        Node::setRotation(x, y, z);
        this->updateModelMatrix();
    }

    void VertexNode::setScale(float x, float y, float z) noexcept {
        Node::setScale(x, y, z);
        this->updateModelMatrix();
    }

    void VertexNode::updateModelMatrix() noexcept {
        // Apply translation
        this->mModelMatrix = glm::translate(glm::mat4(1.0f), this->mPosition);

        // Apply scale
        this->mModelMatrix = glm::scale(this->mModelMatrix, this->mScale);

        // Apply rotation x
        this->mModelMatrix = glm::rotate(this->mModelMatrix, this->mRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

        // Apply rotation y
        this->mModelMatrix = glm::rotate(this->mModelMatrix, this->mRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

        // Apply rotation z
        this->mModelMatrix = glm::rotate(this->mModelMatrix, this->mRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    }

}