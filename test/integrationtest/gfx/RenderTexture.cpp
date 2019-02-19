#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/d2/Sprite.hpp>

class TestRenderTextureScene : public gfx::Scene {
public:
    bool init() noexcept override {
        // Create a label that is in the middle of the screen
        auto sprite = createChild<d2::Sprite>();
        sprite->setId("sprite");
        sprite->setPosition(0.0f, 0.0f);
        sprite->setAnchorPoint(0.0f, 0.0f);
        sprite->setFilename("fixtures/d2/renderTexture/sprite.png");

        return gfx::Scene::init();
    }

    std::shared_ptr<gfx::RenderTexture> renderTexture;
};

class TestRenderTextureApplication : public gfx::Application {

    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(256);
        windowConfiguration.setHeight(256);
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<TestRenderTextureScene>());
        registerWindow(window);

        return true;
    }

};

REGISTER_APPLICATION("d2::RenderTexture", TestRenderTextureApplication);

class TestRenderTextureApplicationTest : public test::ApplicationTest {
public:
    void run() noexcept override {
        // The scene without additional render texture
        Compare("window.scene", "fixtures/d2/renderTexture/no-rt.png");

        // Render the scene into a rendertexture and display that
        Control<TestRenderTextureScene>("window.scene", [](gfx::Application *app, TestRenderTextureScene* scene) {
            // Render the whole scene into a texture
            scene->renderTexture = scene->asRenderTexture();

            // Create a new sprite to display the texture (per default an render texture is flipped, we use that for mirroring the sprite)
            auto s = scene->createChild<d2::Sprite>();
            s->setTexture(scene->renderTexture.get());
            s->setAnchorPoint(0.0f, 0.0f);
            s->setPosition(0.0f, 0.0f);

            // TODO Make the nodes automatically initialized instead of this manual
            s->init();
        });

        // The scene WITH render texture
        Compare("window.scene", "fixtures/d2/renderTexture/with-rt.png");

    }
};

REGISTER_APPLICATIONTEST("d2::RenderTexture", TestRenderTextureApplicationTest);