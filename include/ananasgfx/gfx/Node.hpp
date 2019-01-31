#ifndef GFX_NODE_H
#define GFX_NODE_H

#include <list>
#include <memory>

#include "RenderTexture.hpp"

namespace gfx {

    class Window;

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

            // Try to cast it to the base node type and store it in the children list
            this->mChildren.push_back(std::dynamic_pointer_cast<Node>(object));

            // Call the on child added callback for inheriting classes
            onChildAdded(object.get());

            return object.get();
        }

        void setWindow(Window* pWindow) noexcept;
        Window* getWindow() noexcept;

        bool isInitialized() const noexcept;

    protected:
        virtual void onChildAdded(Node* pNode) noexcept;

    protected:
        Window* pWindow = nullptr;
        std::list<std::shared_ptr<Node>> mChildren;
        bool mInitialized = false;
    };

}

#endif