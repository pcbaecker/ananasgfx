#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>
#include <stb_image_resize.h>
#include <ananasgfx/gfx/Bitmap.hpp>
#include <ee/Log.hpp>

namespace gfx {

    std::optional<std::shared_ptr<Bitmap>> Bitmap::read(const std::string &filename) noexcept {
        // Try to open file and read the content
        int width, height, channels;
        //stbi_set_flip_vertically_on_load(true);
        stbi_uc* pData = stbi_load(filename.c_str(), &width, &height, &channels, 0);

        // Check result
        if (pData == nullptr) {
            return {};
        }

        // Create and return a shared pointer containing the data
        return {std::make_shared<Bitmap>(pData, width, height, channels)};
    }

    Bitmap::Bitmap(void *pData, size_t width, size_t height, uint8_t channels) noexcept :
    pData(pData), mWidth(width), mHeight(height), mChannels(channels) {

    }

    Bitmap::Bitmap(size_t width, size_t height, uint8_t channels) noexcept :
    pData(malloc(width * height * channels)), mWidth(width), mHeight(height), mChannels(channels) {

    }

    Bitmap::Bitmap(Bitmap &&bitmap) noexcept :
    pData(bitmap.pData),
    mWidth(bitmap.mWidth),
    mHeight(bitmap.mHeight),
    mChannels(bitmap.mChannels) {
        bitmap.pData = nullptr;
        bitmap.mWidth = 0;
        bitmap.mHeight = 0;
        bitmap.mChannels = 0;
    }

    Bitmap::~Bitmap() noexcept {
        if (this->pData != nullptr) {
            free(this->pData);
            this->pData = nullptr;
        }
    }

    const void *Bitmap::getData() const noexcept {
        return this->pData;
    }

    size_t Bitmap::getWidth() const noexcept {
        return this->mWidth;
    }

    size_t Bitmap::getHeight() const noexcept {
        return this->mHeight;
    }

    uint8_t Bitmap::getChannels() const noexcept {
        return this->mChannels;
    }

    bool Bitmap::saveAsFile(const std::string &filename) const noexcept {
        //stbi_flip_vertically_on_write(1);
        return stbi_write_png(
                filename.c_str(),
                static_cast<int>(this->mWidth),
                static_cast<int>(this->mHeight),
                this->mChannels,
                this->pData,
                static_cast<int>(this->mWidth * this->mChannels)) > 0;
    }

    std::optional<std::shared_ptr<Bitmap>> Bitmap::resize(size_t width, size_t height) const noexcept {
        if (width == 0 || height == 0 || width > 10000 || height > 10000) {
            return {};
        }

        // Create the memory for the new bitmap
        void* pOutputData = malloc(width * height * this->mChannels);

        // Resize to the given size
        int result = stbir_resize_uint8(
                // Input
                static_cast<const unsigned char*>(this->pData), static_cast<int>(this->mWidth), static_cast<int>(this->mHeight), 0,
                // Output
                static_cast<unsigned char*>(pOutputData), static_cast<int>(width), static_cast<int>(height), 0,
                // Configuration
                this->mChannels);

        // Check for error
        if (result != 1) {
            // We must free the allocated data and return null
            free(pOutputData);
            return {};
        }

        // Create the new bitmap and return it
        return {std::make_shared<gfx::Bitmap>(pOutputData, width, height, this->mChannels)};
    }

    void Bitmap::flipVertical() noexcept {
        // Prepare the new data buffer
        const size_t numBytes = this->mWidth * this->mHeight * this->mChannels;
        void* data = malloc(numBytes);
        memset(data, 0, numBytes);

        // Get the data buffers
        auto srcData = static_cast<uint8_t*>(this->pData);
        auto dstData = static_cast<uint8_t*>(data);

        // Go through the buffers pixel by pixel
        for (int x = 0; x < this->mWidth; x++) {
            for (int y = 0; y < this->mHeight; y++) {
                // Calculate the buffer offsets
                size_t srcOffset = (this->mWidth * y + x) * this->mChannels;
                size_t dstOffset = (this->mWidth * (this->mHeight - y - 1) + x) * this->mChannels;

                // Copy the pixel
                memcpy(&dstData[dstOffset], &srcData[srcOffset], this->mChannels);
            }
        }

        // Swap the data buffers
        free(this->pData);
        this->pData = data;
    }

