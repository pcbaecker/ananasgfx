#include <ananasgfx/d2/VertexNode.hpp>
#include "../Catch.hpp"

class DummyVertexNode : public d2::VertexNode {
public:
    ::gfx::Shader* shader() noexcept override {
        return nullptr;
    }
    void updateIndices() noexcept override {}
    void updateVertices() noexcept override {}
};

TEST_CASE("d2::VertexNode") {

    DummyVertexNode vertexNode;

    SECTION("bool init() noexcept") {
        // Can not be tested without working OpenGL context
    }

    SECTION("void draw() noexcept") {
        // Can not be tested without working OpenGL context
    }

    SECTION("void setPosition(float, float) noexcept") {
        vertexNode.setPosition(123.0f, 234.0f);
        REQUIRE(Approx(123.0f) == vertexNode.getPosition().x);
        REQUIRE(Approx(234.0f) == vertexNode.getPosition().y);
    }

    SECTION("void setRotation(float) noexcept") {
        vertexNode.setRotation(567.0f);
        REQUIRE(Approx(567.0f) == vertexNode.getRotation());
    }

    SECTION("void setScale(float, float) noexcept") {
        vertexNode.setScale(234.0f, 456.0f);
        REQUIRE(Approx(234.0f) == vertexNode.getScale().x);
        REQUIRE(Approx(456.0f) == vertexNode.getScale().y);
    }

    SECTION("void setSize(float, float) noexcept") {
        vertexNode.setSize(765.0f, 254.0f);
        REQUIRE(Approx(765.0f) == vertexNode.getSize().x);
        REQUIRE(Approx(254.0f) == vertexNode.getSize().y);
    }

    SECTION("void setAnchorPoint(float, float) noexcept") {
        vertexNode.setAnchorPoint(712.0f, 913.0f);
        REQUIRE(Approx(712.0f) == vertexNode.getAnchorPoint().x);
        REQUIRE(Approx(913.0f) == vertexNode.getAnchorPoint().y);
    }

    SECTION("void setParentPositionOffset(float, float) noexcept") {
        vertexNode.setParentPositionOffset(723.0f, 87.0f);
        REQUIRE(Approx(723.0f) == vertexNode.getParentPositionOffset().x);
        REQUIRE(Approx(87.0f) == vertexNode.getParentPositionOffset().y);
    }

    SECTION("void setParentRotationOffset(float) noexcept") {
        vertexNode.setParentRotationOffset(654.0f);
        REQUIRE(Approx(654.0f) == vertexNode.getParentRotationOffset());
    }

    SECTION("void setZIndex(uint8_t) noexcept") {
        vertexNode.setZIndex(65);
        REQUIRE(65 == vertexNode.getZIndex());
    }

    SECTION("void setColor(const glm::vec4&) noexcept") {
        glm::vec4 c(1.0f, 0.0f, 1.0f, 0.0f);
        vertexNode.setColor(c);
        REQUIRE(c == vertexNode.getColor());
    }

    SECTION("const glm::vec4& getColor() const noexcept") {
        glm::vec4 c(1.0f, 0.0f, 1.0f, 0.0f);
        vertexNode.setColor(c);
        REQUIRE(c == vertexNode.getColor());
    }

    SECTION("const gfx::Vertices& getVertices() const noexcept") {
        REQUIRE(0 == vertexNode.getVertices().getSize());
        REQUIRE(vertexNode.getVertices().getIndices().empty());
    }

}