#include "../Catch.hpp"
#include <ananasgfx/gfx/Node.hpp>
#include <ananasgfx/gfx/Window.hpp>
#include <ananasgfx/gfx/WindowConfiguration.hpp>

class MyNode : public gfx::Node {
public:
    gfx::nodePriority_t getPriority() const noexcept override {
        return this->mPriority;
    }

    void setPriority(gfx::nodePriority_t priority) noexcept {
        this->mPriority = priority;
    }

private:
    gfx::nodePriority_t mPriority = 0;
};

TEST_CASE("gfx::Node") {

    gfx::Node node;

    SECTION("bool init() noexcept") {
        REQUIRE_FALSE(node.isInitialized());
        REQUIRE(node.init());
        REQUIRE(node.isInitialized());
    }

    SECTION("void update(float) noexcept") {
        node.update(0.0f);
    }

    SECTION("void draw() noexcept") {
        node.draw();
    }

    SECTION("std::shared_ptr<RenderTexture> asRenderTexture() noexcept") {
        // Not testable without OpenGL context
    }

    SECTION("template<class T> T* createChild() noexcept") {
        auto child = node.createChild<MyNode>();
        REQUIRE(child->getParent() == &node);
    }

    SECTION("void setId(const std::string&) noexcept") {
        // Default value
        REQUIRE(node.getId().empty());

        // Set value
        node.setId("myid");
        REQUIRE("myid" == node.getId());
    }

    SECTION("const std::string& getId() const noexcept") {
        // Default value
        REQUIRE(node.getId().empty());

        // Set value
        node.setId("myid");
        REQUIRE("myid" == node.getId());
    }

    SECTION("std::optional<Node*> getChildWithId(const std::string&) const noexcept") {
        auto child = node.createChild<MyNode>();
        child->setId("one");

        REQUIRE_FALSE(node.getChildWithId("two").has_value());
        auto one = node.getChildWithId("one");
        REQUIRE(one.has_value());
        REQUIRE(*one == child);
    }

    SECTION("void setWindow(Window*) noexcept") {
        // Default value
        REQUIRE(nullptr == node.getWindow());

        // Set value
        auto window = gfx::Window::create(gfx::WindowConfiguration());
        node.setWindow(window.get());
        REQUIRE(window.get() == node.getWindow());
    }

    SECTION("Window* getWindow() noexcept") {
        // Default value
        REQUIRE(nullptr == node.getWindow());

        // Set value
        auto window = gfx::Window::create(gfx::WindowConfiguration());
        node.setWindow(window.get());
        REQUIRE(window.get() == node.getWindow());
    }

    SECTION("bool isInitialized() const noexcept") {
        REQUIRE_FALSE(node.isInitialized());
        REQUIRE(node.init());
        REQUIRE(node.isInitialized());
    }

    SECTION("nodePriority_t getPriority() const noexcept") {
        REQUIRE(0 == node.getPriority());
    }

    SECTION("void resortChildren() noexcept") {
        auto one = node.createChild<MyNode>();
        auto two = node.createChild<MyNode>();

        // One is the first element
        one->setPriority(1);
        two->setPriority(2);
        node.resortChildren();
        auto it = node.getChildren().begin();
        REQUIRE((*it++).get() == one);
        REQUIRE((*it).get() == two);

        // Two is the first element
        one->setPriority(2);
        two->setPriority(1);
        node.resortChildren();
        it = node.getChildren().begin();
        REQUIRE((*it++).get() == two);
        REQUIRE((*it).get() == one);
    }

    SECTION("Node* getParent() const noexcept") {
        auto one = node.createChild<MyNode>();
        REQUIRE(nullptr == node.getParent());
        REQUIRE(&node == one->getParent());
    }

    SECTION("bool isVisible() const noexcept") {
        // Default value
        REQUIRE(node.isVisible());

        // Set value
        node.setVisible(false);
        REQUIRE_FALSE(node.isVisible());
    }

    SECTION("void setVisible(bool visible) noexcept") {
        // Default value
        REQUIRE(node.isVisible());

        // Set value
        node.setVisible(false);
        REQUIRE_FALSE(node.isVisible());
    }

    SECTION("const std::list<std::shared_ptr<Node>>& getChildren() const noexcept") {
        REQUIRE(node.getChildren().empty());
        auto one = node.createChild<MyNode>();
        auto two = node.createChild<MyNode>();
        REQUIRE(node.getChildren().size() == 2);
    }

}