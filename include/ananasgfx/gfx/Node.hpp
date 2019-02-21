#ifndef GFX_NODE_H
#define GFX_NODE_H

#include <list>
#include <memory>

#include "RenderTexture.hpp"
#include "Touch.hpp"

namespace gfx {

    typedef int16_t nodePriority_t;

    class Window;
    class Node;

    struct NodeComparator {
        bool operator() (const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs) const noexcept;
    };

    class Node {
    public:
        virtual bool init() noexcept;
        virtual void update(float dt) noexcept;
        virtual void draw() noexcept;

        virtual std::shared_ptr<RenderTexture> asRenderTexture() noexcept;

        template<class T> T* createChild() noexcept {
            // Try to create an instance of the object
            auto object = std::make_shared<T>();

            // Provide a pointer to our window to every child
            object->setWindow(this->pWindow);

            // Provide a pointer to the parent
            object->pParent = this;

            // Try to cast it to the base node type and store it in the children list
            this->mChildren.push_back(std::dynamic_pointer_cast<Node>(object));
            this->resortChildren();

            // Call the on child added callback for inheriting classes
            onChildAdded(object.get());

            return object.get();
        }

        void setId(const std::string& id) noexcept;
        const std::string& getId() const noexcept;
        std::optional<Node*> getChildWithId(const std::string& id) const noexcept;

        void setWindow(Window* pWindow) noexcept;
        Window* getWindow() noexcept;

        bool isInitialized() const noexcept;

        virtual nodePriority_t getPriority() const noexcept;
        void resortChildren() noexcept;

        bool isVisible() const noexcept;
        void setVisible(bool visible) noexcept;

    protected:
        virtual void onChildAdded(Node* pNode) noexcept;
        virtual void onTouchBegan(const Touch& touch) noexcept;
        virtual void onTouchMoved(const Touch& touch) noexcept;
        virtual void onTouchEnded(const Touch& touch) noexcept;

    protected:
        std::string mId;
        Window* pWindow = nullptr;
        std::list<std::shared_ptr<Node>> mChildren;
        bool mInitialized = false;
        bool mVisible = true;
        Node* pParent = nullptr;
    };

}

#endif