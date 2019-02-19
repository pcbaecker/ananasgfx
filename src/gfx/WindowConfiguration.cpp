#include <ananasgfx/gfx/WindowConfiguration.hpp>

namespace gfx {

    void WindowConfiguration::setTitle(std::string title) noexcept {
        this->mTitle = std::move(title);
    }

    const std::string &WindowConfiguration::getTitle() const noexcept {
        return this->mTitle;
    }

    void WindowConfiguration::setWidth(int width) noexcept {
        this->mWidth = width;
    }

    int WindowConfiguration::getWidth() const noexcept {
        return this->mWidth;
    }

    void WindowConfiguration::setHeight(int height) noexcept {
        this->mHeight = height;
    }

    int WindowConfiguration::getHeight() const noexcept {
        return this->mHeight;
    }

    void WindowConfiguration::setFullscreen(bool fullscreen) noexcept {
        this->mFullscreen = fullscreen;
    }

    bool WindowConfiguration::fullscreen() const noexcept {
        return this->mFullscreen;
    }

    void WindowConfiguration::setHideCursor(bool hideCursor) noexcept {
        this->mHideCursor = hideCursor;
    }

    bool WindowConfiguration::hideCursor() const noexcept {
        return this->mHideCursor;
    }

}