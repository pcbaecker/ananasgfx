#include "../Catch.hpp"
#include <unistd.h>
#include <ananasgfx/gfx/Bitmap.hpp>
#include <ee/Log.hpp>

TEST_CASE("gfx::Bitmap") {

    ee::Log::reset();

    SECTION("std::optional<std::shared_ptr<Bitmap>> read(const std::string &) noexcept") {
        // Try to read a file that doesnt exist
        REQUIRE_FALSE(gfx::Bitmap::read("unknown.png").has_value());

        // Try to read a file that does exist but is no image
        REQUIRE_FALSE(gfx::Bitmap::read("resource/Roboto-Bold.ttf").has_value());

        // Read a file that exists
        auto bitmap = gfx::Bitmap::read("resource/icon_lightbulb.png");
        REQUIRE(bitmap.has_value());
        REQUIRE(bitmap->get()->getWidth() == 112);
        REQUIRE(bitmap->get()->getHeight() == 144);
        REQUIRE(bitmap->get()->getChannels() == 2);
    }

    // Read a file
    auto optional = gfx::Bitmap::read("resource/red2x2.png");
    REQUIRE(optional.has_value());
    auto& bitmap = *(*optional);

    SECTION("Move constructor") {
        REQUIRE(bitmap.getChannels() == 4);
        REQUIRE(bitmap.getData() != nullptr);
        REQUIRE(bitmap.getWidth() == 2);
        REQUIRE(bitmap.getHeight() == 2);

        // Move the old bitmap to the new one
        gfx::Bitmap newBitmap(std::move(bitmap));

        REQUIRE(bitmap.getChannels() == 0);
        REQUIRE(bitmap.getData() == nullptr);
        REQUIRE(bitmap.getWidth() == 0);
        REQUIRE(bitmap.getHeight() == 0);
        REQUIRE(newBitmap.getChannels() == 4);
        REQUIRE(newBitmap.getData() != nullptr);
        REQUIRE(newBitmap.getWidth() == 2);
        REQUIRE(newBitmap.getHeight() == 2);
    }

    SECTION("uint8_t getChannels() const noexcept") {
        REQUIRE(bitmap.getChannels() == 4);
    }

    SECTION("const void *getData() const noexcept") {
        // Make sure it is no nullptr
        REQUIRE(bitmap.getData() != nullptr);

        // Go through the different pixels
        auto* pBytes = (unsigned char*)bitmap.getData();
        for (int i = 0; i < 4; i++) {
            // Red
            REQUIRE(pBytes[i * 4] == 0xFF);
            // Green
            REQUIRE(pBytes[i * 4 + 1] == 0x00);
            // Blue
            REQUIRE(pBytes[i * 4 + 2] == 0x00);
            // Alpha
            REQUIRE(pBytes[i * 4 + +3] == 0xFF);
        }
    }

    SECTION("size_t getWidth() const noexcept") {
        REQUIRE(bitmap.getWidth() == 2);
    }

    SECTION("size_t getHeight() const noexcept") {
        REQUIRE(bitmap.getHeight() == 2);
    }

    SECTION("bool saveAsFile(const std::string &) const noexcept") {
        // Try to save to an invalid path
        REQUIRE_FALSE(bitmap.saveAsFile("/doesnt/exist/f.png"));

        // Save to file
        std::string filename = "myfile.png";
        REQUIRE(bitmap.saveAsFile(filename));
        // Make sure file exists
        REQUIRE(access(filename.c_str(), F_OK ) != -1);
        // Remove the file
        REQUIRE(std::remove(filename.c_str()) == 0);
    }

    SECTION("std::optional<std::shared_ptr<Bitmap>> resize(size_t, size_t) const noexcept") {
        // Make invalid resize operations
        REQUIRE_FALSE(bitmap.resize(0,0).has_value());
        REQUIRE_FALSE(bitmap.resize(1,0).has_value());
        REQUIRE_FALSE(bitmap.resize(0,1).has_value());
        REQUIRE_FALSE(bitmap.resize(32000,32000).has_value());
        REQUIRE_FALSE(bitmap.resize(32000,128).has_value());
        REQUIRE_FALSE(bitmap.resize(128,32000).has_value());

        // Resize it smaller
        auto smallOpt = bitmap.resize(1, 1);
        REQUIRE(smallOpt.has_value());
        REQUIRE(smallOpt->get()->getWidth() == 1);
        REQUIRE(smallOpt->get()->getHeight() == 1);
        REQUIRE(smallOpt->get()->getChannels() == 4);

        // Resize it bigger
        auto bigOpt = bitmap.resize(128, 128);
        REQUIRE(bigOpt.has_value());
        REQUIRE(bigOpt->get()->getWidth() == 128);
        REQUIRE(bigOpt->get()->getHeight() == 128);
        REQUIRE(bigOpt->get()->getChannels() == 4);
    }

    // Prepare a grayscale bitmap
    auto* pGrayscaleData = (uint8_t*)malloc(3 * 3);
    memset(pGrayscaleData, 0x00, 3 * 3);
    gfx::Bitmap grayscale(pGrayscaleData, 3, 3, 1);

    SECTION("void setPixel(uint16_t, uint16_t, uint8_t) noexcept") {
        // Test normal case
        REQUIRE(pGrayscaleData[0] == 0x00);
        grayscale.setPixel(0, 0, 0x34);
        REQUIRE(pGrayscaleData[0] == 0x34);
        REQUIRE(pGrayscaleData[2] == 0x00);
        grayscale.setPixel(2, 0, 0x33);
        REQUIRE(pGrayscaleData[2] == 0x33);
        REQUIRE(pGrayscaleData[8] == 0x00);
        grayscale.setPixel(2, 2, 0x22);
        REQUIRE(pGrayscaleData[8] == 0x22);

        // Test the bitmap channel / format is wrong
        REQUIRE(ee::Log::countLogLevels().empty());
        bitmap.setPixel(0, 0, 0x00);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 1);

        // Test out of bounds
        grayscale.setPixel(3, 3, 0x00);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 2);
    }

    SECTION("uint8_t getPixelGrayscale(uint16_t x, uint16_t y) const noexcept") {
        // Test normal case
        pGrayscaleData[0] = 0x11;
        REQUIRE(grayscale.getPixelGrayscale(0, 0) == 0x11);
        pGrayscaleData[1] = 0x12;
        REQUIRE(grayscale.getPixelGrayscale(1, 0) == 0x12);
        pGrayscaleData[3] = 0x13;
        REQUIRE(grayscale.getPixelGrayscale(0, 1) == 0x13);
        pGrayscaleData[8] = 0x14;
        REQUIRE(grayscale.getPixelGrayscale(2, 2) == 0x14);

        // Test the bitmap channel / format is wrong
        REQUIRE(ee::Log::countLogLevels().empty());
        REQUIRE(bitmap.getPixelGrayscale(0, 0) == 0);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 1);

        // Test out of bounds
        REQUIRE(grayscale.getPixelGrayscale(12, 12) == 0);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 2);
    }

    // Prepare a GrayAlpha bitmap
    auto* pGrayAlphaData = (uint8_t*)malloc(3 * 3 * 2);
    memset(pGrayAlphaData, 0x00, 3 * 3 * 2);
    gfx::Bitmap grayAlpha(pGrayAlphaData, 3, 3, 2);

    SECTION("void setPixel(uint16_t, uint16_t, uint8_t, uint8_t) noexcept") {
        // Test normal case
        REQUIRE(pGrayAlphaData[0] == 0x00);
        REQUIRE(pGrayAlphaData[1] == 0x00);
        grayAlpha.setPixel(0, 0, 0x34, 0x35);
        REQUIRE(pGrayAlphaData[0] == 0x34);
        REQUIRE(pGrayAlphaData[1] == 0x35);

        REQUIRE(pGrayAlphaData[4] == 0x00);
        REQUIRE(pGrayAlphaData[5] == 0x00);
        grayAlpha.setPixel(2, 0, 0x36, 0x37);
        REQUIRE(pGrayAlphaData[4] == 0x36);
        REQUIRE(pGrayAlphaData[5] == 0x37);

        REQUIRE(pGrayAlphaData[16] == 0x00);
        REQUIRE(pGrayAlphaData[17] == 0x00);
        grayAlpha.setPixel(2, 2, 0x38, 0x39);
        REQUIRE(pGrayAlphaData[16] == 0x38);
        REQUIRE(pGrayAlphaData[17] == 0x39);

        // Test the bitmap channel / format is wrong
        REQUIRE(ee::Log::countLogLevels().empty());
        bitmap.setPixel(0, 0, 0x00, 0x00);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 1);

        // Test out of bounds
        grayAlpha.setPixel(3, 3, 0x00, 0x00);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 2);
    }

    SECTION("std::tuple<uint8_t,uint8_t> getPixelGrayAlpha(uint16_t, uint16_t) const noexcept") {
        // Test normal case
        pGrayAlphaData[0] = 0x34;
        pGrayAlphaData[1] = 0x35;
        auto pixel = grayAlpha.getPixelGrayAlpha(0, 0);
        REQUIRE(std::get<0>(pixel) == 0x34);
        REQUIRE(std::get<1>(pixel) == 0x35);

        pGrayAlphaData[4] = 0x36;
        pGrayAlphaData[5] = 0x37;
        pixel = grayAlpha.getPixelGrayAlpha(2, 0);
        REQUIRE(std::get<0>(pixel) == 0x36);
        REQUIRE(std::get<1>(pixel) == 0x37);

        pGrayAlphaData[16] = 0x38;
        pGrayAlphaData[17] = 0x39;
        pixel = grayAlpha.getPixelGrayAlpha(2, 2);
        REQUIRE(std::get<0>(pixel) == 0x38);
        REQUIRE(std::get<1>(pixel) == 0x39);

        // Test the bitmap channel / format is wrong
        REQUIRE(ee::Log::countLogLevels().empty());
        pixel = bitmap.getPixelGrayAlpha(0, 0);
        REQUIRE(std::get<0>(pixel) == 0);
        REQUIRE(std::get<1>(pixel) == 0);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 1);

        // Test out of bounds
        pixel = grayAlpha.getPixelGrayAlpha(12, 12);
        REQUIRE(std::get<0>(pixel) == 0);
        REQUIRE(std::get<1>(pixel) == 0);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 2);
    }

    // Prepare an RGB bitmap
    auto* pRgbData = (uint8_t*)malloc(3 * 3 * 3);
    memset(pRgbData, 0x00, 3 * 3 * 3);
    gfx::Bitmap rgbBitmap(pRgbData, 3, 3, 3);

    SECTION("void setPixel(uint16_t, uint16_t, uint8_t, uint8_t, uint8_t) noexcept") {
        // Test normal case
        REQUIRE(pRgbData[0] == 0x00);
        REQUIRE(pRgbData[1] == 0x00);
        REQUIRE(pRgbData[2] == 0x00);
        rgbBitmap.setPixel(0, 0, 0x21, 0x22, 0x23);
        REQUIRE(pRgbData[0] == 0x21);
        REQUIRE(pRgbData[1] == 0x22);
        REQUIRE(pRgbData[2] == 0x23);

        REQUIRE(pRgbData[6] == 0x00);
        REQUIRE(pRgbData[7] == 0x00);
        REQUIRE(pRgbData[8] == 0x00);
        rgbBitmap.setPixel(2, 0, 0x24, 0x25, 0x26);
        REQUIRE(pRgbData[6] == 0x24);
        REQUIRE(pRgbData[7] == 0x25);
        REQUIRE(pRgbData[8] == 0x26);

        REQUIRE(pRgbData[24] == 0x00);
        REQUIRE(pRgbData[25] == 0x00);
        REQUIRE(pRgbData[26] == 0x00);
        rgbBitmap.setPixel(2, 2, 0x27, 0x28, 0x29);
        REQUIRE(pRgbData[24] == 0x27);
        REQUIRE(pRgbData[25] == 0x28);
        REQUIRE(pRgbData[26] == 0x29);

        // Test the bitmap channel / format is wrong
        REQUIRE(ee::Log::countLogLevels().empty());
        bitmap.setPixel(0, 0, 0x00, 0x00, 0x00);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 1);

        // Test out of bounds
        rgbBitmap.setPixel(3, 3, 0x00, 0x00, 0x00);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 2);
    }

    SECTION("std::tuple<uint8_t,uint8_t,uint8_t> getPixelRgb(uint16_t, uint16_t) const noexcept") {
        // Test normal case
        pRgbData[0] = 0x21;
        pRgbData[1] = 0x22;
        pRgbData[2] = 0x23;
        auto pixel = rgbBitmap.getPixelRgb(0, 0);
        REQUIRE(std::get<0>(pixel) == 0x21);
        REQUIRE(std::get<1>(pixel) == 0x22);
        REQUIRE(std::get<2>(pixel) == 0x23);

        pRgbData[6] = 0x24;
        pRgbData[7] = 0x25;
        pRgbData[8] = 0x26;
        pixel = rgbBitmap.getPixelRgb(2, 0);
        REQUIRE(std::get<0>(pixel) == 0x24);
        REQUIRE(std::get<1>(pixel) == 0x25);
        REQUIRE(std::get<2>(pixel) == 0x26);

        pRgbData[24] = 0x27;
        pRgbData[25] = 0x28;
        pRgbData[26] = 0x29;
        pixel = rgbBitmap.getPixelRgb(2, 2);
        REQUIRE(std::get<0>(pixel) == 0x27);
        REQUIRE(std::get<1>(pixel) == 0x28);
        REQUIRE(std::get<2>(pixel) == 0x29);

        // Test the bitmap channel / format is wrong
        REQUIRE(ee::Log::countLogLevels().empty());
        pixel = bitmap.getPixelRgb(0, 0);
        REQUIRE(std::get<0>(pixel) == 0);
        REQUIRE(std::get<1>(pixel) == 0);
        REQUIRE(std::get<2>(pixel) == 0);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 1);

        // Test out of bounds
        pixel = rgbBitmap.getPixelRgb(12, 12);
        REQUIRE(std::get<0>(pixel) == 0);
        REQUIRE(std::get<1>(pixel) == 0);
        REQUIRE(std::get<2>(pixel) == 0);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 2);
    }

    // Prepare an RGBA bitmap
    auto* pRgbaData = (uint8_t*)malloc(3 * 3 * 4);
    memset(pRgbaData, 0x00, 3 * 3 * 4);
    gfx::Bitmap rgbaBitmap(pRgbaData, 3, 3, 4);

    SECTION("void setPixel(uint16_t, uint16_t, uint8_t, uint8_t, uint8_t, uint8_t) noexcept") {
        // Test normal case
        REQUIRE(pRgbaData[0] == 0x00);
        REQUIRE(pRgbaData[1] == 0x00);
        REQUIRE(pRgbaData[2] == 0x00);
        REQUIRE(pRgbaData[3] == 0x00);
        rgbaBitmap.setPixel(0, 0, 0x50, 0x51, 0x52, 0x53);
        REQUIRE(pRgbaData[0] == 0x50);
        REQUIRE(pRgbaData[1] == 0x51);
        REQUIRE(pRgbaData[2] == 0x52);
        REQUIRE(pRgbaData[3] == 0x53);

        REQUIRE(pRgbaData[8] == 0x00);
        REQUIRE(pRgbaData[9] == 0x00);
        REQUIRE(pRgbaData[10] == 0x00);
        REQUIRE(pRgbaData[11] == 0x00);
        rgbaBitmap.setPixel(2, 0, 0x54, 0x55, 0x56, 0x57);
        REQUIRE(pRgbaData[8] == 0x54);
        REQUIRE(pRgbaData[9] == 0x55);
        REQUIRE(pRgbaData[10] == 0x56);
        REQUIRE(pRgbaData[11] == 0x57);

        REQUIRE(pRgbaData[32] == 0x00);
        REQUIRE(pRgbaData[33] == 0x00);
        REQUIRE(pRgbaData[34] == 0x00);
        REQUIRE(pRgbaData[35] == 0x00);
        rgbaBitmap.setPixel(2, 2, 0x58, 0x59, 0x60, 0x61);
        REQUIRE(pRgbaData[32] == 0x58);
        REQUIRE(pRgbaData[33] == 0x59);
        REQUIRE(pRgbaData[34] == 0x60);
        REQUIRE(pRgbaData[35] == 0x61);

        // Test the bitmap channel / format is wrong
        REQUIRE(ee::Log::countLogLevels().empty());
        grayscale.setPixel(0, 0, 0x00, 0x00, 0x00, 0x00);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 1);

        // Test out of bounds
        rgbaBitmap.setPixel(3, 3, 0x00, 0x00, 0x00, 0x00);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 2);
    }

    SECTION("std::tuple<uint8_t,uint8_t,uint8_t,uint8_t> getPixelRgba(uint16_t, uint16_t) const noexcept") {
        // Test normal case
        pRgbaData[0] = 0x50;
        pRgbaData[1] = 0x51;
        pRgbaData[2] = 0x52;
        pRgbaData[3] = 0x53;
        auto pixel = rgbaBitmap.getPixelRgba(0, 0);
        REQUIRE(std::get<0>(pixel) == 0x50);
        REQUIRE(std::get<1>(pixel) == 0x51);
        REQUIRE(std::get<2>(pixel) == 0x52);
        REQUIRE(std::get<3>(pixel) == 0x53);

        pRgbaData[8] = 0x54;
        pRgbaData[9] = 0x55;
        pRgbaData[10] = 0x56;
        pRgbaData[11] = 0x57;
        pixel = rgbaBitmap.getPixelRgba(2, 0);
        REQUIRE(std::get<0>(pixel) == 0x54);
        REQUIRE(std::get<1>(pixel) == 0x55);
        REQUIRE(std::get<2>(pixel) == 0x56);
        REQUIRE(std::get<3>(pixel) == 0x57);

        pRgbaData[32] = 0x58;
        pRgbaData[33] = 0x59;
        pRgbaData[34] = 0x60;
        pRgbaData[35] = 0x61;
        pixel = rgbaBitmap.getPixelRgba(2, 2);
        REQUIRE(std::get<0>(pixel) == 0x58);
        REQUIRE(std::get<1>(pixel) == 0x59);
        REQUIRE(std::get<2>(pixel) == 0x60);
        REQUIRE(std::get<3>(pixel) == 0x61);

        // Test the bitmap channel / format is wrong
        REQUIRE(ee::Log::countLogLevels().empty());
        pixel = grayAlpha.getPixelRgba(0, 0);
        REQUIRE(std::get<0>(pixel) == 0);
        REQUIRE(std::get<1>(pixel) == 0);
        REQUIRE(std::get<2>(pixel) == 0);
        REQUIRE(std::get<3>(pixel) == 0);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 1);

        // Test out of bounds
        pixel = rgbaBitmap.getPixelRgba(12, 12);
        REQUIRE(std::get<0>(pixel) == 0);
        REQUIRE(std::get<1>(pixel) == 0);
        REQUIRE(std::get<2>(pixel) == 0);
        REQUIRE(std::get<3>(pixel) == 0);
        REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 2);
    }

    SECTION("std::shared_ptr<Bitmap> asGrayscale() const noexcept") {

        SECTION("From Grayscale to Grayscale") {
            grayscale.setPixel(0, 0, 0xFF);
            grayscale.setPixel(1, 1, 0xFF);
            auto tmp = grayscale.asGrayscale();
            REQUIRE(tmp->getWidth() == 3);
            REQUIRE(tmp->getHeight() == 3);
            REQUIRE(tmp->getChannels() == 1);
            REQUIRE(tmp->getPixelGrayscale(0,0) == 0xFF);
            REQUIRE(tmp->getPixelGrayscale(0,1) == 0x00);
            REQUIRE(tmp->getPixelGrayscale(1,0) == 0x00);
            REQUIRE(tmp->getPixelGrayscale(1,1) == 0xFF);
        }

        SECTION("From GrayAlpha to Grayscale") {
            grayAlpha.setPixel(0, 0, 0x33, 0x44);
            grayAlpha.setPixel(2, 1, 0x55, 0x66);
            auto tmp = grayAlpha.asGrayscale();
            REQUIRE(tmp->getWidth() == 3);
            REQUIRE(tmp->getHeight() == 3);
            REQUIRE(tmp->getChannels() == 1);
            REQUIRE(tmp->getPixelGrayscale(0,0) == 0x33);
            REQUIRE(tmp->getPixelGrayscale(1,0) == 0x00);
            REQUIRE(tmp->getPixelGrayscale(0,1) == 0x00);
            REQUIRE(tmp->getPixelGrayscale(2,1) == 0x55);
            REQUIRE(tmp->getPixelGrayscale(1,1) == 0x0);
        }

        SECTION("From RGB to Grayscale") {
            rgbBitmap.setPixel(0, 0, 0x11, 0x22, 0x33);
            rgbBitmap.setPixel(1, 2, 0x44, 0x55, 0x66);
            auto tmp = rgbBitmap.asGrayscale();
            REQUIRE(tmp->getWidth() == 3);
            REQUIRE(tmp->getHeight() == 3);
            REQUIRE(tmp->getChannels() == 1);
            REQUIRE(tmp->getPixelGrayscale(0,0) == 0x1E);
            REQUIRE(tmp->getPixelGrayscale(1,0) == 0x00);
            REQUIRE(tmp->getPixelGrayscale(0,1) == 0x00);
            REQUIRE(tmp->getPixelGrayscale(2,1) == 0x00);
            REQUIRE(tmp->getPixelGrayscale(1,1) == 0x00);
            REQUIRE(tmp->getPixelGrayscale(1,2) == 0x51);
        }

        SECTION("From RGBA to Grayscale") {
            rgbaBitmap.setPixel(0, 0, 0x11, 0x22, 0x33, 0x00);
            rgbaBitmap.setPixel(1, 2, 0x44, 0x55, 0x66, 0x00);
            auto tmp = rgbaBitmap.asGrayscale();
            REQUIRE(tmp->getWidth() == 3);
            REQUIRE(tmp->getHeight() == 3);
            REQUIRE(tmp->getChannels() == 1);
            REQUIRE(tmp->getPixelGrayscale(0,0) == 0x1E);
            REQUIRE(tmp->getPixelGrayscale(1,0) == 0x00);
            REQUIRE(tmp->getPixelGrayscale(0,1) == 0x00);
            REQUIRE(tmp->getPixelGrayscale(2,1) == 0x00);
            REQUIRE(tmp->getPixelGrayscale(1,1) == 0x00);
            REQUIRE(tmp->getPixelGrayscale(1,2) == 0x51);
        }
    }
}
