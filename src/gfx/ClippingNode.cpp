#include <ananasgfx/gfx/Window.hpp>
#include <ananasgfx/gfx/ClippingNode.hpp>

namespace gfx {

    bool ClippingNode::init() noexcept {
        // Initialize all stencils
        auto it = this->mStencilNodes.begin();
        while (it != this->mStencilNodes.end()) {
            // Try to initialize stencil
            if (!(*it)->init()) {
                // Erase the stencil
                std::cerr << __PRETTY_FUNCTION__ << ": Unable to initialize stencil" << std::endl;
                it = this->mStencilNodes.erase(it);
            } else {
                it++;
            }
        }

        return Node::init();
    }

    void ClippingNode::draw() noexcept {
        // Start the stencil buffer filling
        this->pWindow->getRenderer()->beginStencilBufferFilling();

        // Draw our stencil nodes (write ones into the stencil buffer)
        for (auto& stencil : this->mStencilNodes) {
            stencil->draw();
        }

        // End writing into the stencil buffer
        this->pWindow->getRenderer()->endStencilBufferFilling();

        // Now activate the stencil buffer
        // Using the stencil buffer will limit drawing to the defined area (where the stencil is drawed or opposite)
        this->pWindow->getRenderer()->activateStencilBuffer(this->mDrawWhereStencil);

        // The normal draw() is now limited to the stencil area
        Node::draw();

        // Finish with using the stencil buffer
        this->pWindow->getRenderer()->deactivateStencilBuffer();
    }
}