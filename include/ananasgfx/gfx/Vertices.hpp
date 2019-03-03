#ifndef GFX_VERTEX_H
#define GFX_VERTEX_H

#include <map>
#include <memory>

#include "VertexBuffer.hpp"

namespace gfx {

    DEFINE_EXCEPTION(VerticesException);

    /**
     * @brief Defines the different vertex types.
     */
    enum VertexType {Position = 0, Color = 1, TextureCoords = 2};

    /**
     * @brief Combines different VertexBuffers and the Indices.
     */
    class Vertices {
    public:
        /**
         * @brief Destructor.
         */
        virtual ~Vertices() noexcept;

        /**
         * @brief Sets the renderer.
         *
         * @param pRenderer The new renderer.
         */
        void setRenderer(Renderer* pRenderer) noexcept;

        /**
         * @brief Returns the renderer.
         *
         * @return The renderer.
         */
        Renderer* getRenderer() const noexcept;

        /**
         * @brief Returns the indices buffer index.
         *
         * @return Indices buffer index.
         */
        bufferIndex_t  getIndicesBufferIndex() const noexcept;

        /**
         * @brief Returns the indices vector.
         *
         * @return The indices vector.
         */
        const std::vector<unsigned short> getIndices() const noexcept;

        /**
         * @brief Sets the indices at given index.
         *
         * @throws ee::Exception.
         * @param index The indices index.
         * @param a The value a.
         * @param b The value b.
         * @param c The value.
         */
        void setIndices(size_t index, unsigned short a, unsigned short b, unsigned short c);

        /**
         * @brief Sets the number of indices.
         *
         * @param size The new number of indices.
         */
        void setNumberOfIndices(size_t size) noexcept;

        /**
         * @brief Sets the size (number of vertices per VertexBuffer).
         *
         * @param size The new size.
         */
        void setSize(size_t size) noexcept;

        /**
         * @brief Returns the current size.
         *
         * @return The current size.
         */
        size_t getSize() const noexcept;

        /**
         * @brief Creates a new vertex buffer.
         *
         * @param type The vertex buffer type.
         * @param alignment The alignment.
         * @param shaderLocation The shader location.
         * @return Reference to the created VertexBuffer.
         */
        VertexBuffer& createBuffer(VertexType type, uint8_t alignment, vertexShaderLocation_t shaderLocation) noexcept;

        /**
         * @brief Returns the VertexBuffer of the requested type.
         *
         * @throws std::exception.
         * @param type The requested type.
         * @return Reference to the requested type.
         */
        VertexBuffer& operator[] (VertexType type);

        /**
         * @brief Returns the map containing the VertexBuffers.
         *
         * @return Reference to the map containing the VertexBuffers.
         */
        const std::map<VertexType, std::shared_ptr<VertexBuffer>>& getBuffers() const noexcept;

    private:
        /**
         * @brief Vector containing the indices.
         */
        std::vector<unsigned short> mIndices;

        /**
         * @brief The indices buffer index.
         */
        bufferIndex_t mIndicesBufferIndex = 0;

        /**
         * @brief The renderer.
         */
        Renderer* pRenderer = nullptr;

        /**
         * @brief The size.
         */
        size_t mSize = 0;

        /**
         * @brief The number of indices.
         */
        size_t mNumberOfIndices = 0;

        /**
         * @brief Map containing the type-VertexBuffer data.
         */
        std::map<VertexType, std::shared_ptr<VertexBuffer>> mVertices;
    };
}

#endif