#ifndef D2_VERTEXNODE_H
#define D2_VERTEXNODE_H

#include <ananasgfx/gfx/Vertex.hpp>
#include <ananasgfx/gfx/Shader.hpp>
#include "Node.hpp"

namespace d2 {

    class VertexNode : public Node {
    public:
        bool init() noexcept override;
        void draw() noexcept override;

        virtual ::gfx::Shader* shader() noexcept = 0;
        virtual void updateIndices() noexcept = 0;
        virtual void updateVertices() noexcept = 0;

        void setPosition(float x, float y) noexcept override;
        void setRotation(float rotation) noexcept override;
        void setScale(float x , float y) noexcept override;
        void setSize(float x, float y) noexcept override;
        void setAnchorPoint(float x, float y) noexcept override;
        void setParentPositionOffset(float x, float y) noexcept override;
        void setParentRotationOffset(float rotation) noexcept override;

        void setColor(const glm::vec4& color) noexcept;

    protected:
        void updateModelMatrix() noexcept;

    protected:
        glm::mat4 mModelMatrix = glm::mat4(1.0f);
        glm::mat4 mModelViewProjectionMatrix;
        ::gfx::Shader* pShader = nullptr;
        ::gfx::ShaderUniform* pMvpUniform = nullptr;
        ::gfx::ShaderUniform* pColorUniform = nullptr;
        ::gfx::Vertices mVertices;
        glm::vec4 mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    };

}

#endif