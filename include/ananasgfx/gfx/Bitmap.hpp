#ifndef GFX_BITMAP_H
#define GFX_BITMAP_H

#include <optional>
#include <memory>

namespace gfx {

    class Bitmap {
    public:
        static std::optional<std::shared_ptr<Bitmap>> read(const std::string& filename) noexcept;

        Bitmap(void* pData, size_t width, size_t height, uint8_t channels) noexcept;
        Bitmap(Bitmap&& bitmap) noexcept;
        virtual ~Bitmap() noexcept;

        const void* getData() const noexcept;
        size_t getWidth() const noexcept;
        size_t getHeight() const noexcept;
        uint8_t getChannels() const noexcept;

        void setPixel(uint16_t x, uint16_t y, uint8_t r) noexcept;
        uint8_t getPixelGrayscale(uint16_t x, uint16_t y) const noexcept;

        void setPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g) noexcept;
        std::tuple<uint8_t,uint8_t> getPixelGrayAlpha(uint16_t x, uint16_t y) const noexcept;

        void setPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) noexcept;
        std::tuple<uint8_t,uint8_t,uint8_t> getPixelRgb(uint16_t x, uint16_t y) const noexcept;

        void setPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept;
        std::tuple<uint8_t,uint8_t,uint8_t,uint8_t> getPixelRgba(uint16_t x, uint16_t y) const noexcept;

        std::optional<std::shared_ptr<Bitmap>> resize(size_t width, size_t height) const noexcept;
        bool saveAsFile(const std::string& filename) const noexcept;
        std::shared_ptr<Bitmap> asGrayscale() const noexcept;

        void clear(uint8_t value = 0) noexcept;
        void flipVertical() noexcept;

    private:
        void* pData = nullptr;
        size_t mWidth = 0;
        size_t mHeight = 0;
        uint8_t mChannels = 0;
    };

}

#endif