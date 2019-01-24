#ifndef GFX_WINDOWCONFIGURATION_H
#define GFX_WINDOWCONFIGURATION_H

#include <string>

namespace gfx {

    class WindowConfiguration {
    public:
        void setTitle(std::string title) noexcept;
        const std::string& getTitle() const noexcept;

        void setWidth(int width) noexcept;
        int getWidth() const noexcept;

        void setHeight(int height) noexcept;
        int getHeight() const noexcept;

        void setFullscreen(bool fullscreen) noexcept;
        bool fullscreen() const noexcept;

        void setHideCursor(bool hideCursor) noexcept;
        bool hideCursor() const noexcept;

    private:
        std::string mTitle;
        int mWidth = 0;
        int mHeight = 0;
        bool mFullscreen = false;
        bool mHideCursor = false;
    };

}

#endif