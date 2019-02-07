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


class Primitives2dScene : public gfx::Scene {
public:
    bool init() noexcept override {
        // Set background color
        this->pWindow->getRenderer()->setClearColor(0.03f, 0.25f, 0.025f, 1.0f);
/*
        auto clippingNode = createChild<gfx::ClippingNode>();
        auto stencil = clippingNode->createStencil<d2::Rectangle>();
        stencil->setSize(this->pWindow->getWidth() * 0.5f, this->pWindow->getHeight());
        stencil->setPosition(this->pWindow->getWidth() * 0.5f, this->pWindow->getHeight() * 0.5f);
        stencil->setAnchorPoint(0.5f, 0.5f);
*/
        // Create rectangle
        this->pRectangle = this->createChild<d2::Rectangle>();
        this->pRectangle->setSize(50, 50);
        this->pRectangle->setPosition(0,10);
        this->pRectangle->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        // Create a child ring that moves automatically with its parent
        auto childRing = this->pRectangle->createChild<d2::Ring>();
        childRing->setSize(65, 65);
        childRing->setPosition(this->pRectangle->getSize().x * 0.5f, this->pRectangle->getSize().y * 0.5f);
        childRing->setAnchorPoint(0.5f, 0.5f);

        // Create sprite
        this->pSprite = createChild<d2::Sprite>();
        this->pSprite->setFilename("resource/icon_lightbulb.png");
        this->pSprite->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        this->pSprite->setZIndex(2);
        this->pSprite->setPosition(75, 200);
        this->pSprite->setAnchorPoint(0.5f, 0.5f);

        // Create other rectangle that is a child of the sprite
        this->pChildRect = this->pSprite->createChild<d2::Rectangle>();
        this->pChildRect->setColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
        this->pChildRect->setSize(50, 50);
        this->pChildRect->setPosition(100, 200);
        this->pChildRect->setAnchorPoint(0.5f, 0.5f);

        // Create a circle that is in the middle of the screen
        auto circle = createChild<d2::Circle>();
        circle->setPosition(this->getWindow()->getWidth() * 0.5f, this->getWindow()->getHeight() * 0.5f);
        circle->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        circle->setZIndex(2);
        circle->setSize(128, 128);
        circle->setColor(glm::vec4(0.33f, 0.9f, 0.01f, 1.0f));

        // Create a rectangle with round corners
        auto cornerRect = createChild<d2::RectangleRoundCorner>();
        cornerRect->setSize(100, 100);
        cornerRect->setPosition(this->getWindow()->getWidth() - 10, this->getWindow()->getHeight() - 10);
        cornerRect->setAnchorPoint(1.0f, 1.0f);

        // Create a ring
        auto ring = createChild<d2::Ring>();
        ring->setSize(300, 300);
        ring->setAnchorPoint(0.0f, 1.0f);
        ring->setPosition(10, this->getWindow()->getHeight() - 10);

        // Create a label
        auto label = createChild<d2::Label>();
        label->setText("Ich bin ABC");
        label->setSize(150,150);
        label->setPosition(200,200);

        return gfx::Scene::init();
    }

    void update(float dt) noexcept override {
        Scene::update(dt);

        // Move the rectangle
        float rectangleSpeed = dt * 125.0f * (!this->mRectangleGoRight ? -1.0f : 1.0f);
        this->pRectangle->setPosition(this->pRectangle->getPosition().x + rectangleSpeed, this->pRectangle->getPosition().y);
        if (this->mRectangleGoRight && this->pRectangle->getPosition().x + this->pRectangle->getSize().x >= this->pWindow->getWidth()) {
            this->mRectangleGoRight = false;
        }
        if (!this->mRectangleGoRight && this->pRectangle->getPosition().x <= 0.0f) {
            this->mRectangleGoRight = true;
        }

        // Rotate the sprite
        this->pSprite->setRotation(this->pSprite->getRotation() + dt);
/*
        auto rendertexture = this->pSprite->asRenderTexture();
        auto bitmap = rendertexture->toBitmap();
        if (bitmap.has_value()) {
            (*bitmap)->saveAsFile("file.png");
        }*/
    }

private:
    d2::Rectangle* pRectangle = nullptr;
    bool mRectangleGoRight = true;

    d2::Sprite* pSprite = nullptr;
    d2::Rectangle* pChildRect = nullptr;

    std::shared_ptr<gfx::RenderTexture> mRenderTexture;
};

class Primitives2dApp : public gfx::Application {
public:
    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(640);
        windowConfiguration.setHeight(480);
        windowConfiguration.setTitle("My first window");
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<Primitives2dScene>());
        registerWindow(window);

        if (!window->getFontManager().registerFont("resource/Roboto-Bold.ttf", "Roboto", "Bold")) {
            std::cerr << __PRETTY_FUNCTION__ << " FONT FAIL" << std::endl;
            return false;
        }

        return true;
    }
};
REGISTER_APPLICATION("Primitives2d", Primitives2dApp);
