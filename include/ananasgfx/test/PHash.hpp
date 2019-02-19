#ifndef TEST_PHASH_H
#define TEST_PHASH_H

#include <vector>
#include <ananasgfx/gfx/Bitmap.hpp>

namespace test {

    typedef uint64_t phash_t;

    class PHash {
    public:
        /**
         * @brief Calculates the phash for the given bitmap.
         *
         * Algorithm is implemented like described here:
         * http://hackerfactor.com/blog/index.php%3F/archives/432-Looks-Like-It.html
         * @param bitmap The bitmap to calculate the phash for.
         * @return The calculated phash.
         */
        static phash_t hash(const gfx::Bitmap& bitmap) noexcept;

        /**
         * @brief Calculates the dct for the given values.
         *
         * See:
         * https://en.wikipedia.org/wiki/Discrete_cosine_transform#DCT-II
         * @param vec The vector with the source values.
         * @return The vector with the output values.
         */
        static std::vector<double> _dct(const std::vector<double> &input) noexcept;

        /**
         * @brief Compares the given vector to the given threshold.
         *
         * Is the element above the threshold we set the appropriate bit of the result to 1, otherwise to 0.
         * @param input The vector containing the elements to compare.
         * @param threshold The threshold to compare with each element.
         * @return The result that contains a bit for every element.
         */
        static phash_t _compareToThreshold(const std::vector<double> &input, double threshold) noexcept;

        /**
         * @brief Converts the given integer to a human readable string representation of bits.
         *
         * @param hash The given has to display.
         * @return A human readable string representation.
         */
        static std::string toString(phash_t hash) noexcept;

        /**
         * @brief Calculates the distance between the two given hashes.
         *
         * @param a The hash number one.
         * @param b The hash number two.
         * @return The number of bits that are different.
         */
        static uint8_t distance(phash_t a, phash_t b) noexcept;
    };

}

#endif