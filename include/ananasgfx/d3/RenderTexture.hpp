#ifndef D3_NODE_H
#define D3_NODE_H

#include <glm/glm.hpp>
#include <ananasgfx/gfx/Node.hpp>

namespace d3 {

    class Node : public ::gfx::Node {
    public:
        bool init() noexcept override;

        virtual void setPosition(float x, float y, float z) noexcept;
        const glm::vec3& getPosition() const noexcept;
        virtual void setRotation(float x, float y, float z) noexcept;
        const glm::vec3& getRotation() const noexcept;
        virtual void setScale(float x , float y, float z) noexcept;
        const glm::vec3& getScale() const noexcept;

    protected:
        glm::vec3 mPosition;
        glm::vec3 mRotation;
        glm::vec3 mScale = glm::vec3(1.0f);
    };

}

#endif