#ifndef GFX_TOUCH_H
#define GFX_TOUCH_H

#include <cstdint>

namespace gfx {

    /**
     * @brief Holds information about a touch.
     */
    class Touch {
    public:
        /**
         * @brief Constructor.
         *
         * @param id The touch id.
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         */
        Touch(uint8_t id, double x, double y) noexcept;

        /**
         * @brief Returns the last x coordinate.
         *
         * @return The last X-Coordinate.
         */
        double getLastX() const noexcept;

        /**
         * @brief Returns the last y coordinate.
         *
         * @return The last Y-Coordinate.
         */
        double getLastY() const noexcept;

        /**
         * @brief Sets the last coordinates.
         *
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         */
        void setLast(double x, double y) noexcept;

    private:
        /**
         * @brief The start x coordinate.
         */
        double mStartX = 0.0f;

        /**
         * @brief The start y coordinate.
         */
        double mStartY = 0.0f;

        /**
         * @brief The last x coordinate.
         */
        double mLastX = 0.0f;

        /**
         * @brief The last y coordinate.
         */
        double mLastY = 0.0f;

        /**
         * @brief The touch id.
         */
        uint8_t mId = 0;
    };
}

#endif