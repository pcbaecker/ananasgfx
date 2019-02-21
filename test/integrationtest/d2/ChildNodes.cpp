#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/d2/Rectangle.hpp>

class TestChildNodesScene : public gfx::Scene {
public:
    bool init() noexcept override {
        //
        auto rectOne = createChild<d2::Rectangle>();
        rectOne->setId("one");
        rectOne->setPosition(32.0f, 32.0f);
        rectOne->setAnchorPoint(0.0f, 0.0f);
        rectOne->setSize(128.0f, 128.0f);

        //
        auto rectTwo = rectOne->createChild<d2::Rectangle>();
        rectTwo->setId("two");
        rectTwo->setPosition(0.0f, 0.0f);
        rectTwo->setAnchorPoint(0.0f, 0.0f);
        rectTwo->setSize(64.0f, 64.0f);
        rectTwo->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        rectTwo->setZIndex(2);

        //
        auto rectThree = rectTwo->createChild<d2::Rectangle>();
        rectThree->setId("three");
        rectThree->setPosition(32.0f, 32.0f);
        rectThree->setAnchorPoint(0.0f, 0.0f);
        rectThree->setSize(64.0f, 64.0f);
        rectThree->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        rectThree->setZIndex(1);

        return gfx::Scene::init();
    }
};

class TestChildNodesApplication : public gfx::Application {

    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(200);
        windowConfiguration.setHeight(200);
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<TestChildNodesScene>());
        registerWindow(window);

        return true;
    }

};

REGISTER_APPLICATION("2d childnodes", TestChildNodesApplication);

class TestChildNodesApplicationTest : public test::ApplicationTest {
public:
    void run() noexcept override {
        Compare("window.scene", "fixtures/d2/childNodes/first.png");

        Control<d2::Rectangle>("window.scene.one", [](gfx::Application *app, d2::Rectangle *rect) {
            rect->setPosition(150.0f, 150.0f);
        });

        Compare("window.scene", "fixtures/d2/childNodes/second.png");
    }
};

REGISTER_APPLICATIONTEST("2d childnodes", TestChildNodesApplicationTest);