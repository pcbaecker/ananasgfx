#ifndef UI_TOUCHABLE_H
#define UI_TOUCHABLE_H

#include <ananasgfx/d2/Node.hpp>

namespace ui {

    class Touchable {
    public:

        void setCallback(std::function<void()> callback) noexcept {
            this->mCallback = std::move(callback);
        }

        const std::function<void()>& getCallback() const noexcept {
            return this->mCallback;
        }

    protected:
        virtual void onFocus() noexcept {
            if (this->mFocusBackground.has_value()) {
                (*this->mFocusBackground)->setVisible(true);
            }
            if (this->mBlurBackground.has_value()) {
                (*this->mBlurBackground)->setVisible(false);
            }
        }

        virtual void onBlur() noexcept {
            if (this->mFocusBackground.has_value()) {
                (*this->mFocusBackground)->setVisible(false);
            }
            if (this->mBlurBackground.has_value()) {
                (*this->mBlurBackground)->setVisible(true);
            }
        }

        virtual std::optional<d2::Node*> getBackgroundBlur() noexcept = 0;

        virtual std::optional<d2::Node*> getBackgroundFocus() noexcept = 0;

        bool _init(const glm::vec2& size) noexcept {
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

        void _setSize(float x, float y) noexcept {
            if (this->mBlurBackground.has_value()) {
                (*this->mBlurBackground)->setSize(x,y);
            }
            if (this->mFocusBackground.has_value()) {
                (*this->mFocusBackground)->setSize(x,y);
            }
        }

        void touchBegins(const gfx::Touch& touch) noexcept {
            if (!this->mActiveTouch.has_value()) {
                this->mActiveTouch = &touch;
                this->onFocus();
            }
        }

        void touchEnds() noexcept {
            if (this->mActiveTouch.has_value()) {
                if (this->mCallback) {
                    //this->mCallback(this);
                }
                this->mActiveTouch.reset();
                this->onBlur();
            }
        }

    private:
        std::optional<d2::Node*> mBlurBackground;
        std::optional<d2::Node*> mFocusBackground;
        std::function<void()> mCallback;
        std::optional<const gfx::Touch*> mActiveTouch;
    };

}

#endif