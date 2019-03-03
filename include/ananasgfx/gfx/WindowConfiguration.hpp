#ifndef GFX_WINDOWCONFIGURATION_H
#define GFX_WINDOWCONFIGURATION_H

#include <string>

namespace gfx {

    /**
     * @brief Holds the window configuration.
     */
    class WindowConfiguration {
    public:
        /**
         * @brief Sets the title of a window.
         */
        void setTitle(std::string title) noexcept;

        /**
         * @brief Returns the title of a window.
         *
         * @return The title of a window.
         */
        const std::string& getTitle() const noexcept;

        /**
         * @brief Sets the width of a window.
         *
         * @param width The width of a window.
         */
        void setWidth(int width) noexcept;

        /**
         * @brief Returns the width of a window.
         *
         * @return The width of a window.
         */
        int getWidth() const noexcept;

        /**
         * @brief Sets the height of a window.
         *
         * @param height The height of a window.
         */
        void setHeight(int height) noexcept;

        /**
         * @brief Returns the height of a window.
         *
         * @return The height of a window.
         */
        int getHeight() const noexcept;

        /**
         * @brief Sets the window to fullscreen.
         *
         * @param fullscreen True for fullscreen.
         */
        void setFullscreen(bool fullscreen) noexcept;

        /**
         * @brief Returns true if we want fullscreen.
         *
         * @return True for fullscreen.
         */
        bool fullscreen() const noexcept;

        /**
         * @brief True means we want to hide the cursor.
         *
         * @param hideCursor True means we want to hide the cursor.
         */
        void setHideCursor(bool hideCursor) noexcept;

        /**
         * @brief True means we want to hide the cursor.
         *
         * @return True means we want to hide the cursor.
         */
        bool hideCursor() const noexcept;

    private:
        /**
         * @brief The window title.
         */
        std::string mTitle;

        /**
         * @brief The window width.
         */
        int mWidth = 0;

        /**
         * @brief The window height.
         */
        int mHeight = 0;

        /**
         * @brief True for fullscreen.
         */
        bool mFullscreen = false;

        /**
         * @brief True if we want to hide cursor.
         */
        bool mHideCursor = false;
    };

}

#endif