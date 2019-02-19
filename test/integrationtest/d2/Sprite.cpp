#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/d2/Sprite.hpp>

class TestSpriteScene : public gfx::Scene {
public:
    bool init() noexcept override {
        // Create a sprite that is in the middle of the screen
        auto rect = createChild<d2::Sprite>();
        rect->setFilename("fixtures/d2/sprite/sprite.png");
        rect->setId("sprite");
        rect->setPosition(this->getWindow()->getWidth() * 0.5f, this->getWindow()->getHeight() * 0.5f);
        rect->setAnchorPoint(0.5f, 0.5f);
        rect->setSize(64, 64);

        return gfx::Scene::init();
    }
};

class TestSpriteApplication : public gfx::Application {

    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(256);
        windowConfiguration.setHeight(256);
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<TestSpriteScene>());
        registerWindow(window);

        return true;
    }

};

REGISTER_APPLICATION("d2::Sprite", TestSpriteApplication);

class TestSpriteApplicationTest : public test::ApplicationTest {
public:
    void run() noexcept override {

        Compare("window.scene", "fixtures/d2/sprite/first.png");

        Control<d2::Sprite>("window.scene.sprite", [](gfx::Application *app, d2::Sprite *sprite) {
            sprite->setPosition(20.0f, 20.0f);
            sprite->setAnchorPoint(0.0f, 0.0f);
            sprite->setSize(200, 200);
        });

        Compare("window.scene", "fixtures/d2/sprite/second.png");
    }
};

REGISTER_APPLICATIONTEST("d2::Sprite", TestSpriteApplicationTest);