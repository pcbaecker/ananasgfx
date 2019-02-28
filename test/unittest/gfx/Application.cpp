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

    SECTION("void tick() noexcept") {
        // Because no windows are registed there will not happen anything
        application.tick();
    }

    SECTION("bool isDone() const noexcept") {
        // No windows registered
        REQUIRE(application.isDone());

        // With window registered.
        application.registerWindow(gfx::Window::create(gfx::WindowConfiguration()));
        REQUIRE_FALSE(application.isDone());
    }

    SECTION("void close() noexcept") {
        // No windows registered
        REQUIRE(application.isDone());

        // With window registered.
        application.registerWindow(gfx::Window::create(gfx::WindowConfiguration()));
        REQUIRE_FALSE(application.isDone());

        // Close will dispose all windows
        application.close();
        REQUIRE(application.isDone());
    }

    SECTION("void setMaxLifetime(long) noexcept") {
        // Check default value
        REQUIRE(0 == application.getMaxLifetime());

        // Set value
        application.setMaxLifetime(123);
        REQUIRE(123 == application.getMaxLifetime());
    }

    SECTION("long getMaxLifetime() const noexcept") {
        // Check default value
        REQUIRE(0 == application.getMaxLifetime());

        // Set value
        application.setMaxLifetime(123);
        REQUIRE(123 == application.getMaxLifetime());
    }

    SECTION("void addTask(std::shared_ptr<Task>) noexcept") {
        // We can add a task but not query if it is correctly stored because that would involve complex concurrent semantics
        application.addTask(nullptr);
    }

    SECTION("std::list<std::shared_ptr<Window>>& getWindows() noexcept") {
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

    SECTION("void setDevmode(bool devmode) noexcept") {
        // Default value
        REQUIRE_FALSE(application.isDevmode());

        // Set value
        application.setDevmode(true);
        REQUIRE(application.isDevmode());
    }

    SECTION("bool isDevmode() const noexcept") {
        // Default value
        REQUIRE_FALSE(application.isDevmode());

        // Set value
        application.setDevmode(true);
        REQUIRE(application.isDevmode());
    }

    SECTION("const FileManager& getFileManager() const") {
        // Default value
        REQUIRE_THROWS_AS(application.getFileManager(), gfx::ApplicationException);

        // Set value
        auto fm = std::make_shared<gfx::FileManager>("","");
        application.setFileManager(fm);
        REQUIRE(fm.get() == &application.getFileManager());
    }

    SECTION("void setFileManager(std::shared_ptr<FileManager>) noexcept") {
        // Default value
        REQUIRE_THROWS_AS(application.getFileManager(), gfx::ApplicationException);

        // Set value
        auto fm = std::make_shared<gfx::FileManager>("","");
        application.setFileManager(fm);
        REQUIRE(fm.get() == &application.getFileManager());
    }
}