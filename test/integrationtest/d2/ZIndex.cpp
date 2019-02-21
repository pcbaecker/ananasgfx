#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/d2/Rectangle.hpp>

class TestZIndexScene : public gfx::Scene {
public:
    bool init() noexcept override {
        //
        auto rectOne = createChild<d2::Rectangle>();
        rectOne->setId("one");
        rectOne->setPosition(32.0f, 32.0f);
        rectOne->setAnchorPoint(0.0f, 0.0f);
        rectOne->setSize(64.0f, 64.0f);
        rectOne->setZIndex(1);

        //
        auto rectTwo = createChild<d2::Rectangle>();
        rectTwo->setId("two");
        rectTwo->setPosition(64.0f, 64.0f);
        rectTwo->setAnchorPoint(0.0f, 0.0f);
        rectTwo->setSize(64.0f, 64.0f);
        rectTwo->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        rectTwo->setZIndex(2);

        //
        auto rectThree = createChild<d2::Rectangle>();
        rectThree->setId("three");
        rectThree->setPosition(96.0f, 96.0f);
        rectThree->setAnchorPoint(0.0f, 0.0f);
        rectThree->setSize(64.0f, 64.0f);
        rectThree->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        rectThree->setZIndex(3);

        return gfx::Scene::init();
    }
};

class TestZIndexApplication : public gfx::Application {

    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(200);
        windowConfiguration.setHeight(200);
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<TestZIndexScene>());
        registerWindow(window);

        return true;
    }

};

REGISTER_APPLICATION("2d ZIndex", TestZIndexApplication);

class TestZIndexApplicationTest : public test::ApplicationTest {
public:
    void run() noexcept override {
        Compare("window.scene", "fixtures/d2/zindex/first.png");

        Control<d2::Rectangle>("window.scene.one", [](gfx::Application *app, d2::Rectangle *rect) {
            rect->setZIndex(3);
        });
        Control<d2::Rectangle>("window.scene.three", [](gfx::Application *app, d2::Rectangle *rect) {
            rect->setZIndex(1);
        });

        Compare("window.scene", "fixtures/d2/zindex/second.png");
    }
};

REGISTER_APPLICATIONTEST("2d ZIndex", TestZIndexApplicationTest);