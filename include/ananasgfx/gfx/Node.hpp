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

    /**
     * @brief The base node class for everything that should be drawn.
     */
    class Node {
        friend class ClippingNode;
    public:
        /**
         * @brief Initializes this node
         *
         * @return True on success.
         */
        virtual bool init() noexcept;

        /**
         * @brief Updates this node
         *
         * @param dt The delta time since last update.
         */
        virtual void update(float dt) noexcept;

        /**
         * @brief Draws this node and its children into the current framebuffer.
         */
        virtual void draw() noexcept;

        /**
         * @brief Draws this node and its children into a rendertexture.
         *
         * @return Pointer to the created rendertexture.
         */
        virtual std::shared_ptr<RenderTexture> asRenderTexture() noexcept;

        /**
         * @brief Creates a new child.
         *
         * @tparam T The class of the new child.
         * @return Pointer to the newly created child.
         */
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

        /**
         * @brief Sets the id of this node.
         *
         * @param id The new id of this node.
         */
        void setId(const std::string& id) noexcept;

        /**
         * @brief Returns the id of this node.
         */
        const std::string& getId() const noexcept;

        /**
         * @brief Tries to find a child with the given id.
         *
         * @param id The id we search for.
         * @return Optional that can contain a pointer to the child node.
         */
        std::optional<Node*> getChildWithId(const std::string& id) const noexcept;

        /**
         * @brief Sets the window handle.
         *
         * @param pWindow Pointer to the window.
         */
        void setWindow(Window* pWindow) noexcept;

        /**
         * @brief Returns the window handle.
         *
         * @return Pointer to the window pointer.
         */
        Window* getWindow() noexcept;

        /**
         * @brief Returns true if this node is already initialized.
         *
         * @return True if this node is already initialized.
         */
        bool isInitialized() const noexcept;

        /**
         * @brief Returns the draw priority of this node.
         *
         * @return The draw priority of this node.
         */
        virtual nodePriority_t getPriority() const noexcept;

        /**
         * @brief Resorts all children by its priority.
         */
        void resortChildren() noexcept;

        /**
         * @brief Returns the parent of this node or nullptr if this is the root node.
         *
         * @return Returns the parent of this node.
         */
        Node* getParent() const noexcept;

        /**
         * @brief Returns true if this node is visible.
         *
         * @return True if this node is visible.
         */
        bool isVisible() const noexcept;

        /**
         * @brief Sets if this node should be visible or not.
         *
         * @param visible True if this node should be visible.
         */
        void setVisible(bool visible) noexcept;

    protected:
        /**
         * @brief This callback will be called everytime a new child is added.
         *
         * @param pNode Pointer to the new node.
         */
        virtual void onChildAdded(Node* pNode) noexcept;

        /**
         * @brief Called when a touch begins.
         *
         * @param touch The touch object.
         */
        virtual void onTouchBegan(const Touch& touch) noexcept;

        /**
         * @brief Called when a touch moved.
         *
         * @param touch The touch object.
         */
        virtual void onTouchMoved(const Touch& touch) noexcept;

        /**
         * @brief Called when a touch ended.
         *
         * @param touch The touch object.
         */
        virtual void onTouchEnded(const Touch& touch) noexcept;

    protected:
        /**
         * @brief The id of this object.
         */
        std::string mId;

        /**
         * @brief The window handle.
         */
        Window* pWindow = nullptr;

        /**
         * @brief List with all children.
         */
        std::list<std::shared_ptr<Node>> mChildren;

        /**
         * @brief True if this node is already initialized.
         */
        bool mInitialized = false;

        /**
         * @brief True if this node should be visible.
         */
        bool mVisible = true;

        /**
         * @brief Pointer to the parent node.
         */
        Node* pParent = nullptr;
    };
}

#endif