#include <ananasgfx/font/Character.hpp>

namespace font {

    Character::Character(
            long charCode,
            float advanceX,
            float underBaseline,
            float overBaseline,
            std::shared_ptr<gfx::Bitmap> bitmap) noexcept :
            mCharCode(charCode), mAdvanceX(advanceX), mUnderBaseline(underBaseline), mOverBaseline(overBaseline), mBitmap(std::move(bitmap)) {

    }

    const gfx::Bitmap &Character::getBitmap() const noexcept {
        return *this->mBitmap;
    }

    long Character::getCharCode() const noexcept {
        return this->mCharCode;
    }

    float Character::getAdvanceX() const noexcept {
        return this->mAdvanceX;
    }

    float Character::getUnderBaseline() const noexcept {
        return this->mUnderBaseline;
    }

    float Character::getOverBaseline() const noexcept {
        return this->mOverBaseline;
    }

}