#ifndef D3_VERTEXNODE_H
#define D3_VERTEXNODE_H

#include <ananasgfx/gfx/Vertex.hpp>
#include <ananasgfx/gfx/Shader.hpp>
#include "Node.hpp"

namespace d3 {

    class VertexNode : public ::d3::Node {
    public:
        bool init() noexcept override;
        void draw() noexcept override;

        virtual ::gfx::Shader* shader() noexcept = 0;
        virtual void updateIndices() noexcept = 0;
        virtual void updateVertices() noexcept = 0;

        void setPosition(float x, float y, float z) noexcept override;
        void setRotation(float x, float y, float z) noexcept override;
        void setScale(float x , float y, float z) noexcept override;

    protected:
        void updateModelMatrix() noexcept;

    protected:
        glm::mat4 mModelMatrix = glm::mat4(1.0f);
        ::gfx::Shader* pShader = nullptr;
        ::gfx::ShaderUniform* pMvpUniform = nullptr;
        ::gfx::Vertices mVertices;
    };

}

#endif