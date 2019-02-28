#ifndef GFX_BITMAP_H
#define GFX_BITMAP_H

#include <optional>
#include <memory>

namespace gfx {

    /**
     * @brief Contains the data and meta information of a bitmap that represents an image.
     */
    class Bitmap {
    public:
        /**
         * @brief Reads an image file from the given path into a bitmap.
         *
         * @param filename The path to the image file we want to read.
         * @return An optional that can contain the bitmap.
         */
        static std::optional<std::shared_ptr<Bitmap>> read(const std::string& filename) noexcept;

        /**
         * @brief Constructor.
         *
         * @param pData The binary data.
         * @param width The width of the bitmap.
         * @param height The height of the bitmap.
         * @param channels The number of channels in this bitmap.
         */
        Bitmap(void* pData, size_t width, size_t height, uint8_t channels) noexcept;

        /**
         * @brief Constructor.
         *
         * @param width The width of the bitmap.
         * @param height The height of the bitmap.
         * @param channels The number of channels.
         */
        Bitmap(size_t width, size_t height, uint8_t channels) noexcept;

        /**
         * @brief Move constructor.
         *
         * @param bitmap The moved bitmap.
         */
        Bitmap(Bitmap&& bitmap) noexcept;

        /**
         * @brief Destructor.
         */
        virtual ~Bitmap() noexcept;

        /**
         * @brief Returns a pointer to the internal data.
         *
         * @return Pointer to the internal data.
         */
        const void* getData() const noexcept;

        /**
         * @brief Returns the width of the bitmap.
         *
         * @return The width of the bitmap.
         */
        size_t getWidth() const noexcept;

        /**
         * @brief Returns the height of the bitmap.
         *
         * @return The height of the bitmap.
         */
        size_t getHeight() const noexcept;

        /**
         * @brief Returns the number of channels.
         *
         * @return The number of channels.
         */
        uint8_t getChannels() const noexcept;

        /**
         * @brief Sets a single pixel at given coordinates.
         *
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         * @param r The pixel value.
         */
        void setPixel(uint16_t x, uint16_t y, uint8_t r) noexcept;

        /**
         * @brief Returns the value of a single pixel.
         *
         * @param x The X-Coordinate of the pixel.
         * @param y The Y-Coordinate of the pixel.
         * @return The value of the pixel.
         */
        uint8_t getPixelGrayscale(uint16_t x, uint16_t y) const noexcept;

        /**
         * @brief Sets the pixel at the given coordinates.
         *
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         * @param r The r value of the pixel.
         * @param g The g value of the pixel.
         */
        void setPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g) noexcept;

        /**
         * @brief Returns the value of a single pixel.
         *
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         * @return The two channels from the pixel.
         */
        std::tuple<uint8_t,uint8_t> getPixelGrayAlpha(uint16_t x, uint16_t y) const noexcept;

        /**
         * @brief Sets the pixel at the given coordinates.
         *
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         * @param r The r value.
         * @param g The g value.
         * @param b The b value.
         */
        void setPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) noexcept;

        /**
         * @brief Returns the value for a pixel.
         *
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         * @return The three channels from the pixel
         */
        std::tuple<uint8_t,uint8_t,uint8_t> getPixelRgb(uint16_t x, uint16_t y) const noexcept;

        /**
         * @brief Sets the pixel at the given coordinates.
         *
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         * @param r The red value.
         * @param g The green value.
         * @param b The blue value.
         * @param a The alpha value.
         */
        void setPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept;

        /**
         * @brief Returns the pixel at the given coordinates.
         *
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         * @return The four channels from the pixel.
         */
        std::tuple<uint8_t,uint8_t,uint8_t,uint8_t> getPixelRgba(uint16_t x, uint16_t y) const noexcept;

        /**
         * @brief Creates a new resized bitmap.
         *
         * @param width The width of the new bitmap.
         * @param height The height of the new bitmap.
         * @return The new bitmap.
         */
        std::optional<std::shared_ptr<Bitmap>> resize(size_t width, size_t height) const noexcept;

        /**
         * @brief Saves the bitmap into a file.
         *
         * Currently only png is supported.
         * @param filename The name of the target file.
         * @return True if saving was successful.
         */
        bool saveAsFile(const std::string& filename) const noexcept;

        /**
         * @brief Converts the bitmap into a grayscale bitmap.
         *
         * @return The new bitmap.
         */
        std::shared_ptr<Bitmap> asGrayscale() const noexcept;

        /**
         * @brief Clears the internal data buffer with the given value.
         *
         * @param value The value to override all bytes with.
         */
        void clear(uint8_t value = 0) noexcept;

        /**
         * @brief Flips the bitmap vertically.
         */
        void flipVertical() noexcept;

    private:
        /**
         * @brief The internal data buffer.
         */
        void* pData = nullptr;

        /**
         * @brief The width of the bitmap.
         */
        size_t mWidth = 0;

        /**
         * @brief The height of the bitmap.
         */
        size_t mHeight = 0;

        /**
         * @brief The number of channels.
         */
        uint8_t mChannels = 0;
    };
}

#endif