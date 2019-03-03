#ifndef GFX_VERTEXBUFFER_H
#define GFX_VERTEXBUFFER_H

#include <vector>
#include <glm/glm.hpp>
#include <ee/Exception.hpp>

namespace gfx {

    typedef unsigned int bufferIndex_t;
    typedef unsigned short vertexShaderLocation_t;

    class Vertices;
    class Renderer;

    DEFINE_EXCEPTION(VertexBufferException);

    /**
     * @brief Buffers a type of vertices.
     */
    class VertexBuffer {
        friend class Vertices;
    public:

        /**
         * @brief Constructor.
         *
         * @throws std::exception.
         * @param pRenderer The renderer.
         * @param index The vertex shader location.
         * @param alignment The alignment.
         */
        VertexBuffer(Renderer* pRenderer, vertexShaderLocation_t index, uint8_t alignment);

        /**
         * @brief Destructor.
         */
        virtual ~VertexBuffer() noexcept;

        /**
         * @brief Sets the vertex at given index.
         *
         * @throws ee::Exception.
         * @param index The vertex index.
         * @param x The X-Value.
         * @param y The Y-Value.
         * @param z The Z-Value.
         */
        void set(size_t index, float x, float y, float z);

        /**
         * @brief Sets the vertex at given index.
         *
         * @throws ee::Exception.
         * @param index The vertex index.
         * @param vector The value to set.
         */
        void set(size_t index, const glm::vec3& vector);

        /**
         * @brief Sets the vertex at given index.
         *
         * @throws ee::Exception.
         * @param index The vertex index.
         * @param vector The value to set.
         */
        void set(size_t index, const glm::vec4& vector);

        /**
         * @brief Sets the vertex at given index.
         *
         * @throws ee::Exception.
         * @param index The vertex index.
         * @param x The X-Value.
         * @param y The Y-Value.
         */
        void set(size_t index, float x, float y);

        /**
         * @brief Returns the 3-vector value at given index.
         *
         * @throws ee::Exception.
         * @param index The vertex index.
         * @return The 3-vector value at given index.
         */
        const glm::vec3& get3(size_t index) const;

        /**
         * @brief Returns the buffer index.
         *
         * @return The buffer index.
         */
        bufferIndex_t getBufferIndex() const noexcept;

        /**
         * @brief Returns the alignment.
         *
         * @return The alignment.
         */
        uint8_t getAlignment() const noexcept;

        /**
         * @brief Returns the shader location.
         *
         * @return The shader location.
         */
        vertexShaderLocation_t getShaderLocation() const noexcept;

        /**
         * @brief Returns a reference to the internal data.
         *
         * @return Reference to the internal data.
         */
        const std::vector<float>& getData() const noexcept;

    private:
        /**
         * @brief Sets the size of this buffer.
         *
         * @throws ee::Exception.
         * @param size The size of this buffer.
         */
        void setSize(size_t size);

    private:
        /**
         * @brief The renderer.
         */
        Renderer* pRenderer = nullptr;

        /**
         * @brief The vertex shader location.
         */
        vertexShaderLocation_t mShaderLocation = 0;

        /**
         * @brief The buffer index.
         */
        bufferIndex_t mBufferIndex = 0;

        /**
         * @brief The internal data vector.
         */
        std::vector<float> mData;

        /**
         * @brief The alignment.
         */
        uint8_t mAlignment = 0;
    };

}

#endif