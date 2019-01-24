#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>
#include <ananasgfx/gfx/Bitmap.hpp>

#include <iostream>
namespace gfx {

    std::optional<std::shared_ptr<Bitmap>> Bitmap::read(const std::string &filename) noexcept {
        // Try to open file and read the content
        int width, height, channels;
        stbi_uc* pData = stbi_load(filename.c_str(), &width, &height, &channels, 0);

        // Check result
        if (pData == nullptr) {
            return std::nullopt;
        }

        // Create and return a shared pointer containing the data
        return std::make_shared<Bitmap>(pData, width, height, channels);
    }

    Bitmap::Bitmap(void *pData, size_t width, size_t height, uint8_t channels) noexcept :
    pData(pData), mWidth(width), mHeight(height), mChannels(channels) {

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
        return stbi_write_png(
                filename.c_str(),
                static_cast<int>(this->mWidth),
                static_cast<int>(this->mHeight),
                this->mChannels,
                this->pData,
                static_cast<int>(this->mWidth * this->mChannels)) > 0;
    }
}