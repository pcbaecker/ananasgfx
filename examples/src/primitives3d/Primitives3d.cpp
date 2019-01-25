#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/d3/Cube.hpp>

class Primitives3dScene : public gfx::Scene {
public:
    bool init() noexcept override {
        // Create cube
        this->pCube = createChild<d3::Cube>();
        this->pCube->setPosition(-10.0f, -10.0f, -10.0f);

        return gfx::Scene::init();
    }

    void update(float dt) noexcept override {
        Scene::update(dt);

        // Rotate the cube
        this->pCube->setRotation(this->pCube->getRotation().x + 1.0f * dt, this->pCube->getRotation().y + 1.0f * dt, 0.0f);
    }

private:
    d3::Cube* pCube = nullptr;
};

class Primitives3dApp : public gfx::Application {
public:
    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(640);
        windowConfiguration.setHeight(480);
        windowConfiguration.setTitle("My first window");
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<Primitives3dScene>());
        registerWindow(window);

        return true;
    }
};
REGISTER_APPLICATION("Primitives3d", Primitives3dApp);