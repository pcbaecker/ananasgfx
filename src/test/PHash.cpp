#include <ananasgfx/test/PHash.hpp>
#include <ee/Log.hpp>
#include <cmath>
#include <glm/ext/scalar_constants.hpp>

namespace test {

    uint64_t PHash::hash(const gfx::Bitmap &bitmap) noexcept {
        // Reduce size
        auto resizedBitmap = bitmap.resize(32,32);
        if (!resizedBitmap.has_value()) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "Could not resize size of bitmap", {
                ee::Note("Bitmap width", bitmap.getWidth()),
                ee::Note("Bitmap height", bitmap.getHeight()),
                ee::Note("Bitmap channels", bitmap.getChannels())
            });
            return 0;
        }

        // Reduce color
        auto grayscaleBitmap = resizedBitmap->get()->asGrayscale();
        if (grayscaleBitmap->getChannels() != 1
        || grayscaleBitmap->getWidth() != 32
        || grayscaleBitmap->getHeight() != 32) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "The bitmap must be a grayscale and 32x32", {
                    ee::Note("GS Bitmap width", grayscaleBitmap->getWidth()),
                    ee::Note("GS Bitmap height", grayscaleBitmap->getHeight()),
                    ee::Note("GS Bitmap channels", grayscaleBitmap->getChannels())
            });
            return 0;
        }

        // Convert uint8_t to double
        std::vector<double> grayvalues(32*32);
        auto* pData = static_cast<const uint8_t*>(grayscaleBitmap->getData());
        for (int i = 0; i < 32*32; i++) {
            grayvalues[i] = static_cast<double>(pData[i]);
        }

        // Perform dct
        auto freq32 = _dct(grayvalues);

        // Pick the top-left 8x8 matrix
        std::vector<double> freq8(8*8);
        for (uint8_t x = 0; x < 8; x++) {
            for (uint8_t y = 0; y < 8; y++) {
                int offset32 = 32*y+x;
                int offset8 = 8*y+x;
                freq8[offset8] = freq32[offset32];
            }
        }

        // Compute the average (skipping the first term)
        double mean = 0.0;
        for (int i = 1; i < 8*8; i++) {
            mean += freq8[i];
        }
        mean = mean / (8*8-1);

        // Set the bits by comparing each element to the mean
        return _compareToThreshold(freq8, mean);
    }

    std::vector<double> PHash::_dct(const std::vector<double> &input) noexcept {
        std::vector<double> result;
        size_t len = input.size();
        result.reserve(len);
        double factor = glm::pi<double>() / len;
        for (size_t i = 0; i < len; i++) {
            double sum = 0;
            for (size_t j = 0; j < len; j++)
                sum += input.at(j) * std::cos((j + 0.5) * i * factor);
            result.push_back(sum);
        }
        return result;
    }

    uint64_t PHash::_compareToThreshold(const std::vector<double> &input, double threshold) noexcept {
        // Check vector size
        if (input.size() != 64) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "The given input vector has not 64 elements", {
                ee::Note("Vector size", input.size())
            });
            return 0;
        }

        // Iterate through every element and compare it to the threshold
        uint64_t result = 0;
        for (int i = 0; i < 64; i++) {
            if (input[i] >= threshold) {
                result |= 1UL << i;
            }
        }

        return result;
    }

    std::string PHash::toString(uint64_t hash) noexcept {
        std::string str;
        for (int i = 0; i < 64; i++) {
            if (hash & (1 << i)) {
                str += "1";
            } else {
                str += "0";
            }
        }
        return str;
    }

    uint8_t PHash::distance(uint64_t a, uint64_t b) noexcept {
        // Get the difference between the hashes
        uint64_t diff = a ^b;

        // Count the different bits
        uint8_t count = 0;
        while (diff) {
            count += diff & 1;
            diff >>= 1;
        }
        return count;
    }
}