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
        if (!this->mVisible) {
            return;
        }

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

    void Node::onTouchBegan(const Touch &touch) noexcept {
        for (auto& child : this->mChildren) {
            child->onTouchBegan(touch);
        }
    }

    void Node::onTouchMoved(const Touch &touch) noexcept {
        for (auto& child : this->mChildren) {
            child->onTouchMoved(touch);
        }
    }

    void Node::onTouchEnded(const Touch &touch) noexcept {
        for (auto& child : this->mChildren) {
            child->onTouchEnded(touch);
        }
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

    nodePriority_t Node::getPriority() const noexcept {
        return 0;
    }

    void Node::resortChildren() noexcept {
        this->mChildren.sort([](const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) {
            return lhs->getPriority() <= rhs->getPriority();
        });
    }

    bool NodeComparator::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const noexcept {
        return lhs->getPriority() <= rhs->getPriority();
    }

    void Node::setId(const std::string &id) noexcept {
        this->mId = id;
    }

    const std::string &Node::getId() const noexcept {
        return this->mId;
    }

    std::optional<Node *> Node::getChildWithId(const std::string &id) const noexcept {
        // Iterate through all children
        for (auto& child : this->mChildren) {
            if (child->getId() == id) {
                return child.get();
            }
        }

        // No child with given Id found
        return std::nullopt;
    }

    bool Node::isVisible() const noexcept {
        return this->mVisible;
    }

    void Node::setVisible(bool visible) noexcept {
        this->mVisible = visible;
    }
}