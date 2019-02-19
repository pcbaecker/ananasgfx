#ifndef GFX_VERTEX_H
#define GFX_VERTEX_H

#include <map>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <ee/Exception.hpp>

namespace gfx {


    typedef unsigned int bufferIndex_t;
    typedef unsigned short vertexShaderLocation_t;

    enum VertexType {Position = 0, Color = 1, TextureCoords = 2};

    class Vertices;
    class Renderer;

    DEFINE_EXCEPTION(VertexBufferException);

    class VertexBuffer {
        friend class Vertices;
    public:
        VertexBuffer(Renderer* pRenderer, vertexShaderLocation_t index, uint8_t alignment);
        virtual ~VertexBuffer() noexcept;

        void set(size_t index, float x, float y, float z);
        void set(size_t index, const glm::vec3& vector);
        void set(size_t index, const glm::vec4& vector);
        void set(size_t index, float x, float y);
        const glm::vec3& get3(size_t index) const;
        bufferIndex_t getBufferIndex() const noexcept;
        uint8_t getAlignment() const noexcept;

        vertexShaderLocation_t getShaderLocation() const noexcept;
        const std::vector<float> getData() const noexcept;

    private:
        void setSize(size_t size);

    private:
        Renderer* pRenderer = nullptr;
        vertexShaderLocation_t mShaderLocation = 0;
        bufferIndex_t mBufferIndex = 0;
        std::vector<float> mData;
        uint8_t mAlignment = 0;
    };

    DEFINE_EXCEPTION(VerticesException);

    class Vertices {
    public:
        virtual ~Vertices() noexcept;
        void setRenderer(Renderer* pRenderer) noexcept;

        bufferIndex_t  getIndicesBufferIndex() const noexcept;
        const std::vector<unsigned short> getIndices() const noexcept;

        void setIndices(size_t index, unsigned short a, unsigned short b, unsigned short c);

        void setNumberOfIndices(size_t size) noexcept;
        void setSize(size_t size) noexcept;
        size_t getSize() const noexcept;
        VertexBuffer& createBuffer(VertexType type, uint8_t alignment, vertexShaderLocation_t shaderLocation) noexcept;

        VertexBuffer& operator[] (VertexType type);
        const std::map<VertexType, std::shared_ptr<VertexBuffer>>& getBuffers() const noexcept;

    private:
        std::vector<unsigned short> mIndices;
        bufferIndex_t mIndicesBufferIndex = 0;
        Renderer* pRenderer = nullptr;
        size_t mSize = 0;
        size_t mNumberOfIndices = 0;
        std::map<VertexType, std::shared_ptr<VertexBuffer>> mVertices;
    };

}

#endif