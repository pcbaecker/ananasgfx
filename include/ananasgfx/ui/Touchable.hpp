#ifndef UI_TOUCHABLE_H
#define UI_TOUCHABLE_H

#include <functional>
#include <optional>
#include <glm/glm.hpp>

namespace d2 {
    class Node;
}

namespace ui {

    class Touchable {
    public:

        void setCallback(std::function<void()> callback) noexcept;

        const std::function<void()>& getCallback() const noexcept;

    protected:
        virtual void onFocus() noexcept;

        virtual void onBlur() noexcept;

        virtual std::optional<d2::Node*> getBackgroundBlur() noexcept = 0;

        virtual std::optional<d2::Node*> getBackgroundFocus() noexcept = 0;

        bool _init(const glm::vec2& size) noexcept;

        void _setSize(float x, float y) noexcept;

        void touchBegins() noexcept;

        void touchEnds(bool success) noexcept;

    private:
        std::optional<d2::Node*> mBlurBackground;
        std::optional<d2::Node*> mFocusBackground;
        std::function<void()> mCallback;
        bool mTouchActive = false;
    };

}

#endif