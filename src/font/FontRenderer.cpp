#include <ananasgfx/font/FontRenderer.hpp>

namespace font {

    bool validFollower(char c) noexcept {
        return (c & 0xC0) == 0x80;
    }

    std::vector<long> FontRenderer::convert(const std::string &string) noexcept {
        std::vector<long> vector;

        // Go through the string char for char
        for (int i = 0; i < string.length();) {
            // Check if this is a one byte character
            if ((string[i] & 0x80) == 0x00) {
                // Store the byte
                vector.emplace_back(static_cast<long>(string[i]));
                i += 1;
                continue;
            }

            // Check if this is a two bytes character
            if ((string[i] & 0xE0) == 0xC0) {
                // There must be at least one more byte remaining
                if (string.length() < i + 2) {
                    break;
                }

                // Check that the following byte is correct
                if (!validFollower(string[i+1])) {
                    // There seems to be something wrong, we skip one byte
                    i++;
                    continue;
                }

                // Store the two bytes
                vector.emplace_back(
                        ((string[i] & 0x1F) << 6) +
                        (string[i+1] & 0x3F));
                i += 2;
                continue;
            }

            // Check if this is a three bytes character
            if ((string[i] & 0xF0) == 0xE0) {
                // There must be at least 2 more bytes remaining
                if (string.length() < i + 3) {
                    break;
                }

                // Check that the following 2 bytes are correct
                if (!validFollower(string[i+1]) || !validFollower(string[i+2])) {
                    // There seems to be something wrong, we skip one byte
                    i++;
                    continue;
                }

                // Store the three bytes
                vector.emplace_back(
                        ((string[i] & 0x0F) << 12) +
                        ((string[i+1] & 0x3F) << 6) +
                        (string[i+2] & 0x3F));
                i += 3;
                continue;
            }

            // Check if this is a four bytes character
            if ((string[i] & 0xF8) == 0xF0) {
                // There must be at least 3 more bytes remaining
                if (string.length() < i + 4) {
                    break;
                }

                // Check that the following 3 bytes are correct
                if (!validFollower(string[i+1]) || !validFollower(string[i+2]) || !validFollower(string[i+3])) {
                    // There seems to be something wrong, we skip one byte
                    i++;
                    continue;
                }

                // Store the four bytes
                vector.emplace_back(
                        ((string[i] & 0x07) << 18) +
                        ((string[i+1] & 0x3F) << 12) +
                        ((string[i+2] & 0x3F) << 6) +
                        (string[i+3] & 0x3F));
                i += 4;
                continue;
            }

            // Invalid byte, skipping
            i++;
        }



        return vector;
    }

}