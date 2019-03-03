#include <ananasgfx/gfx/Vertices.hpp>
#include <ananasgfx/gfx/Renderer.hpp>

namespace gfx {

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

    Renderer *Vertices::getRenderer() const noexcept {
        return this->pRenderer;
    }
}