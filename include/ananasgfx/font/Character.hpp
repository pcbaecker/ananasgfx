#ifndef FONT_CHARACTER_H
#define FONT_CHARACTER_H

#include <memory>
#include <ananasgfx/gfx/Bitmap.hpp>

namespace font {

    /**
     * @brief Represents a single character in a font.
     */
    class Character {
    public:
        /**
         * @brief Constructor.
         *
         * @param charCode The unicode charcode.
         * @param advanceX The x-advance coordinate.
         * @param underBaseline The distance under the baseline.
         * @param overBaseline The distance over the baseline.
         * @param bitmap The bitmap of the character.
         */
        Character(long charCode,
                  float advanceX,
                  float underBaseline,
                  float overBaseline,
                  std::shared_ptr<gfx::Bitmap> bitmap) noexcept;

        /**
         * @brief Returns a reference to the bitmap.
         *
         * @return Reference to the bitmap.
         */
        const gfx::Bitmap& getBitmap() const noexcept;

        /**
         * @brief Returns the char code.
         *
         * @return The char code.
         */
        long getCharCode() const noexcept;

        /**
         * @brief Returns the advance x offset.
         *
         * @return The advance x offset.
         */
        float getAdvanceX() const noexcept;

        /**
         * @brief Returns the under baseline offset.
         *
         * @return The under baseline offset.
         */
        float getUnderBaseline() const noexcept;

        /**
         * @brief Returns the over baseline offset.
         *
         * @return The over baseline offset.
         */
        float getOverBaseline() const noexcept;

    private:
        /**
         * @brief The char code.
         */
        long mCharCode;

        /**
         * @brief The advance x offset.
         */
        float mAdvanceX;

        /**
         * @brief The under baseline offset.
         */
        float mUnderBaseline;

        /**
         * @brief The over baseline offset.
         */
        float mOverBaseline;

        /**
         * @brief The bitmap.
         */
        std::shared_ptr<gfx::Bitmap> mBitmap;
    };

}

#endif