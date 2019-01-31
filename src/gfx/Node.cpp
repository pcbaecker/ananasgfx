#include <ananasgfx/gfx/Node.hpp>
#include <ananasgfx/gfx/Window.hpp>
#include <ee/Log.hpp>

namespace gfx {

    bool Node::init() noexcept {
        // Initialize all children
        auto it = this->mChildren.begin();
        while (it != this->mChildren.end()) {
            // Try to initialize child
            if (!(*it)->init()) {
                // Erase the child
                ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not init child", {});
                it = this->mChildren.erase(it);
            } else {
                it++;
            }
        }

        // This node is initialized from now on
        this->mInitialized = true;

        return true;
    }

    Window *Node::getWindow() noexcept {
        return this->pWindow;
    }

    void Node::setWindow(gfx::Window *pWindow) noexcept {
        this->pWindow = pWindow;
    }

    void Node::update(float dt) noexcept {
        for (auto& child : this->mChildren) {
            child->update(dt);
        }
    }

    void Node::draw() noexcept {
        for (auto& child : this->mChildren) {
            child->draw();
        }
    }

    bool Node::isInitialized() const noexcept {
        return this->mInitialized;
    }

    void Node::onChildAdded(Node *pNode) noexcept {
        // Can be overridden by inheriting classes
    }

    std::shared_ptr<RenderTexture> Node::asRenderTexture() noexcept {
        // Create a RenderTexture
        auto rendertexture = std::make_shared<gfx::RenderTexture>(
                this->pWindow, this->pWindow->getWidth(), this->pWindow->getHeight());

        // Begin drawing into the rendertexture
        rendertexture->begin();
        this->pWindow->getRenderer()->clearScreen();

        // Draw this node and all children
        this->draw();

        // Finish drawing
        rendertexture->end();

        return rendertexture;
    }
}