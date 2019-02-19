#include "../Catch.hpp"
#include <ananasgfx/gfx/Application.hpp>

class TestApplication : public gfx::Application {
public:
    bool init() noexcept override {
        return false;
    }
};

TEST_CASE("gfx::Application") {

    TestApplication application;

    SECTION("void registerWindow(std::shared_ptr<Window>) noexcept") {
        REQUIRE(application.getWindows().empty());
        application.registerWindow(gfx::Window::create(gfx::WindowConfiguration()));
        REQUIRE(application.getWindows().size() == 1);
    }

    SECTION("std::optional<gfx::Node*> getNode(const std::string&) noexcept") {
        auto window = gfx::Window::create(gfx::WindowConfiguration());
        application.registerWindow(window);
        auto scene = std::make_shared<gfx::Scene>();
        window->addScene(scene);

        SECTION("Get the scene") {
            auto sceneOpt = application.getNode("window.scene");
            REQUIRE(sceneOpt.has_value());
            REQUIRE(*sceneOpt == scene.get());
        }

        auto plainNode = scene->createChild<gfx::Node>();
        plainNode->setId("mynode");

        SECTION("Get a node at the root") {
            auto plainNodeOpt = application.getNode("window.scene.mynode");
            REQUIRE(plainNodeOpt.has_value());
            REQUIRE(*plainNodeOpt == plainNode);

            auto unknownNodeOpt = application.getNode("window.scene.unknown");
            REQUIRE_FALSE(unknownNodeOpt.has_value());
        }

        auto secondLevelNode = plainNode->createChild<gfx::Node>();
        secondLevelNode->setId("secLvlNode");

        SECTION("Get a node at the second level") {
            auto secLvlNodeOpt = application.getNode("window.scene.mynode.secLvlNode");
            REQUIRE(secLvlNodeOpt.has_value());
            REQUIRE(*secLvlNodeOpt == secondLevelNode);

            auto unknownNodeOpt = application.getNode("window.scene.secLvlNode");
            REQUIRE_FALSE(unknownNodeOpt.has_value());
        }
    }

}