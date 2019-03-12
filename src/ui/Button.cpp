#include <ananasgfx/ui/Button.hpp>
#include <ananasgfx/d2/Rectangle.hpp>

namespace ui {

    Button::Button() noexcept {
        this->mMinSize = vec2(16,16);
    }

    void Button::setSize(float x, float y) noexcept {
        if (this->mBlurBackground.has_value()) {
            (*this->mBlurBackground)->setSize(x,y);
        }
        if (this->mFocusBackground.has_value()) {
            (*this->mFocusBackground)->setSize(x,y);
        }
        Node::setSize(x, y);
    }

    bool Button::init() noexcept {
        this->mBlurBackground = getBlurBackground();
        this->mFocusBackground = getFocusBackground();

        if (this->mBlurBackground.has_value()) {
            (*this->mBlurBackground)->setSize(this->mSize);
        }
        if (this->mFocusBackground.has_value()) {
            (*this->mFocusBackground)->setSize(this->mSize);
            (*this->mFocusBackground)->setVisible(false);
        }
        return Node::init();
    }

    void Button::onTouchBegan(const float x, const float y, const gfx::Touch &touch) noexcept {
        if (!this->mActiveTouch.has_value()) {
            this->mActiveTouch = &touch;
            this->onFocus();
        }
    }

    void Button::onTouchEnded(const float x, const float y, const gfx::Touch &touch) noexcept {
        if (this->mActiveTouch.has_value()) {
            if (this->mCallback) {
                this->mCallback(this);
            }
            this->mActiveTouch.reset();
            this->onBlur();
        }
    }

    void Button::setCallback(std::function<void(Button *)> callback) noexcept {
        this->mCallback = std::move(callback);
    }

    const std::function<void(Button *)> &Button::getCallback() const noexcept {
        return this->mCallback;
    }

    void Button::onFocus() noexcept {
        if (this->mFocusBackground.has_value()) {
            (*this->mFocusBackground)->setVisible(true);
        }
        if (this->mBlurBackground.has_value()) {
            (*this->mBlurBackground)->setVisible(false);
        }
    }

    void Button::onBlur() noexcept {
        if (this->mFocusBackground.has_value()) {
            (*this->mFocusBackground)->setVisible(false);
        }
        if (this->mBlurBackground.has_value()) {
            (*this->mBlurBackground)->setVisible(true);
        }
    }
}