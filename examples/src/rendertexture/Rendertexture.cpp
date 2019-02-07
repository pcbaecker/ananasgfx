#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/gfx/ClippingNode.hpp>
#include <ananasgfx/gfx/RenderTexture.hpp>
#include <ananasgfx/d2/Rectangle.hpp>
#include <ananasgfx/d2/Sprite.hpp>
#include <ananasgfx/d2/Circle.hpp>
#include <ananasgfx/d2/Ring.hpp>
#include <ananasgfx/d2/Label.hpp>
#include <ananasgfx/d2/RectangleRoundCorner.hpp>
#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/gfx/Scene.hpp>
#include <ananasgfx/font/FontManager.hpp>

class RendertextureScene : public gfx::Scene {
public:
    bool init() noexcept override {
        // Set background color
        this->pWindow->getRenderer()->setClearColor(0.0f, 0.0f, 0.05f, 0.0f);

        // Create sprite
        this->pSprite = createChild<d2::Sprite>();
        this->pSprite->setFilename("resource/icon_lightbulb.png");
        this->pSprite->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        this->pSprite->setPosition(75, 200);
        this->pSprite->setAnchorPoint(0.5f, 0.5f);

        // Rendertexture
        this->mRenderTexture = std::make_shared<gfx::RenderTexture>(this->pWindow, this->pWindow->getWidth()*0.5f, this->pWindow->getHeight()*0.5f);
        this->pRTSprite = createChild<d2::Sprite>();
        this->pRTSprite->setTexture(this->mRenderTexture.get());
        this->pRTSprite->setAnchorPoint(0.0f, 0.0f);
        this->pRTSprite->setPosition(this->pWindow->getWidth()*0.5f, 0.0f);
        this->pRTSprite->setVerticalFlip(true);

        return gfx::Scene::init();
    }

    void update(float dt) noexcept override {
        gfx::Scene::update(dt);

        this->mRenderTexture->begin();
        this->pWindow->getRenderer()->clearScreen();
        this->pSprite->draw();
        this->mRenderTexture->end();
    }

private:
    d2::Sprite* pSprite = nullptr;
    d2::Sprite* pRTSprite = nullptr;
    std::shared_ptr<gfx::RenderTexture> mRenderTexture;
};

class RendertextureApp : public gfx::Application {
public:
    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(640);
        windowConfiguration.setHeight(480);
        windowConfiguration.setTitle("Rendertexture example");
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<RendertextureScene>());
        registerWindow(window);

        return true;
    }
};
REGISTER_APPLICATION("Rendertexture", RendertextureApp);
