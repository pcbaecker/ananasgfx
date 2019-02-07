#include <ananasgfx/font/FontRenderer.hpp>

#include <iostream>
#include <list>

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

    std::shared_ptr<gfx::Bitmap> FontRenderer::render(
            const std::string &text,
            Font *font,
            font::size_t fontSize,
            const glm::vec2 &maxSize) noexcept {
        // Convert the given text into unicode characters
        auto characters = convert(text);

        // Get the constraints
        float maxOverBaseline = 0.0f, maxUnderBaseline = 0.0f, width = 0.0f;
        std::vector<Character*> charmap;
        for (auto& code : characters) {
            auto opt = font->getCharacter(code, fontSize);
            if (opt.has_value()) {
                auto c = *opt;
                if (maxOverBaseline < c->getOverBaseline())
                    maxOverBaseline = c->getOverBaseline();
                if (maxUnderBaseline < c->getUnderBaseline())
                    maxUnderBaseline = c->getUnderBaseline();
                width += c->getAdvanceX();
                charmap.push_back(c);
            }
        }

        // Calculate the bitmap constraints
        float height = maxOverBaseline + maxUnderBaseline;
        if (width > maxSize.x) {
            width = maxSize.x;
        }
        if (height > maxSize.y) {
            height = maxSize.y;
        }

        // Create bitmap
        auto w = static_cast<size_t>(width);
        auto h = static_cast<size_t>(height);
        auto bitmap = std::make_shared<gfx::Bitmap>(malloc(w*h), w, h, 1);
        bitmap->clear();

        // Write the characters into the bitmap
        size_t t = 0;
        for (auto& c : charmap) {
            auto data = static_cast<const uint8_t*>(c->getBitmap().getData());

            size_t j = 0;
            for (int y = 0; y < c->getBitmap().getHeight(); y++) {
                for (int x = 0; x < c->getBitmap().getWidth(); x++) {
                    if (data[j]) {
                        bitmap->setPixel(t + x, y + (maxOverBaseline - c->getOverBaseline()), data[j]);
                    }
                    j++;
                }
            }

            t += c->getAdvanceX();
        }

        return bitmap;
    }

    void FontRenderer::render(
            const std::string &text, Font *font,
            font::size_t fontSize,
            gfx::Bitmap &bitmap,
            gfx::HorizontalAlign horizontalAlign,
            gfx::VerticalAlign verticalAlign) noexcept {
        // Convert the given text into unicode characters
        auto characters = convert(text);

        // Get the constraints
        float maxOverBaseline = 0.0f, maxUnderBaseline = 0.0f, width = 0.0f;
        std::list<Character*> charmap;
        for (auto& code : characters) {
            auto opt = font->getCharacter(code, fontSize);
            if (opt.has_value()) {
                auto c = *opt;
                if (maxOverBaseline < c->getOverBaseline())
                    maxOverBaseline = c->getOverBaseline();
                if (maxUnderBaseline < c->getUnderBaseline())
                    maxUnderBaseline = c->getUnderBaseline();
                width += c->getAdvanceX();
                charmap.push_back(c);
            }
        }

        // Calculate the bitmap constraints
        float height = maxOverBaseline + maxUnderBaseline;
        if (height > bitmap.getHeight()) {
            height = bitmap.getHeight();
        }

        // Set start points
        float startX = 0.0f;
        float startY = 0.0f;
        switch (verticalAlign) {
            case gfx::Top:
                startY = 0.0f;
                break;
            case gfx::Middle:
                startY = bitmap.getHeight()*0.5f - height*0.5f;
                break;
            case gfx::Bottom:
                startY = bitmap.getHeight() - height;
                break;
        }
        switch (horizontalAlign) {
            case gfx::Left:
                startX = 0.0f;
                break;
            case gfx::Center:
                startX = bitmap.getWidth()*0.5f - width*0.5f;
                break;
            case gfx::Right:
                startX = bitmap.getWidth() - width;
                break;
        }

        for (auto& c : charmap) {
            auto data = static_cast<const uint8_t*>(c->getBitmap().getData());

            size_t j = 0;
            for (int y = 0; y < c->getBitmap().getHeight(); y++) {
                for (int x = 0; x < c->getBitmap().getWidth(); x++) {
                    if (data[j]) {
                        float t = startX + x;
                        bitmap.setPixel(startX + x, y + startY + (maxOverBaseline - c->getOverBaseline()), data[j]);
                    }
                    j++;
                }
            }
            startX += c->getAdvanceX();
        }
    }

}