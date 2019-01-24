#include <ananasgfx/gfx/Vertex.hpp>
#include <ananasgfx/gfx/Renderer.hpp>

namespace gfx {

    VertexBuffer::VertexBuffer(Renderer* pRenderer, vertexShaderLocation_t shaderLocation, uint8_t alignment) :
    pRenderer(pRenderer),
    mShaderLocation(shaderLocation),
    mAlignment(alignment),
    mBufferIndex(this->pRenderer->createVertexBuffer()) {

    }

    VertexBuffer::~VertexBuffer() noexcept {
        this->pRenderer->deleteVertexBuffer(this->mBufferIndex);
    }

    void VertexBuffer::set(size_t index, float x, float y) {
        // Make sure that index is not out of bounds
        if (index >= this->mData.size() / this->mAlignment) {
            throw VertexBufferException(__PRETTY_FUNCTION__, "Index out of bounds", {
                    ee::Note("Index", index, __PRETTY_FUNCTION__),
                    ee::Note("X", x, __PRETTY_FUNCTION__),
                    ee::Note("Y", y, __PRETTY_FUNCTION__)
            });
        }

        // Copy into memory
        index = index * this->mAlignment;
        this->mData[index++] = x;
        this->mData[index++] = y;
    }

    void VertexBuffer::set(size_t index, float x, float y, float z) {
        // Make sure that index is not out of bounds
        if (index >= this->mData.size() / this->mAlignment) {
            throw VertexBufferException(__PRETTY_FUNCTION__, "Index out of bounds", {
                ee::Note("Index", index, __PRETTY_FUNCTION__),
                ee::Note("X", x, __PRETTY_FUNCTION__),
                ee::Note("Y", y, __PRETTY_FUNCTION__),
                ee::Note("Z", z, __PRETTY_FUNCTION__)
            });
        }

        // Copy into memory
        index = index * this->mAlignment;
        this->mData[index++] = x;
        this->mData[index++] = y;
        this->mData[index] = z;
    }

    void VertexBuffer::set(size_t index, const glm::vec3 &vertex) {
        // Make sure that index is not out of bounds
        if (index >= this->mData.size() / this->mAlignment) {
            throw VertexBufferException(__PRETTY_FUNCTION__, "Index out of bounds", {
                    ee::Note("Index", index, __PRETTY_FUNCTION__),
                    ee::Note("X", vertex.x, __PRETTY_FUNCTION__),
                    ee::Note("Y", vertex.y, __PRETTY_FUNCTION__),
                    ee::Note("Z", vertex.z, __PRETTY_FUNCTION__)
            });
        }

        // Copy into memory
        memcpy(&this->mData[index * this->mAlignment], reinterpret_cast<const float*>(&vertex), 3 * sizeof(float));
    }

    void VertexBuffer::set(size_t index, const glm::vec4 &vertex) {
        // Make sure that index is not out of bounds
        if (index >= this->mData.size() / this->mAlignment) {
            throw VertexBufferException(__PRETTY_FUNCTION__, "Index out of bounds", {
                    ee::Note("Index", index, __PRETTY_FUNCTION__),
                    ee::Note("X", vertex.x, __PRETTY_FUNCTION__),
                    ee::Note("Y", vertex.y, __PRETTY_FUNCTION__),
                    ee::Note("Z", vertex.z, __PRETTY_FUNCTION__),
                    ee::Note("W", vertex.w, __PRETTY_FUNCTION__)
            });
        }

        // Copy into memory
        memcpy(&this->mData[index * this->mAlignment], reinterpret_cast<const float*>(&vertex), 4 * sizeof(float));
    }

    const glm::vec3& VertexBuffer::get3(size_t index) const {
        return *reinterpret_cast<const glm::vec3*>(&this->mData[index * this->mAlignment]);
    }

    bufferIndex_t VertexBuffer::getBufferIndex() const noexcept {
        return this->mBufferIndex;
    }

    void VertexBuffer::setSize(size_t size) {
        this->mData.resize(size * this->mAlignment);
    }

    vertexShaderLocation_t VertexBuffer::getShaderLocation() const noexcept {
        return this->mShaderLocation;
    }

    const std::vector<float> VertexBuffer::getData() const noexcept {
        return this->mData;
    }

    uint8_t VertexBuffer::getAlignment() const noexcept {
        return this->mAlignment;
    }

    Vertices::~Vertices() noexcept {
        if (this->pRenderer && this->mIndicesBufferIndex != 0) {
            this->pRenderer->deleteIndicesBuffer(this->mIndicesBufferIndex);
        }
    }

    void Vertices::setSize(size_t size) noexcept {
        if (this->mSize != size) {
            this->mSize = size;

            for (auto& v : this->mVertices) {
                v.second->setSize(this->mSize);
            }
        }
    }

    size_t Vertices::getSize() const noexcept {
        return this->mSize;
    }

    void Vertices::setNumberOfIndices(size_t size) noexcept {
        if (this->mNumberOfIndices != size) {
            this->mNumberOfIndices = size;

            this->mIndices.resize(size);
        }
    }

    void Vertices::setRenderer(Renderer *pRenderer) noexcept {
        this->pRenderer = pRenderer;

        this->mIndicesBufferIndex = this->pRenderer->createIndicesBuffer();
    }

    VertexBuffer& Vertices::createBuffer(VertexType type, uint8_t alignment, vertexShaderLocation_t shaderLocation) noexcept {
        // Make sure that no buffer with the given type already exists
        if (this->mVertices.count(type) == 0) {
            // Try to create the vertex buffer (may throw an exception due to unsuccessful creation)
            this->mVertices.emplace(type, std::make_shared<VertexBuffer>(this->pRenderer, shaderLocation, alignment));

            // Set the size to the verex
            if (this->mSize > 0) {
                this->mVertices.at(type)->setSize(this->mSize);
            }
        }

        return *this->mVertices.at(type);
    }

    bufferIndex_t Vertices::getIndicesBufferIndex() const noexcept {
        return this->mIndicesBufferIndex;
    }

    VertexBuffer &Vertices::operator[](VertexType type) {
        // Check if a vertex buffer for given type is present
        if (this->mVertices.count(type) == 0) {
            throw VerticesException(__PRETTY_FUNCTION__, "No vertex buffer for given type present", {
                ee::Note("Type", type, __PRETTY_FUNCTION__)
            });
        }

        // Return a reference of the buffer
        return *this->mVertices[type];
    }

    const std::map<VertexType, std::shared_ptr<VertexBuffer>> &Vertices::getBuffers() const noexcept {
        return this->mVertices;
    }

    const std::vector<unsigned short> Vertices::getIndices() const noexcept {
        return this->mIndices;
    }

    void Vertices::setIndices(size_t index, unsigned short a, unsigned short b, unsigned short c) {
        index = index * 3;
        this->mIndices[index++] = a;
        this->mIndices[index++] = b;
        this->mIndices[index] = c;
    }
}