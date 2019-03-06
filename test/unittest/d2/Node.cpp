#include <ananasgfx/d2/Node.hpp>

#include "../Catch.hpp"

TEST_CASE("d2::Node") {

    d2::Node node;

    SECTION("bool init() noexcept") {
        REQUIRE(node.init());
    }

    SECTION("void setPosition(float, float)") {
        node.setPosition(15.0f, 16.0f);
        REQUIRE(node.getPosition().x == Approx(15.0f));
        REQUIRE(node.getPosition().y == Approx(16.0f));
    }

    SECTION("setPosition(const glm::vec2&)") {
        node.setPosition(glm::vec2(10.0f, 12.0f));
        REQUIRE(node.getPosition().x == Approx(10.0f));
        REQUIRE(node.getPosition().y == Approx(12.0f));
    }

    SECTION("const glm::vec2& getPosition() const") {
        node.setPosition(glm::vec2(9.0f, 3.0f));
        REQUIRE(node.getPosition().x == Approx(9.0f));
        REQUIRE(node.getPosition().y == Approx(3.0f));
    }

    SECTION("void setScale(float, float)") {
        node.setScale(3.0f, 4.0f);
        REQUIRE(node.getScale().x == Approx(3.0f));
        REQUIRE(node.getScale().y == Approx(4.0f));
    }

    SECTION("void setScale(float)") {
        node.setScale(5.0f);
        REQUIRE(node.getScale().x == Approx(5.0f));
        REQUIRE(node.getScale().y == Approx(5.0f));
    }

    SECTION("void setScale(const glm::vec2&)") {
        node.setScale(glm::vec2(9.0f, 2.0f));
        REQUIRE(node.getScale().x == Approx(9.0f));
        REQUIRE(node.getScale().y == Approx(2.0f));
    }

    SECTION("const glm::vec2& getScale() const") {
        node.setScale(3.0f, 4.0f);
        REQUIRE(node.getScale().x == Approx(3.0f));
        REQUIRE(node.getScale().y == Approx(4.0f));
    }

    SECTION("void setSize(float, float)") {
        node.setSize(1.5f, 3.5f);
        REQUIRE(node.getSize().x == Approx(1.5f));
        REQUIRE(node.getSize().y == Approx(3.5f));
    }

    SECTION("void setSize(const glm::vec2&)") {
        node.setSize(glm::vec2(2.5f, 7.3f));
        REQUIRE(node.getSize().x == Approx(2.5f));
        REQUIRE(node.getSize().y == Approx(7.3f));
    }

    SECTION("const glm::vec2& getSize() const") {
        node.setSize(1.5f, 3.5f);
        REQUIRE(node.getSize().x == Approx(1.5f));
        REQUIRE(node.getSize().y == Approx(3.5f));
    }

    SECTION("void setAnchorPoint(float, float)") {
        node.setAnchorPoint(1.3f, 0.4f);
        REQUIRE(node.getAnchorPoint().x == Approx(1.3f));
        REQUIRE(node.getAnchorPoint().y == Approx(0.4f));
    }

    SECTION("void setAnchorPoint(const glm::vec2&)") {
        node.setAnchorPoint(glm::vec2(4.2f, 5.1f));
        REQUIRE(node.getAnchorPoint().x == Approx(4.2f));
        REQUIRE(node.getAnchorPoint().y == Approx(5.1f));
    }

    SECTION("const glm::vec2& getAnchorPoint() const") {
        node.setAnchorPoint(1.3f, 0.4f);
        REQUIRE(node.getAnchorPoint().x == Approx(1.3f));
        REQUIRE(node.getAnchorPoint().y == Approx(0.4f));
    }

    SECTION("void setRotation(float)") {
        node.setRotation(45.2f);
        REQUIRE(node.getRotation() == 45.2f);
    }

    SECTION("float getRotation() const") {
        node.setRotation(45.2f);
        REQUIRE(node.getRotation() == 45.2f);
    }

    SECTION("void setParentPositionOffset(float, float)") {
        node.setParentPositionOffset(1.4f, 5.2f);
        REQUIRE(node.getParentPositionOffset().x == Approx(1.4f));
        REQUIRE(node.getParentPositionOffset().y == Approx(5.2f));
    }

    SECTION("void setParentPositionOffset(const glm::vec2&)") {
        node.setParentPositionOffset(glm::vec2(4.1f, 9.6f));
        REQUIRE(node.getParentPositionOffset().x == Approx(4.1f));
        REQUIRE(node.getParentPositionOffset().y == Approx(9.6f));
    }

    SECTION("const glm::vec2& getParentPositionOffset() const") {
        node.setParentPositionOffset(1.2f, 5.4f);
        REQUIRE(node.getParentPositionOffset().x == Approx(1.2f));
        REQUIRE(node.getParentPositionOffset().y == Approx(5.4f));
    }

    SECTION("glm::vec2 getScreenPosition() const") {
        auto pos = node.getScreenPosition();
        REQUIRE(pos.x == Approx(0.0f));
        REQUIRE(pos.y == Approx(0.0f));

        node.setParentPositionOffset(100.0f, 200.0f);
        pos = node.getScreenPosition();
        REQUIRE(pos.x == Approx(100.0f));
        REQUIRE(pos.y == Approx(200.0f));

        node.setPosition(25.0f, 30.0f);
        pos = node.getScreenPosition();
        REQUIRE(pos.x == Approx(125.0f));
        REQUIRE(pos.y == Approx(230.0f));
    }

    SECTION("void setParentRotationOffset(float rotation)") {
        node.setParentRotationOffset(45.0f);
        REQUIRE(node.getParentRotationOffset() == Approx(45.0f));
    }

    SECTION("float getParentRotationOffset() const") {
        node.setParentRotationOffset(46.0f);
        REQUIRE(node.getParentRotationOffset() == Approx(46.0f));
    }

    SECTION("void setZIndex(uint8_t) noexcept") {
        // Test default value
        REQUIRE(0 == node.getZIndex());

        // Set the z-index
        node.setZIndex(123);
        REQUIRE(123 == node.getZIndex());
    }

    SECTION("uint8_t getZIndex() const noexcept") {
        // Test default value
        REQUIRE(0 == node.getZIndex());

        // Set the z-index
        node.setZIndex(123);
        REQUIRE(123 == node.getZIndex());
    }

    SECTION("gfx::nodePriority_t getPriority() const noexcept") {
        // Test default value
        REQUIRE(1024 == node.getPriority());

        // Adjust by setting the z-index
        node.setZIndex(3);
        REQUIRE(1027 == node.getPriority());
    }

    SECTION("std::shared_ptr<gfx::RenderTexture> asRenderTexture() noexcept") {
        // This method cannot be tested without a working OpenGL context
    }

    SECTION("Parent position and rotation offset propagated to child nodes") {
        node.setPosition(25.0f, 30.0f);
        node.setAnchorPoint(0.0f, 0.0f);
        node.setRotation(32.0f);
        REQUIRE(node.init());//< nodes must be initialized to make sure offset is propagated on createChild()
        auto pos = node.getScreenPosition();
        REQUIRE(pos.x == Approx(25.0f));
        REQUIRE(pos.y == Approx(30.0f));
        REQUIRE(node.getRotation() == Approx(32.0f));
        REQUIRE(node.getParentRotationOffset() == Approx(0.0f));

        auto childOne = node.createChild<d2::Node>();
        childOne->setPosition(50.0f, 55.0f);
        childOne->setAnchorPoint(0.0f, 0.0f);
        childOne->setRotation(65.0f);
        REQUIRE(childOne->init());
        pos = childOne->getScreenPosition();
        REQUIRE(pos.x == Approx(75.0f));
        REQUIRE(pos.y == Approx(85.0f));
        REQUIRE(childOne->getRotation() == Approx(65.0f));
        REQUIRE(childOne->getParentRotationOffset() == Approx(32.0f));

        auto childTwo = childOne->createChild<d2::Node>();
        childTwo->setPosition(12.0f, 13.0f);
        childTwo->setRotation(9.0f);
        pos = childTwo->getScreenPosition();
        REQUIRE(pos.x == Approx(87.0f));
        REQUIRE(pos.y == Approx(98.0f));
        REQUIRE(childTwo->getRotation() == Approx(9.0f));
        REQUIRE(childTwo->getParentRotationOffset() == Approx(97.0f));
    }

    SECTION("void onTouchBegan(const gfx::Touch&) noexcept") {
        // TODO
    }

    SECTION("void onTouchMoved(const gfx::Touch&) noexcept") {
        // TODO
    }

    SECTION("void onTouchEnded(const gfx::Touch&) noexcept") {
        // TODO
    }

    SECTION("bool contains(float, float) noexcept") {
        // TODO
    }

    SECTION("void onTouchBegan(const float, const float, const gfx::Touch&) noexcept") {
        // TODO
    }

    SECTION("void onTouchMoved(const float, const float, const gfx::Touch&) noexcept") {
        // TODO
    }

    SECTION("void onTouchEnded(const float, const float,const gfx::Touch&) noexcept") {
        // TODO
    }

}