#include "../Catch.hpp"
#include <ananasgfx/gfx/Vertices.hpp>

TEST_CASE("gfx::Vertices") {

    gfx::Vertices vertices;

    SECTION("void setRenderer(Renderer*) noexcept") {
        // Cannot be tested without an active OpenGl context
    }

    SECTION("Renderer* getRenderer() const noexcept") {
        // Cannot be tested without an active OpenGl context
    }

    SECTION("bufferIndex_t  getIndicesBufferIndex() const noexcept") {
        // Cannot be tested without an active OpenGl context
    }

    SECTION("const std::vector<unsigned short> getIndices() const noexcept") {
        // Default value
        REQUIRE(vertices.getIndices().empty());

        // Set value
        vertices.setNumberOfIndices(6);
        REQUIRE(6 == vertices.getIndices().size());
        vertices.setIndices(0, 1, 2, 3);
        REQUIRE(vertices.getIndices()[1] == 2);
    }

    SECTION("void setIndices(size_t index, unsigned short, unsigned short, unsigned short)") {
        vertices.setNumberOfIndices(6);
        vertices.setIndices(0, 1, 2, 3);
        vertices.setIndices(1, 4, 5, 6);
        REQUIRE(vertices.getIndices()[0] == 1);
        REQUIRE(vertices.getIndices()[1] == 2);
        REQUIRE(vertices.getIndices()[2] == 3);
        REQUIRE(vertices.getIndices()[3] == 4);
        REQUIRE(vertices.getIndices()[4] == 5);
        REQUIRE(vertices.getIndices()[5] == 6);
    }

    SECTION("void setNumberOfIndices(size_t) noexcept") {
        // Default value
        REQUIRE(vertices.getIndices().empty());

        // Set value
        vertices.setNumberOfIndices(6);
        REQUIRE(6 == vertices.getIndices().size());
    }

    SECTION("void setSize(size_t) noexcept") {
        // Can not correctly be tested without OpenGL context
        REQUIRE(0 == vertices.getSize());
        vertices.setSize(3);
        REQUIRE(3 == vertices.getSize());
    }

    SECTION("VertexBuffer& createBuffer(VertexType, uint8_t, vertexShaderLocation_t) noexcept") {
        // Cannot be tested without an active OpenGl context
    }

    SECTION("VertexBuffer& operator[] (VertexType)") {
        // Cannot be tested without an active OpenGl context
    }

    SECTION("const std::map<VertexType, std::shared_ptr<VertexBuffer>>& getBuffers() const noexcept") {
        // Cannot be tested without an active OpenGl context
    }

}