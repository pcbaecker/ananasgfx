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
#include <ananasgfx/font/FontManager.hpp>
#include <random>

class RendertextureScene : public gfx::Node {
public:
    RendertextureScene() :
    mRandomEngine(mRandomDevice()),
    mDistribution(0, 1) {}

    bool init() noexcept override {
        // Set background color
        this->pWindow->getRenderer()->setClearColor(1.0f,1.0f, 1.0f, 1.0f);

        // Rendertexture
        this->mRenderTexture = std::make_shared<gfx::RenderTexture>(this->pWindow, this->pWindow->getWidth(), this->pWindow->getHeight());
        this->mRenderTexture->begin();
        this->pWindow->getRenderer()->clearScreen();
        this->mRenderTexture->end();

        // The sprite to display the rendertexture
        this->pRTSprite = createChild<d2::Sprite>();
        this->pRTSprite->setTexture(this->mRenderTexture.get());
        this->pRTSprite->setAnchorPoint(0.0f, 0.0f);
        this->pRTSprite->setPosition(0.0f, 0.0f);
        this->pRTSprite->setVerticalFlip(true);

        // The circle to be drawn onto the rendertexture
        this->pCircle = createChild<d2::Circle>();
        this->pCircle->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        this->pCircle->setAnchorPoint(0.5f, 0.5f);
        this->pCircle->setSize(25.0f, 25.0f);
        this->pCircle->setPosition(0.0f, 0.0f);
        this->pCircle->setVisible(false);

        return gfx::Node::init();
    }

protected:

    void drawCircle(float x, float y) noexcept {
        this->mRenderTexture->begin();
        this->pCircle->setPosition(x, y);
        this->pCircle->setVisible(true);
        this->pCircle->draw();
        this->pCircle->setVisible(false);
        this->mRenderTexture->end();
    }

    void onTouchBegan(gfx::Touch &touch) noexcept override {
        drawCircle(static_cast<float>(touch.getLastX()), static_cast<float>(touch.getLastY()));
    }

    void onTouchMoved(gfx::Touch &touch) noexcept override {
        drawCircle(static_cast<float>(touch.getLastX()), static_cast<float>(touch.getLastY()));
    }

    void onTouchEnded(gfx::Touch &touch) noexcept override {
        this->pCircle->setColor(glm::vec4(randomFloat(), randomFloat(), randomFloat(), 1.0f));
    }

    float randomFloat() {
        return static_cast<float>(this->mDistribution(this->mRandomEngine));
    }

private:
    d2::Sprite* pRTSprite = nullptr;
    d2::Circle* pCircle = nullptr;
    std::shared_ptr<gfx::RenderTexture> mRenderTexture;

    std::random_device mRandomDevice;
    std::mt19937 mRandomEngine;
    std::uniform_real_distribution<> mDistribution;
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
        window->addRootNode(std::make_shared<RendertextureScene>());
        registerWindow(window);

        return true;
    }
};
REGISTER_APPLICATION("Rendertexture", RendertextureApp);
