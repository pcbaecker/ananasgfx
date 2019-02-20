#include <ananasgfx/gfx/Touch.hpp>

namespace gfx {

    Touch::Touch(uint8_t id, double x, double y) noexcept : mId(id), mStartX(x), mStartY(y) {

    }

    double Touch::getLastX() const noexcept {
        return this->mLastX;
    }

    double Touch::getLastY() const noexcept {
        return this->mLastY;
    }

    void Touch::setLast(double x, double y) noexcept {
        this->mLastX = x;
        this->mLastY = y;
    }

}