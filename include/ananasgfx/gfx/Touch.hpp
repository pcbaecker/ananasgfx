#ifndef GFX_TOUCH_H
#define GFX_TOUCH_H

#include <cstdint>

namespace gfx {

    class Touch {
    public:
        Touch(uint8_t id, double x, double y) noexcept;

        double getLastX() const noexcept;
        double getLastY() const noexcept;
        void setLast(double x, double y) noexcept;

    private:
        double mStartX = 0.0f;
        double mStartY = 0.0f;
        double mLastX = 0.0f;
        double mLastY = 0.0f;
        uint8_t mId = 0;
    };

}

#endif