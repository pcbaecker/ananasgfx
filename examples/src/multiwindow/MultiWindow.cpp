#if !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)

#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/d2/RectangleRoundCorner.hpp>

glm::vec2 getRandomPosition(float maxWidth, float maxHeight) {
    return glm::vec2(
            static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/maxWidth)),
            static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/maxHeight)));
}

class MultiWindowSceneOne : public gfx::Node {
public:
    bool init() noexcept override {
        // Create the rectangle
        this->pRRC = createChild<d2::RectangleRoundCorner>();
        this->pRRC->setSize(128.0f, 128.0f);
        this->pRRC->setAnchorPoint(0.5f, 0.0f);
        this->pRRC->setPosition(64.0f, 128.0f);
        this->pRRC->setColor(glm::vec4(1.0f, 0.0f, 0.3f, 1.0f));

        return gfx::Node::init();
    }

    void update(float dt) noexcept override {
        Node::update(dt);

        this->mUpdate += dt;
        if (this->mUpdate >= 1.0f) {
            glm::vec2 pos = getRandomPosition(this->pWindow->getWidth(), this->pWindow->getHeight());
            this->pRRC->setPosition(pos.x, pos.y);
            this->mUpdate = 0.0f;
        }
    }

private:
    float mUpdate = 0.0f;
    d2::RectangleRoundCorner* pRRC = nullptr;
};

class MultiWindowSceneTwo : public gfx::Node {
public:
    bool init() noexcept override {
        // Create the rectangle
        this->pRRC = createChild<d2::RectangleRoundCorner>();
        this->pRRC->setSize(128.0f, 128.0f);
        this->pRRC->setAnchorPoint(0.5f, 0.0f);
        this->pRRC->setPosition(64.0f, 128.0f);
        this->pRRC->setColor(glm::vec4(0.0f, 1.0f, 0.3f, 1.0f));

        return gfx::Node::init();
    }

    void update(float dt) noexcept override {
        Node::update(dt);

        this->mUpdate += dt;
        if (this->mUpdate >= 1.0f) {
            glm::vec2 pos = getRandomPosition(this->pWindow->getWidth(), this->pWindow->getHeight());
            this->pRRC->setPosition(pos.x, pos.y);
            this->mUpdate = 0.0f;
        }
    }

private:
    float mUpdate = 0.0f;
    d2::RectangleRoundCorner* pRRC = nullptr;
};

class MultiWindowApp : public gfx::Application {
public:
    bool init() noexcept override {
        // Create window Configuration
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(640);
        windowConfiguration.setHeight(480);

        // Create window one
        windowConfiguration.setTitle("My first window");
        auto windowOne = gfx::Window::create(windowConfiguration);
        windowOne->addRootNode(std::make_shared<MultiWindowSceneOne>());
        registerWindow(windowOne);

        // Create window two
        windowConfiguration.setTitle("My second window");
        auto windowTwo = gfx::Window::create(windowConfiguration);
        windowTwo->addRootNode(std::make_shared<MultiWindowSceneTwo>());
        registerWindow(windowTwo);

        return true;
    }
};
REGISTER_APPLICATION("MultiWindowApp", MultiWindowApp);

#endif