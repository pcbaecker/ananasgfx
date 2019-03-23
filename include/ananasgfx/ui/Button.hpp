#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <functional>

#include "Node.hpp"
#include "Touchable.hpp"

namespace ui {

    class Button : public Touchable, public Node {
    public:
        Button() noexcept;

        bool init() noexcept override;

        void setSize(float x, float y) noexcept override;

        void onTouchBegan(gfx::Touch &touch) noexcept override;
    protected:
    private:

    };
}

#endif