#ifndef GFX_CLIPPINGNODE_H
#define GFX_CLIPPINGNODE_H

#include "Node.hpp"

namespace gfx {

    /**
     * @brief Makes it possible to clip out some areas of the screen.
     */
    class ClippingNode : public gfx::Node {
    public:
        /**
         * @brief Creates a stencil child node.
         *
         * @tparam T The type of the stencil node.
         * @return Pointer to the stencil node.
         */
        template<class T> T* createStencil() noexcept {
            // Try to create an instance of the object
            auto object = std::make_shared<T>();

            // Provide a pointer to our window to every child
            object->setWindow(this->pWindow);

            // Provide a pointer to the parent
            object->pParent = this;

            // Try to cast it to the base node type and store it in the stencil nodes list
            this->mStencilNodes.push_back(std::dynamic_pointer_cast<Node>(object));

            // Return a pointer to the created stencil
            return object.get();
        }

        /**
         * @brief Initializes the node.
         *
         * @return True on success.
         */
        bool init() noexcept override;

        /**
         * @brief Draws the clipping node.
         */
        void draw() noexcept override;

    private:
        /**
         * @brief Defines whether to draw content where the stencil is defined or other way round.
         */
        bool mDrawWhereStencil = true;

        /**
         * @brief Holds all stencil nodes.
         *
         * We can not store them in the children list,
         * because the have to be called at a different time during draw() command.
         */
        std::list<std::shared_ptr<Node>> mStencilNodes;
    };

}

#endif