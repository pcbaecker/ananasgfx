#include <ananasgfx/ui/Touchable.hpp>
#include <ananasgfx/d2/Node.hpp>

namespace ui {

    void Touchable::setCallback(std::function<void()> callback) noexcept {
        this->mCallback = std::move(callback);
    }

    const std::function<void()>& Touchable::getCallback() const noexcept {
        return this->mCallback;
    }

    void Touchable::onFocus() noexcept {
        if (this->mFocusBackground.has_value()) {
            (*this->mFocusBackground)->setVisible(true);
        }
        if (this->mBlurBackground.has_value()) {
            (*this->mBlurBackground)->setVisible(false);
        }
    }

    void Touchable::onBlur() noexcept {
        if (this->mFocusBackground.has_value()) {
            (*this->mFocusBackground)->setVisible(false);
        }
        if (this->mBlurBackground.has_value()) {
            (*this->mBlurBackground)->setVisible(true);
        }
    }

    bool Touchable::_init(const glm::vec2& size) noexcept {
        this->mBlurBackground = getBackgroundBlur();
        this->mFocusBackground = getBackgroundFocus();

        if (this->mBlurBackground.has_value()) {
            (*this->mBlurBackground)->setSize(size);
        }
        if (this->mFocusBackground.has_value()) {
            (*this->mFocusBackground)->setSize(size);
            (*this->mFocusBackground)->setVisible(false);
        }
        return true;
    }

    void Touchable::_setSize(float x, float y) noexcept {
        if (this->mBlurBackground.has_value()) {
            (*this->mBlurBackground)->setSize(x,y);
        }
        if (this->mFocusBackground.has_value()) {
            (*this->mFocusBackground)->setSize(x,y);
        }
    }

    void Touchable::touchBegins() noexcept {
        if (!this->mTouchActive) {
            this->mTouchActive = true;
            this->onFocus();
        }
    }

    void Touchable::touchEnds(bool success) noexcept {
        if (this->mTouchActive) {
            if (success && this->mCallback) {
                this->mCallback();
            }
            this->mTouchActive = false;
            this->onBlur();
        }
    }

}