#include <ananasgfx/gfx/VertexBuffer.hpp>
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
        this->mData[index] = y;
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

    const std::vector<float>& VertexBuffer::getData() const noexcept {
        return this->mData;
    }

    uint8_t VertexBuffer::getAlignment() const noexcept {
        return this->mAlignment;
    }

}