#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <functional>

#include "Node.hpp"

namespace d2 {
    class Node;
}

namespace ui {

    class Button : public Node {
    public:
        Button() noexcept;

        bool init() noexcept override;

        void setSize(float x, float y) noexcept override;

        void onTouchBegan(float x, float y, const gfx::Touch &touch) noexcept override;

        void onTouchEnded(float x, float y, const gfx::Touch &touch) noexcept override;

        void setCallback(std::function<void(Button*)> callback) noexcept;
        const std::function<void(Button*)>& getCallback() const noexcept;

    protected:
        virtual void onFocus() noexcept;
        virtual void onBlur() noexcept;

        virtual std::optional<d2::Node*> getBlurBackground() noexcept = 0;

        virtual std::optional<d2::Node*> getFocusBackground() noexcept = 0;

    private:
        std::optional<d2::Node*> mBlurBackground;
        std::optional<d2::Node*> mFocusBackground;
        std::function<void(Button*)> mCallback;
        std::optional<const gfx::Touch*> mActiveTouch;
    };
}

#endif