    void Bitmap::setPixel(uint16_t x, uint16_t y, uint8_t r) noexcept {
        // Make sure we have a grayscale bitmap
        if (this->mChannels != 1) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "This method can only be used on Grayscale bitmaps", {
                ee::Note("Channels", this->mChannels)
            });
            return;
        }

        // Make sure the given coordinates do not exceed the boundary
        if (x >= this->mWidth || y >= this->mHeight) {
            /*ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "The given coordinates are out of bounds", {
                    ee::Note("Channels", this->mChannels),
                    ee::Note("Width", this->mWidth),
                    ee::Note("Height", this->mHeight),
                    ee::Note("x", x),
                    ee::Note("y", y)
            });*/
            return;
        }

        // Calculate the offset
        size_t offset = ((this->mWidth * y) + x);

        // Set data
        auto* data = static_cast<uint8_t*>(this->pData);
        data[offset] = r;
    }

    uint8_t Bitmap::getPixelGrayscale(uint16_t x, uint16_t y) const noexcept {
        // Make sure we have a grayscale bitmap
        if (this->mChannels != 1) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "This method can only be used on Grayscale bitmaps", {
                    ee::Note("Channels", this->mChannels)
            });
            return 0;
        }

        // Make sure the given coordinates do not exceed the boundary
        if (x >= this->mWidth || y >= this->mHeight) {
            /*ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "The given coordinates are out of bounds", {
                    ee::Note("Channels", this->mChannels),
                    ee::Note("Width", this->mWidth),
                    ee::Note("Height", this->mHeight),
                    ee::Note("x", x),
                    ee::Note("y", y)
            });*/
            return 0;
        }

        // Calculate the offset
        size_t offset = ((this->mWidth * y) + x);

        // Get data
        auto* data = static_cast<uint8_t*>(this->pData);
        return data[offset];
    }

    void Bitmap::setPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g) noexcept {
        // Make sure we have a GrayAlpha bitmap
        if (this->mChannels != 2) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "This method can only be used on GrayAlpha bitmaps", {
                    ee::Note("Channels", this->mChannels)
            });
            return;
        }

        // Make sure the given coordinates do not exceed the boundary
        if (x >= this->mWidth || y >= this->mHeight) {
            /*ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "The given coordinates are out of bounds", {
                    ee::Note("Channels", this->mChannels),
                    ee::Note("Width", this->mWidth),
                    ee::Note("Height", this->mHeight),
                    ee::Note("x", x),
                    ee::Note("y", y)
            });*/
            return;
        }

        // Calculate the offset
        size_t offset = ((this->mWidth * y) + x) * 2;

        // Set data
        auto* data = static_cast<uint8_t*>(this->pData);
        data[offset] = r;
        data[offset+1] = g;
    }

    std::tuple<uint8_t, uint8_t> Bitmap::getPixelGrayAlpha(uint16_t x, uint16_t y) const noexcept {
        // Make sure we have a GrayAlpha bitmap
        if (this->mChannels != 2) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "This method can only be used on GrayAlpha bitmaps", {
                    ee::Note("Channels", this->mChannels)
            });
            return {0,0};
        }

        // Make sure the given coordinates do not exceed the boundary
        if (x >= this->mWidth || y >= this->mHeight) {
            /*ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "The given coordinates are out of bounds", {
                    ee::Note("Channels", this->mChannels),
                    ee::Note("Width", this->mWidth),
                    ee::Note("Height", this->mHeight),
                    ee::Note("x", x),
                    ee::Note("y", y)
            });*/
            return {0,0};
        }

        // Calculate the offset
        size_t offset = ((this->mWidth * y) + x) * 2;

        // Get data
        auto* data = static_cast<uint8_t*>(this->pData);
        return {data[offset], data[offset+1]};
    }

    void Bitmap::setPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) noexcept {
        // Make sure we have a RGB bitmap
        if (this->mChannels != 3) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "This method can only be used on RGB bitmaps", {
                    ee::Note("Channels", this->mChannels)
            });
            return;
        }

        // Make sure the given coordinates do not exceed the boundary
        if (x >= this->mWidth || y >= this->mHeight) {
            /*ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "The given coordinates are out of bounds", {
                    ee::Note("Channels", this->mChannels),
                    ee::Note("Width", this->mWidth),
                    ee::Note("Height", this->mHeight),
                    ee::Note("x", x),
                    ee::Note("y", y)
            });*/
            return;
        }

        // Calculate the offset
        size_t offset = ((this->mWidth * y) + x) * 3;

        // Set data
        auto* data = static_cast<uint8_t*>(this->pData);
        data[offset] = r;
        data[offset+1] = g;
        data[offset+2] = b;
    }

    std::tuple<uint8_t, uint8_t, uint8_t> Bitmap::getPixelRgb(uint16_t x, uint16_t y) const noexcept {
        // Make sure we have a RGB bitmap
        if (this->mChannels != 3) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "This method can only be used on RGB bitmaps", {
                    ee::Note("Channels", this->mChannels)
            });
            return {0,0,0};
        }

        // Make sure the given coordinates do not exceed the boundary
        if (x >= this->mWidth || y >= this->mHeight) {
            /*ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "The given coordinates are out of bounds", {
                    ee::Note("Channels", this->mChannels),
                    ee::Note("Width", this->mWidth),
                    ee::Note("Height", this->mHeight),
                    ee::Note("x", x),
                    ee::Note("y", y)
            });*/
            return {0,0,0};
        }

        // Calculate the offset
        size_t offset = ((this->mWidth * y) + x) * 3;

        // Get data
        auto* data = static_cast<uint8_t*>(this->pData);
        return {data[offset], data[offset+1], data[offset+2]};
    }

    void Bitmap::setPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept {
        // Make sure we have a RGBA bitmap
        if (this->mChannels != 4) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "This method can only be used on RGBA bitmaps", {
                    ee::Note("Channels", this->mChannels)
            });
            return;
        }

        // Make sure the given coordinates do not exceed the boundary
        if (x >= this->mWidth || y >= this->mHeight) {
            /*ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "The given coordinates are out of bounds", {
                    ee::Note("Channels", this->mChannels),
                    ee::Note("Width", this->mWidth),
                    ee::Note("Height", this->mHeight),
                    ee::Note("x", x),
                    ee::Note("y", y)
            });*/
            return;
        }

        // Calculate the offset
        size_t offset = ((this->mWidth * y) + x) * 4;

        // Set data
        auto* data = static_cast<uint8_t*>(this->pData);
        data[offset] = r;
        data[offset+1] = g;
        data[offset+2] = b;
        data[offset+3] = a;
    }

    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> Bitmap::getPixelRgba(uint16_t x, uint16_t y) const noexcept {
        // Make sure we have a RGBA bitmap
        if (this->mChannels != 4) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "This method can only be used on RGBA bitmaps", {
                    ee::Note("Channels", this->mChannels)
            });
            return {0,0,0,0};
        }

        // Make sure the given coordinates do not exceed the boundary
        if (x >= this->mWidth || y >= this->mHeight) {
            /*ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "The given coordinates are out of bounds", {
                    ee::Note("Channels", this->mChannels),
                    ee::Note("Width", this->mWidth),
                    ee::Note("Height", this->mHeight),
                    ee::Note("x", x),
                    ee::Note("y", y)
            });*/
            return {0,0,0,0};
        }

        // Calculate the offset
        size_t offset = ((this->mWidth * y) + x) * 4;

        // Get data
        auto* data = static_cast<uint8_t*>(this->pData);
        return {data[offset], data[offset+1], data[offset+2], data[offset+3]};
    }

    std::shared_ptr<Bitmap> Bitmap::asGrayscale() const noexcept {
        // Create the raw bitmap data
        auto bitmap = std::make_shared<Bitmap>(
                this->mWidth, this->mHeight, 1);

        // Iterate through all pixels
        for (uint16_t x = 0; x < this->mWidth; x++) {
            for (uint16_t y = 0; y < this->mHeight; y++) {
                switch (this->mChannels) {
                    default:
                        ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "Unsupported number of chanells", {
                            ee::Note("Channels", this->mChannels)
                        }); break;
                    case 1:
                        // Just copy the pixel
                        bitmap->setPixel(x, y, this->getPixelGrayscale(x, y));
                        break;

                    case 2: {
                        // Just use the value part
                        auto pixel = this->getPixelGrayAlpha(x, y);
                        bitmap->setPixel(x, y, std::get<0>(pixel));
                    }break;

                    case 3: {
                        // Combine rgb channels
                        auto p = this->getPixelRgb(x, y);
                        auto v = static_cast<uint8_t>(
                                0.299*std::get<0>(p) + 0.587*std::get<1>(p) + 0.114*std::get<2>(p));
                        bitmap->setPixel(x, y, v);
                    }break;

                    case 4: {
                        // Combine rgb channels
                        auto p = this->getPixelRgba(x, y);
                        auto v = static_cast<uint8_t>(
                                0.299*std::get<0>(p) + 0.587*std::get<1>(p) + 0.114*std::get<2>(p));
                        bitmap->setPixel(x, y, v);
                    }break;
                }
            }
        }

        return bitmap;
    }

    void Bitmap::clear(uint8_t value) noexcept {
        memset(this->pData, value, this->mWidth * this->mHeight * this->mChannels);
    }
}