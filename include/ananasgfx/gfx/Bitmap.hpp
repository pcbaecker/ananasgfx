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

        bool saveAsFile(const std::string& filename) const noexcept;

    private:
        void* pData = nullptr;
        size_t mWidth = 0;
        size_t mHeight = 0;
        uint8_t mChannels = 0;
    };

}

#endif