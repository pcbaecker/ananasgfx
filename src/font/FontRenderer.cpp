#include <ananasgfx/font/FontRenderer.hpp>

#include <iostream>
#include <list>
#include <ee/Log.hpp>

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

    std::unique_ptr<gfx::Bitmap> FontRenderer::render(
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
        auto bitmap = std::make_unique<gfx::Bitmap>(malloc(w*h), w, h, 1);
        bitmap->clear();

        // Write the characters into the bitmap
        size_t t = 0;
        for (auto& c : charmap) {
            auto data = static_cast<const uint8_t*>(c->getBitmap().getData());

            size_t j = 0;
            for (int y = 0; y < c->getBitmap().getHeight(); y++) {
                for (int x = 0; x < c->getBitmap().getWidth(); x++) {
                    if (data[j]) {
                        bitmap->setPixel(static_cast<uint16_t>(t + x), static_cast<uint16_t>(y + (maxOverBaseline - c->getOverBaseline())), data[j]);
                    }
                    j++;
                }
            }

            t += static_cast<size_t>(c->getAdvanceX());
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
        float startY = 0.0f;
        float startX = 0.0f;
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
                        //float t = startX + x;
                        bitmap.setPixel(static_cast<uint16_t>(startX + x), static_cast<uint16_t>(y + startY + (maxOverBaseline - c->getOverBaseline())), data[j]);
                    }
                    j++;
                }
            }
            startX += c->getAdvanceX();
        }
    }

    std::list<Character *> FontRenderer::getCharacters(const std::string &text) noexcept {
        if (!this->mFont.has_value()) {
            WARN("A font must be present", {});
            return {};
        }
        auto font = *this->mFont;

        // Convert the given text into unicode characters
        auto codes = convert(text);

        // Get the characters for each code
        std::list<Character*> characters;
        for (auto& code : codes) {
            auto opt = font->getCharacter(code, this->mFontSize);
            if (opt.has_value()) {
                characters.push_back(*opt);
            }
        }

        return characters;
    }

    float FontRenderer::getHeight(const std::string &text, float width) noexcept {
        if (this->mMultiline) {
            auto rows = getRows(getCharacters(text), width);
            return rows.size() * this->mFontSize * 1.5f;
        } else {
            Chunk chunk;
            chunk.characters = getCharacters(text);
            setConstraints(chunk);
            return chunk.height;
        }
    }

    float FontRenderer::getWidth(const std::string &text, float height) noexcept {
        Chunk chunk;
        chunk.characters = getCharacters(text);
        setConstraints(chunk);
        return chunk.width;
    }

    void FontRenderer::render(const std::string &text, gfx::Bitmap &bitmap) noexcept {
        if (this->mMultiline) {
            auto rows = getRows(getCharacters(text), bitmap.getWidth());

            // Set start points
            const float lineHeight = this->mFontSize * 1.5f;
            float startY = 0.0f;
            switch (this->mVerticalAlign) {
                case gfx::Top:
                    startY = 0.0f;
                    break;
                case gfx::Middle:
                    startY = bitmap.getHeight()*0.5f - (rows.size() * lineHeight) * 0.5f;
                    break;
                case gfx::Bottom:
                    startY = bitmap.getHeight() - rows.size() * lineHeight;
                    break;
            }
            for (auto& row : rows) {
                row.width = 0.0f;
                setConstraints(row);

                render(row, startY, bitmap);

                startY += lineHeight;
            }

        } else {
            Chunk chunk;
            chunk.characters = getCharacters(text);

            setConstraints(chunk);

            // Set start points
            float startY = 0.0f;
            switch (this->mVerticalAlign) {
                case gfx::Top:
                    startY = 0.0f;
                    break;
                case gfx::Middle:
                    startY = bitmap.getHeight()*0.5f - chunk.height*0.5f;
                    break;
                case gfx::Bottom:
                    startY = bitmap.getHeight() - chunk.height;
                    break;
            }

            render(chunk, startY, bitmap);
        }
    }

    void FontRenderer::setConstraints(Chunk& chunk) noexcept {
        // Iterate through all characters
        for (auto& c : chunk.characters) {
            if (chunk.maxOverBaseline < c->getOverBaseline())
                chunk.maxOverBaseline = c->getOverBaseline();
            if (chunk.maxUnderBaseline < c->getUnderBaseline())
                chunk.maxUnderBaseline = c->getUnderBaseline();
            chunk.width += c->getAdvanceX();
        }

        // Calculate the height
        chunk.height = chunk.maxOverBaseline + chunk.maxUnderBaseline;
    }

    std::list<FontRenderer::Chunk> FontRenderer::getRows(const std::list<Character*>& characters, float width) noexcept {
        std::list<Chunk> rows;
        auto* row = &rows.emplace_back();
        Character* whitespace = nullptr;

        float wordWidth = 0.0f;
        std::list<Character*> wordCharacters;
        for (auto& c : characters) {

            if (c->getCharCode() == ' ') {
                whitespace = c;
                // A word finished

                // Check if the word fits into this row
                if (row->width + c->getAdvanceX() + wordWidth <= width) {// TODO whitespace width will always be added here, but sometimes this is wrong
                    // The word fits into this row -> add it
                    row->width += c->getAdvanceX() + wordWidth;
                    if (!row->characters.empty()) {
                        row->characters.push_back(c);
                    }
                    row->characters.insert(row->characters.end(), wordCharacters.begin(), wordCharacters.end());
                } else {
                    // The word does NOT fit into this row -> start a new row
                    row = &rows.emplace_back();

                    // Add the word into the new row
                    row->width += wordWidth;
                    row->characters.insert(row->characters.end(), wordCharacters.begin(), wordCharacters.end());
                }

                // Clear the word buffer
                wordWidth = 0.0f;
                wordCharacters.clear();
            } else {
                wordWidth += c->getAdvanceX();
                wordCharacters.push_back(c);
            }
        }

        // Check if the word fits into this row
        float whitespaceWidth = (whitespace != nullptr && !row->characters.empty() ? whitespace->getAdvanceX() : 0.0f);
        if (row->width + whitespaceWidth + wordWidth <= width) {
            // The word fits into this row -> add it
            row->width += whitespaceWidth + wordWidth;
            if (whitespace != nullptr && !row->characters.empty()) {
                row->characters.push_back(whitespace);
            }
            row->characters.insert(row->characters.end(), wordCharacters.begin(), wordCharacters.end());
        } else {
            // The word does NOT fit into this row -> start a new row
            row = &rows.emplace_back();

            // Add the word into the new row
            row->width += wordWidth;
            row->characters.insert(row->characters.end(), wordCharacters.begin(), wordCharacters.end());
        }

        return rows;
    }

    void FontRenderer::render(const FontRenderer::Chunk &chunk, float yOffset, gfx::Bitmap& bitmap) noexcept {
        float startX = 0.0f;
        switch (this->mHorizontalAlign) {
            case gfx::Left:
                startX = 0.0f;
                break;
            case gfx::Center:
                startX = bitmap.getWidth()*0.5f - chunk.width*0.5f;
                break;
            case gfx::Right:
                startX = bitmap.getWidth() - chunk.width;
                break;
        }

        for (auto& c : chunk.characters) {
            auto data = static_cast<const uint8_t*>(c->getBitmap().getData());

            //std::cout << (char)c->getCharCode();

            size_t j = 0;
            for (int y = 0; y < c->getBitmap().getHeight(); y++) {
                for (int x = 0; x < c->getBitmap().getWidth(); x++) {
                    if (data[j]) {
                        //float t = startX + x;
                        bitmap.setPixel(static_cast<uint16_t>(startX + x), static_cast<uint16_t>(y + yOffset + (chunk.maxOverBaseline - c->getOverBaseline())), data[j]);
                    }
                    j++;
                }
            }
            startX += c->getAdvanceX();
        }
        //std::cout << std::endl;
    }

    void FontRenderer::setHorizontalAlign(gfx::HorizontalAlign horizontalAlign) noexcept {
        this->mHorizontalAlign = horizontalAlign;
    }

    void FontRenderer::setVerticalAlign(gfx::VerticalAlign verticalAlign) noexcept {
        this->mVerticalAlign = verticalAlign;
    }

    void FontRenderer::setFont(Font *font) noexcept {
        this->mFont = font;
    }

    void FontRenderer::setFontSize(font::size_t fontSize) noexcept {
        this->mFontSize = fontSize;
    }

    void FontRenderer::setMultiline(bool value) noexcept {
        this->mMultiline = value;
    }
}