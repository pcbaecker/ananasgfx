#include <ananasgfx/d3/Cube.hpp>
#include <ananasgfx/gfx/Window.hpp>

namespace d3 {

    bool Cube::init() noexcept {
        return d3::VertexNode::init();
    }

    void Cube::updateIndices() noexcept {
        this->mVertices.setNumberOfIndices(12 * 3);
        this->mVertices.setIndices(0, 0, 1, 2);
        this->mVertices.setIndices(1, 1, 2, 3);
        this->mVertices.setIndices(2, 1, 3, 5);
        this->mVertices.setIndices(3, 3, 5, 7);
        this->mVertices.setIndices(4, 0, 1, 4);
        this->mVertices.setIndices(5, 1, 4, 5);
        this->mVertices.setIndices(6, 0, 4, 2);
        this->mVertices.setIndices(7, 4, 2, 6);
        this->mVertices.setIndices(8, 2, 6, 3);
        this->mVertices.setIndices(9, 6, 3, 7);
        this->mVertices.setIndices(10, 4, 5, 7);
        this->mVertices.setIndices(11, 5, 6, 7);
    }

    void Cube::updateVertices() noexcept {
        this->mVertices.setSize(8);

        auto& position = this->mVertices.createBuffer(gfx::VertexType::Position, 3, 0);
        position.set(0, 1.0f, -1.0f, 1.0f);
        position.set(1, 1.0f, 1.0f, 1.0f);
        position.set(2, -1.0f, -1.0f, 1.0f);
        position.set(3, -1.0f, 1.0f, 1.0f);
        position.set(4, 1.0f, -1.0f, -1.0f);
        position.set(5, 1.0f, 1.0f, -1.0f);
        position.set(6, -1.0f, -1.0f, -1.0f);
        position.set(7, -1.0f, 1.0f, -1.0f);

        auto& color = this->mVertices.createBuffer(gfx::VertexType::Color, 3, 1);
        color.set(0, 1.0f, 0.0f, 0.0f);
        color.set(1, 0.0f, 1.0f, 0.0f);
        color.set(2, 1.0f, 0.0f, 0.0f);
        color.set(3, 0.0f, 1.0f, 0.0f);
        color.set(4, 0.0f, 0.0f, 1.0f);
        color.set(5, 1.0f, 0.0f, 1.0f);
        color.set(6, 0.0f, 0.0f, 1.0f);
        color.set(7, 1.0f, 0.0f, 1.0f);

        /*
        this->mVertices.createBuffer(gfx::VertexType::Position, 3, 0);
        this->mVertices[gfx::VertexType::Position].set(0, -1.0f,-1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(1, -1.0f,-1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(2, -1.0f, 1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(3, 1.0f, 1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(4, -1.0f,-1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(5, -1.0f, 1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(6, 1.0f,-1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(7, -1.0f,-1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(8, 1.0f,-1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(9, 1.0f, 1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(10, 1.0f,-1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(11, -1.0f,-1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(12, -1.0f,-1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(13, -1.0f, 1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(14, -1.0f, 1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(15, 1.0f,-1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(16, -1.0f,-1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(17, -1.0f,-1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(18, -1.0f, 1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(19, -1.0f,-1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(20, 1.0f,-1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(21, 1.0f, 1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(22, 1.0f,-1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(23, 1.0f, 1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(24, 1.0f,-1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(25, 1.0f, 1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(26, 1.0f,-1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(27, 1.0f, 1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(28, 1.0f, 1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(29, -1.0f, 1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(30, 1.0f, 1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(31, -1.0f, 1.0f,-1.0f);
        this->mVertices[gfx::VertexType::Position].set(32, -1.0f, 1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(33, 1.0f, 1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(34, -1.0f, 1.0f, 1.0f);
        this->mVertices[gfx::VertexType::Position].set(35, 1.0f,-1.0f, 1.0f);

        this->mVertices.createBuffer(gfx::VertexType::Color, 3, 1);
        this->mVertices[gfx::VertexType::Color].set(0, 0.583f,  0.771f,  0.014f);
        this->mVertices[gfx::VertexType::Color].set(1, 0.609f,  0.115f,  0.436f);
        this->mVertices[gfx::VertexType::Color].set(2, 0.327f,  0.483f,  0.844f);
        this->mVertices[gfx::VertexType::Color].set(3, 0.822f,  0.569f,  0.201f);
        this->mVertices[gfx::VertexType::Color].set(4, 0.435f,  0.602f,  0.223f);
        this->mVertices[gfx::VertexType::Color].set(5, 0.310f,  0.747f,  0.185f);
        this->mVertices[gfx::VertexType::Color].set(6, 0.597f,  0.770f,  0.761f);
        this->mVertices[gfx::VertexType::Color].set(7, 0.559f,  0.436f,  0.730f);
        this->mVertices[gfx::VertexType::Color].set(8, 0.359f,  0.583f,  0.152f);
        this->mVertices[gfx::VertexType::Color].set(9, 0.483f,  0.596f,  0.789f);
        this->mVertices[gfx::VertexType::Color].set(10, 0.559f,  0.861f,  0.639f);
        this->mVertices[gfx::VertexType::Color].set(11, 0.195f,  0.548f,  0.859f);
        this->mVertices[gfx::VertexType::Color].set(12, 0.014f,  0.184f,  0.576f);
        this->mVertices[gfx::VertexType::Color].set(13, 0.771f,  0.328f,  0.970f);
        this->mVertices[gfx::VertexType::Color].set(14, 0.406f,  0.615f,  0.116f);
        this->mVertices[gfx::VertexType::Color].set(15, 0.676f,  0.977f,  0.133f);
        this->mVertices[gfx::VertexType::Color].set(16, 0.971f,  0.572f,  0.833f);
        this->mVertices[gfx::VertexType::Color].set(17, 0.140f,  0.616f,  0.489f);
        this->mVertices[gfx::VertexType::Color].set(18, 0.997f,  0.513f,  0.064f);
        this->mVertices[gfx::VertexType::Color].set(19, 0.945f,  0.719f,  0.592f);
        this->mVertices[gfx::VertexType::Color].set(20, 0.543f,  0.021f,  0.978f);
        this->mVertices[gfx::VertexType::Color].set(21, 0.279f,  0.317f,  0.505f);
        this->mVertices[gfx::VertexType::Color].set(22, 0.167f,  0.620f,  0.077f);
        this->mVertices[gfx::VertexType::Color].set(23, 0.347f,  0.857f,  0.137f);
        this->mVertices[gfx::VertexType::Color].set(24, 0.055f,  0.953f,  0.042f);
        this->mVertices[gfx::VertexType::Color].set(25, 0.714f,  0.505f,  0.345f);
        this->mVertices[gfx::VertexType::Color].set(26, 0.783f,  0.290f,  0.734f);
        this->mVertices[gfx::VertexType::Color].set(27, 0.722f,  0.645f,  0.174f);
        this->mVertices[gfx::VertexType::Color].set(28, 0.302f,  0.455f,  0.848f);
        this->mVertices[gfx::VertexType::Color].set(29, 0.225f,  0.587f,  0.040f);
        this->mVertices[gfx::VertexType::Color].set(30, 0.517f,  0.713f,  0.338f);
        this->mVertices[gfx::VertexType::Color].set(31, 0.517f,  0.713f,  0.338f);
        this->mVertices[gfx::VertexType::Color].set(32, 0.053f,  0.959f,  0.120f);
        this->mVertices[gfx::VertexType::Color].set(33, 0.393f,  0.621f,  0.362f);
        this->mVertices[gfx::VertexType::Color].set(34, 0.673f,  0.211f,  0.457f);
        this->mVertices[gfx::VertexType::Color].set(35, 0.820f,  0.883f,  0.371f);
         */
    }

    ::gfx::Shader *Cube::shader() noexcept {
        return this->pWindow->getRenderer()->getShader(gfx::ShaderType::SimpleColor);
    }

    void Cube::update(float dt) noexcept {
        VertexNode::update(dt);
    }
}